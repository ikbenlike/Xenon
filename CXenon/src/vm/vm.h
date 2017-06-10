#ifndef __XENON_VM_H_
    #define __XENON_VM_H_
    #include <stdbool.h>

    enum xenon_opcodes {
        CONST,
        IADD,
        ISUB,
        IPRINT, 
        HALT
    };

    enum xenon_variable_types {
        opcode,
        integer,
        boolean,
        character
    };

    typedef struct {
        enum xenon_variable_types type;
        union {
            int opcode;
            int integer;
            bool boolean;
            char character;
        };
    } xenon_stack_item_t;

    typedef struct {
        int len;
        int cursor;
        xenon_stack_item_t *stack;
    } xenon_stack_t;

    int xenon_vm_exec(xenon_stack_t code, xenon_stack_t stack, int startip);

#endif
