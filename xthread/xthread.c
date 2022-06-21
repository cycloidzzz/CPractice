#include <stdio.h>

#include "list.h"
#include "xthread.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

extern void xthread_context_switch(
    xthread_context_t *new,
    xthread_context_t **old_ptr) __asm__("xthread_context_switch");

static const size_t kXthreadStackSize = 4096;
static volatile int num_xthread = 0;
static xthread_t *cur_thread = NULL;
static LIST_HEAD(xthread_list);

static void xthread_schedule() {
  // disable timer

  // restore timer
}

static void xthread_disable_timer() {
  sigset_t new_sigset;
  sigemptyset(&new_sigset);
  sigaddset(&new_sigset, SIGALRM);
  sigprocmask(SIG_SETMASK, &new_sigset, NULL);
}

static void xthread_enable_timer() {
  sigset_t new_sigset;
  sigemptyset(&new_sigset);
  sigaddset(&new_sigset, SIGALRM);
  sigprocmask(SIG_UNBLOCK, &new_sigset, NULL);
}

// reschedule from the xthread_list.
void xthread_timer_callback(int signal_id) {
  xthread_disable_timer();

  printf("Hello from xthread scheduler.\n");
  fflush(stdout);

  if (!list_empty(&xthread_list)) {
    xthread_t *old_thread, *new_thread;

    list_node_t *entry_ptr = xthread_list.next;

    old_thread = cur_thread;
    new_thread = container_of(entry_ptr, xthread_t, sink);

    list_del(&(new_thread->sink));
    list_add_tail(&(old_thread->sink), &xthread_list);

    cur_thread = new_thread;

    printf("Switching from %p to %p\n", old_thread, new_thread);
    fflush(stdout);

    xthread_enable_timer();
    xthread_context_switch(new_thread->context, &(old_thread->context));
  }
}

static void xthread_on_thread_init(xthread_t *thread) {
  thread->callback(thread->args);
}

static void xthread_on_thread_exit(xthread_t *thread) {
  thread->status = kZombie;
  // FIXME (ozr) : call xthread_reschedule
}

static int xthread_set_timer() {
  struct itimerval timer;

  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 500000;

  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 500000;

  return setitimer(ITIMER_REAL, &timer, NULL);
}

void xthread_constructor() {
  printf("Start creating thread.");
  fflush(stdout);

  cur_thread = (xthread_t *)malloc(sizeof(*cur_thread));
  cur_thread->status = kRunning;
  cur_thread->callback = NULL;
  cur_thread->args = NULL;
  cur_thread->context = NULL;
  cur_thread->stack_base = NULL;

  signal(SIGALRM, xthread_timer_callback);
  if (xthread_set_timer() == -1) {
    perror("xthread_set_timer");
  }
}

xthread_t *xthread_create(xthread_function_t function, void *args) {
  sigset_t new_sigset, old_sigset;

  sigemptyset(&new_sigset);
  sigaddset(&new_sigset, SIGALRM);
  sigprocmask(SIG_BLOCK, &new_sigset, &old_sigset);

  xthread_t *new_thread;
  new_thread = (xthread_t *)malloc(sizeof(*new_thread));

  printf("Creating thread with malloc.\n");
  fflush(stdout);

  if (NULL == new_thread) {
    goto xthread_create_error;
  }

  new_thread->callback = function;
  new_thread->args = args;

  void *stack_base;
  size_t *ra_base;
  xthread_context_t *context_base;
  stack_base = (void *)malloc(2 * kXthreadStackSize);

  printf("Creating thread stack with malloc.\n");
  fflush(stdout);

  if (NULL == stack_base) {
    printf("Error on creating stack_base\n");
    fflush(stdout);
    goto handle_stack_error;
  }

  ra_base = (size_t *)(stack_base + kXthreadStackSize - sizeof(size_t));
  context_base = (xthread_context_t *)((void *)ra_base - sizeof(*context_base));
  memset(context_base, 0, sizeof(*context_base));

  printf("Fill context with zeros.\n");
  fflush(stdout);

  // set up stack_base
  new_thread->stack_base = stack_base;
  // set up context
  *ra_base = (size_t)xthread_on_thread_init;
  // set up thread rsp
  new_thread->context = context_base;
  new_thread->context->rdi = (size_t)new_thread;

  // add into the xthread_list
  list_add(&(new_thread->sink), &xthread_list);

  if (list_empty(&xthread_list)) {
    printf("What the fuck? Something wrong with xthread_create\n");
    fflush(stdout);
  }

xthread_create_error:
  // Restore old sigset.
  sigprocmask(SIG_SETMASK, &old_sigset, NULL);
  return new_thread;

handle_stack_error:
  free((void *)new_thread);
  new_thread = NULL;

  goto xthread_create_error;
}