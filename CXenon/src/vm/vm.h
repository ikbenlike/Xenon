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
        FADD,
        FSUB,
        FMUL,
        FDIV,
        FMOD,
        SADD,
        SPRINT,
        SPRINTLN,
        IPRINT,
        IPRINTLN,
        FPRINT,
        FPRINTLN,
        HALT
    };

    enum xenon_variable_types {
        opcode,
        integer,
        floating,
        boolean,
        character,
        string
    };

    typedef struct {
        char *contents;
        size_t len;
    } xenon_string_t;

    typedef struct {
        enum xenon_variable_types type;
        union {
            int opcode;
            int integer;
            float floating;
            bool boolean;
            char character;
            xenon_string_t string;
        };
    } xenon_stack_item_t;

    typedef struct {
        int len;
        int cursor;
        xenon_stack_item_t *stack;
    } xenon_stack_t;

    typedef struct {
        int startip;
        xenon_stack_t stack;
        xenon_stack_t code;
    } xenon_vm_t;

    int xenon_vm_exec(xenon_stack_t code, xenon_stack_t stack, int startip);
    int xenon_vm_wrapper(xenon_vm_t *vm);

#endif
