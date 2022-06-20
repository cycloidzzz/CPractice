#ifndef CPRACTICE_COMMON_DEBUG_H
#define CPRACTICE_COMMON_DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG

#define CPRACTICE_LOG(level, format, ...)
#define CPRACTICE_FATAL(level, format, ...)
#define CPRACTICE_ASSERT(val, format, ...)

#else

#define CPRACTICE_LOG(level, format, ...)                                      \
  fprintf(stderr,                                                              \
          "\033[0;32;32m(" #level " : %s: %s: %d): \t\033[0m" format "\n",     \
          __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define CPRACTICE_FATAL(format, ...)                                           \
  do {                                                                         \
    fprintf(stderr,                                                            \
            "\033[0;32;31m(FATAL : %s: %s: %d): \t\033[0m" format "\n",        \
            __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);                  \
    exit(1);                                                                   \
  } while (0)

#define CPRACTICE_ASSERT(val, format, ...)                                     \
  do {                                                                         \
    if (!(val)) {                                                              \
      PSI_FATAL(" assertion fail: " #val " " format, ##__VA_ARGS__);           \
    }                                                                          \
  } while (0)

#endif // ! NDEBUG

#endif // ! CPRACTICE_COMMON_DEBUG_H