#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main(int argc, char **argv){
    xenon_stack_t stack;
    stack.stack = calloc(40, sizeof(xenon_stack_item_t));
    xenon_stack_t code;
    code.stack = calloc(40, sizeof(xenon_stack_item_t));
    code.stack[0] = (xenon_stack_item_t){.type = opcode, .opcode = CONST};
    code.stack[1] = (xenon_stack_item_t){.type = integer, .integer = 4};
    code.stack[2] = (xenon_stack_item_t){.type = opcode, .opcode = CONST};
    code.stack[3] = (xenon_stack_item_t){.type = integer, .integer = 6};
    code.stack[4] = (xenon_stack_item_t){.type = opcode, .opcode = IADD};
    code.stack[5] = (xenon_stack_item_t){.type = opcode, .opcode = IPRINT};
    code.stack[6] = (xenon_stack_item_t){.type = opcode, .opcode = HALT};

    xenon_vm_exec(code, stack, 0);

    return 0;
}
