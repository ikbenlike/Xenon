#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "vm_utils.h"

int main(int argc, char **argv){
    /*xenon_vm_t vm = (xenon_vm_t){
        .startip = 0,
        .stack.stack = calloc(40, sizeof(xenon_stack_item_t)),
        .code.stack = calloc(40, sizeof(xenon_stack_item_t))
    };
    xenon_stack_t stack;
    stack.stack = calloc(40, sizeof(xenon_stack_item_t));
    xenon_stack_t code;
    code.stack = calloc(40, sizeof(xenon_stack_item_t));*/
    xenon_vm_t *vm = xenon_vm_generate(0, 40, 40);
    vm->code.stack[0] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[1] = (xenon_stack_item_t){.type = integer, .integer = 4};
    vm->code.stack[2] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[3] = (xenon_stack_item_t){.type = integer, .integer = 6};
    vm->code.stack[4] = (xenon_stack_item_t){.type = opcode, .opcode = IADD};
    vm->code.stack[5] = (xenon_stack_item_t){.type = opcode, .opcode = IPRINTLN};
    vm->code.stack[6] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[7] = (xenon_stack_item_t){.type = integer, .integer = 10};
    vm->code.stack[8] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[9] = (xenon_stack_item_t){.type = integer, .integer = 3};
    vm->code.stack[10] = (xenon_stack_item_t){.type = opcode, .opcode = IMOD};
    vm->code.stack[11] = (xenon_stack_item_t){.type = opcode, .opcode = IPRINTLN};
    vm->code.stack[12] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[13] = (xenon_stack_item_t){.type = integer, .integer = 10};
    vm->code.stack[14] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[15] = (xenon_stack_item_t){.type = integer, .integer = 5};
    vm->code.stack[16] = (xenon_stack_item_t){.type = opcode, .opcode = IDIV};
    vm->code.stack[17] = (xenon_stack_item_t){.type = opcode, .opcode = IPRINTLN};
    vm->code.stack[18] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[19] = (xenon_stack_item_t){.type = integer, .integer = 2};
    vm->code.stack[20] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[21] = (xenon_stack_item_t){.type = integer, .integer = 3};
    vm->code.stack[22] = (xenon_stack_item_t){.type = opcode, .opcode = IMUL};
    vm->code.stack[23] = (xenon_stack_item_t){.type = opcode, .opcode = IPRINTLN};
    vm->code.stack[24] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[25] = (xenon_stack_item_t){.type = integer, .integer = 3};
    vm->code.stack[26] = (xenon_stack_item_t){.type = opcode, .opcode = PUSH};
    vm->code.stack[27] = (xenon_stack_item_t){.type = integer, .integer = 1};
    vm->code.stack[28] = (xenon_stack_item_t){.type = opcode, .opcode = ISUB};
    vm->code.stack[29] = (xenon_stack_item_t){.type = opcode, .opcode = IPRINTLN};
    vm->code.stack[30] = (xenon_stack_item_t){.type = opcode, .opcode = HALT};

    //xenon_vm_exec(code, stack, 0);

    xenon_vm_wrapper(vm);

    return 0;
}
