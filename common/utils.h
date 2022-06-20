#ifndef CPRACTICE_COMMON_UTILS_H
#define CPRACTICE_COMMON_UTILS_H

typedef struct cuint_unittest_struct_t {
  char *description;
  void (*test_function)();
} cunit_unittest_t;

#endif // ! CPRACTICE_COMMON_UTILS_H