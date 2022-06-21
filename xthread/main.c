#include "xthread.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void hello(void *args) {
  while (1) {
    printf("What the fuck from Thread %zd\n", (size_t)args);
    fflush(stdout);
  }
}

int main() {
  xthread_constructor();

  xthread_t *my_thread1 = xthread_create(hello, (void *)1);
  xthread_t *my_thread2 = xthread_create(hello, (void *)2);

  while (1) {
    printf("Hello from main\n");
    fflush(stdout);
  }

  return 0;
}