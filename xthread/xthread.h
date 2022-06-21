#ifndef CPRACTICE_XTHREAD_H
#define CPRACTICE_XTHREAD_H

#include "list.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct xthread_context_struct_t {
  size_t rbx;
  size_t rbp;
  size_t r12;
  size_t r13;
  size_t r14;
  size_t r15;
  size_t rdi;
} xthread_context_t;

typedef enum xthread_status_t {
  kReady = 0,
  kRunning,
  kSleeping,
  kZombie,
} xthread_status_t;

typedef void (*xthread_function_t)(void *);

// Callee-saved registers: r12, r13, r14, r15, rbx, rsp, rbp
/**
 *
 *  return_address
 *  rbx
 *  rbp
 *  r12
 *  r13
 *  r14
 *  r15
 *  rsp <- stack pointer
 **/

typedef struct xthread_struct_t {
  xthread_context_t *context;
  xthread_function_t callback;
  void *args;
  void *stack_base;
  xthread_status_t status;
  list_node_t sink;
} xthread_t;

extern void xthread_constructor();
extern xthread_t *xthread_create(xthread_function_t function, void *args);

#endif // ! CPRACTICE_XTHREAD_H