.global xthread_context_switch
xthread_context_switch:
    pushq %rdi
    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %rbp
    pushq %rbx
    movq  %rsp,(%rsi)

    movq %rdi,%rsp
    popq %rbx
    popq %rbp
    popq %r12
    popq %r13
    popq %r14
    popq %r15
    popq %rdi
    retq