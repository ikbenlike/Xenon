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
    xenon_vm_t *vm = xenon_vm_generate(0, 70, 70);
    //xenon_stack_append(vm->code, xenon_opcode_generate(PUSH));
    vm->code.stack[0] = xenon_opcode_generate(PUSH);
    vm->code.stack[1] = xenon_int_generate(4);
    vm->code.stack[2] = xenon_opcode_generate(PUSH);
    vm->code.stack[3] = xenon_int_generate(6);
    vm->code.stack[4] = xenon_opcode_generate(IADD);
    vm->code.stack[5] = xenon_opcode_generate(IPRINTLN);
    vm->code.stack[6] = xenon_opcode_generate(PUSH);
    vm->code.stack[7] = xenon_int_generate(10);
    vm->code.stack[8] = xenon_opcode_generate(PUSH);
    vm->code.stack[9] = xenon_int_generate(3);
    vm->code.stack[10] = xenon_opcode_generate(IMOD);
    vm->code.stack[11] = xenon_opcode_generate(IPRINTLN);
    vm->code.stack[12] = xenon_opcode_generate(PUSH);
    vm->code.stack[13] = xenon_int_generate(10);
    vm->code.stack[14] = xenon_opcode_generate(PUSH);
    vm->code.stack[15] = xenon_int_generate(5);
    vm->code.stack[16] = xenon_opcode_generate(IDIV);
    vm->code.stack[17] = xenon_opcode_generate(IPRINTLN);
    vm->code.stack[18] = xenon_opcode_generate(PUSH);
    vm->code.stack[19] = xenon_int_generate(2);
    vm->code.stack[20] = xenon_opcode_generate(PUSH);
    vm->code.stack[21] = xenon_int_generate(3);
    vm->code.stack[22] = xenon_opcode_generate(IMUL);
    vm->code.stack[23] = xenon_opcode_generate(IPRINTLN);
    vm->code.stack[24] = xenon_opcode_generate(PUSH);
    vm->code.stack[25] = xenon_int_generate(3);
    vm->code.stack[26] = xenon_opcode_generate(PUSH);
    vm->code.stack[27] = xenon_int_generate(1);
    vm->code.stack[28] = xenon_opcode_generate(ISUB);
    vm->code.stack[29] = xenon_opcode_generate(IPRINTLN);
    vm->code.stack[30] = xenon_opcode_generate(PUSH);
    vm->code.stack[31] = xenon_float_generate(3.1);
    vm->code.stack[32] = xenon_opcode_generate(PUSH);
    vm->code.stack[33] = xenon_float_generate(3.1);
    vm->code.stack[34] = xenon_opcode_generate(FMUL);
    vm->code.stack[35] = xenon_opcode_generate(FPRINTLN);
    vm->code.stack[36] = xenon_opcode_generate(PUSH);
    vm->code.stack[37] = xenon_string_generate("Hello ");
    vm->code.stack[38] = xenon_opcode_generate(PUSH);
    vm->code.stack[39] = xenon_string_generate("World!");
    vm->code.stack[40] = xenon_opcode_generate(SADD);
    vm->code.stack[41] = xenon_opcode_generate(SPRINTLN);
    vm->code.stack[42] = xenon_opcode_generate(HALT);

    //xenon_vm_exec(code, stack, 0);

    xenon_vm_wrapper(vm);

    return 0;
}
