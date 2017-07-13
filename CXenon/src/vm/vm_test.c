#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "vm_utils.h"

int main(int argc, char **argv){
    xenon_vm_t *vm = xenon_vm_generate(0, 70, 70, 100);
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(4));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(6));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IADD));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(10));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(3));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IMOD));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(10));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(5));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IDIV));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(2));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(3));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IMUL));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(3));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_int_generate(1));
    xenon_stack_append(&vm->code, xenon_opcode_generate(ISUB));
    xenon_stack_append(&vm->code, xenon_opcode_generate(IPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_float_generate(3.1));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_float_generate(3.1));
    xenon_stack_append(&vm->code, xenon_opcode_generate(FMUL));
    xenon_stack_append(&vm->code, xenon_opcode_generate(FPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_string_generate("Hello "));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_string_generate("World!"));
    xenon_stack_append(&vm->code, xenon_opcode_generate(SADD));
    xenon_stack_append(&vm->code, xenon_opcode_generate(SPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_bool_generate(1 == 1));
    xenon_stack_append(&vm->code, xenon_opcode_generate(BRT));
    xenon_stack_append(&vm->code, xenon_int_generate(vm->code.cursor + 1));
    xenon_stack_append(&vm->code, xenon_opcode_generate(JMP));
    xenon_stack_append(&vm->code, xenon_int_generate(vm->code.cursor + 4));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_string_generate("This shouldn't print"));
    xenon_stack_append(&vm->code, xenon_opcode_generate(SPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(CALL));
    xenon_stack_append(&vm->code, xenon_func_generate(0, 1, vm->code.cursor + 2));
    xenon_stack_append(&vm->code, xenon_opcode_generate(HALT));
    xenon_stack_append(&vm->code, xenon_opcode_generate(PUSH));
    xenon_stack_append(&vm->code, xenon_string_generate("Hello Function World!"));
    xenon_stack_append(&vm->code, xenon_opcode_generate(SPRINTLN));
    xenon_stack_append(&vm->code, xenon_opcode_generate(RET));

    xenon_vm_exec_wrapper(vm);

    vm_free(vm);

    return 0;
}
