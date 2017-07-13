#ifndef __XENON_VM_H_
    #define __XENON_VM_H_
    #include <stdbool.h>
    #include <stddef.h>

    enum xenon_opcodes {
        PUSH,
        IADD,
        ISUB,
        IMUL,
        IDIV,
        IMOD,
        IEQ,
        INEQ,
        FADD,
        FSUB,
        FMUL,
        FDIV,
        FMOD,
        SADD,
        BADD,
        BSUB,
        BMUL,
        BDIV,
        BEQ,
        BNEQ,
        SPRINT,
        SPRINTLN,
        IPRINT,
        IPRINTLN,
        FPRINT,
        FPRINTLN,
        BPRINT,
        BPRINTLN,
        CALL,
        RET,
        JMP,
        BRT,
        BRF,
        HALT
    };

    enum xenon_variable_types {
        opcode,
        integer,
        floating,
        boolean,
        character,
        string,
        function
    };

    typedef struct {
        char *contents;
        size_t len;
    } xenon_string_t;

    typedef struct {
        int nargs;
        int nlocals;
        int addr;
    } xenon_function_t;

    typedef struct {
        enum xenon_variable_types type;
        union {
            int opcode;
            int integer;
            float floating;
            bool boolean;
            char character;
            xenon_string_t string;
            xenon_function_t func;
        };
    } xenon_stack_item_t;

    typedef struct {
        int len;
        int cursor;
        xenon_stack_item_t *stack;
    } xenon_stack_t;

    typedef struct {
        int ret;
        xenon_stack_item_t *locals;
    } xenon_context_t;

    typedef struct {
        int startip;
        xenon_stack_t stack;
        xenon_stack_t code;
        xenon_context_t *ctx;
    } xenon_vm_t;

    int xenon_vm_exec(xenon_stack_t code, xenon_stack_t stack, int startip, xenon_context_t *cstack);
    int xenon_vm_exec_wrapper(xenon_vm_t *vm);

#endif
