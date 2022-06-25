#include <stdint.h>
#include <stdio.h>

static inline uint64_t write_rax() {
  // Common constraints in x86-64 inline assembly
  // See http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s7 for
  // more details.
  // (1) Register Operand Constraints a. Generally, you can use
  // "r" to bind a variable with one of the GPRs. b. If you want to bind a
  // register with one of the {rax, rbx, rcx, rdx, rdi, rsi}, you can use the
  // following register operand constraints.
  //  "a" : rax, eax, ax, al
  //  "b" : rbx, ebx, bx, bl
  //  "c" : rcx, ecx, cx, cl
  //  "d" : rdx, edx, dx, dl
  //  "S" : rsi, esi, si
  //  "D" : rdi, edi, di
  // c. It is not recommended to directly reference r8-r15 with the register
  // operand constraints, just use "r".
  // TODO (ozr) : Memory operand constraint (m)
  // TODO (ozr) : Matching constraint
  uint64_t return_value = 0;
  __asm__ __volatile__("movq $114514,%%rax;" : "=a"(return_value)::);
  return return_value;
}

static int my_aplusb(int32_t a, int32_t b) {
  int32_t result = 0;
  // bind @a with %eax, bind @b with %ebx, bind @result with %eax.
  // You can the the generated assembly with objdump.
  __asm__ __volatile__("addl %%ebx,%%eax;" : "=a"(result) : "a"(a), "b"(b));
  return result;
}

int main() {
  uint64_t rax_value = 0;
  rax_value = write_rax();
  printf("return value = %llu\n", rax_value);

  int a = 114000, b = 514;
  int result = my_aplusb(a, b);
  printf("%d + %d = %d\n", a, b, result);
  return 0;
}