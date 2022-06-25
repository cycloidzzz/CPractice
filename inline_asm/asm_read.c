#include <stdint.h>
#include <stdio.h>

typedef volatile uint64_t atomic_t;

static inline uint64_t read_rsp() {
  uint64_t rsp;
  __asm__ __volatile__("movq %%rsp, %0;" : "=r"(rsp)::);
  return rsp;
}

static inline uint64_t read_rbp() {
  uint64_t rbp;
  __asm__ __volatile__("movq %%rbp, %0;" : "=r"(rbp)::);
  return rbp;
}

int main() {
  uint64_t rsp_value, rbp_value;
  rsp_value = read_rsp();
  rbp_value = read_rbp();

  printf("The rsp = %llx\n", rsp_value);
  printf("The rbp = %llx\n", rbp_value);
  return 0;
}