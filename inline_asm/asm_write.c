#include <stdint.h>
#include <stdio.h>

static inline uint64_t write_rax() {
  // Common constraints in x86-64 inline assembly
  // See http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s7 for
  // more details.
  // (1) Register Operand Constraints
  // a. Generally, you can use
  //    "r" to bind a variable with one of the GPRs.
  // b. If you want to bind a
  //    value with one of the registers in {rax, rbx, rcx, rdx, rdi, rsi},
  //    you can use the following register operand constraints.
  //    "a" : rax, eax, ax, al
  //    "b" : rbx, ebx, bx, bl
  //    "c" : rcx, ecx, cx, cl
  //    "d" : rdx, edx, dx, dl
  //    "S" : rsi, esi, si
  //    "D" : rdi, edi, di

  // c. It is not recommended to directly reference r8-r15 with the register
  //    operand constraints, please use "r" Constraints instead.

  // TODO (ozr) : Memory Operand Constraints (m)
  // TODO (ozr) : Matching Constraints
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

static int use_clobber_list() {
  // Clobber list: To tell gcc that we will modify the value of %eax in
  // the inline assembly procedure.
  // So the compiler will help
  // (1) Saves the value of the registers in the clobber list before executing
  // the inline assembly.
  // and
  // (2) Restores the registers after executing the
  // inline assembly.
  int x = 10, y;
  __asm__ __volatile__("movl %1,%%eax;"
                       "movl %%eax,%0;"
                       : "=r"(y)
                       : "r"(x)
                       : "%eax");
}

// A trick with Clobber List: compiler barrier
// In order to stop gcc from re-ordering memory read/write,
// we fool gcc that we are modifying the operands in memory
// with the Clobber List "memory",
// which is exactly the same as how the keyword `volatile` works in C.
static void compiler_mb() { __asm__ __volatile__("" ::: "memory"); }

int main() {
  uint64_t rax_value = 0;
  rax_value = write_rax();
  printf("return value = %llu\n", rax_value);

  int a = 114000, b = 514;
  int result = my_aplusb(a, b);
  printf("%d + %d = %d\n", a, b, result);
  return 0;
}