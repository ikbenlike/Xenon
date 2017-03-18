/*
*    CXenon VM v0.0.5
*/

// compile with: "gcc test.c vm.c types.c --std=c99 "

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "vm.h"
#include "types.h"

int main(void){
    VM *vm;
    struct stack_base loop[28];
    vm_add_opcode_to_stack(loop, CONST, 0);
    vm_add_int_to_stack(loop, 10, 1);
    vm_add_opcode_to_stack(loop, GSTORE, 2);
    vm_add_int_to_stack(loop, 0, 3);
    vm_add_opcode_to_stack(loop, CONST, 4);
    vm_add_int_to_stack(loop, 0, 5);
    vm_add_opcode_to_stack(loop, GSTORE, 6);
    vm_add_int_to_stack(loop, 1, 7);
    vm_add_opcode_to_stack(loop, GLOAD, 8);
    vm_add_int_to_stack(loop, 1, 9);
    vm_add_opcode_to_stack(loop, GLOAD, 10);
    vm_add_int_to_stack(loop, 0, 11);
    vm_add_opcode_to_stack(loop, ILT, 12);
    vm_add_opcode_to_stack(loop, BRF, 13);
    vm_add_int_to_stack(loop, 24, 14);
    vm_add_opcode_to_stack(loop, GLOAD, 15);
    vm_add_int_to_stack(loop, 1, 16);
    vm_add_opcode_to_stack(loop, CONST, 17);
    vm_add_int_to_stack(loop, 1, 18);
    vm_add_opcode_to_stack(loop, IADD, 19);
    vm_add_opcode_to_stack(loop, GSTORE, 20);
    vm_add_int_to_stack(loop, 1, 21);
    vm_add_opcode_to_stack(loop, BR, 22);
    vm_add_int_to_stack(loop, 8, 23);
    vm_add_opcode_to_stack(loop, GLOAD, 24);
    vm_add_int_to_stack(loop, 0, 25);
    vm_add_opcode_to_stack(loop, IPRINTLN, 26);
    vm_add_opcode_to_stack(loop, HALT, 27);
    vm = vm_create(loop, sizeof(loop), 2);
    vm_exec(vm, 0, false);
    vm_free(vm);
    struct stack_base hellonums[4];
    vm_add_opcode_to_stack(hellonums, CONST, 0);
    vm_add_int_to_stack(hellonums, 1234, 1);
    vm_add_opcode_to_stack(hellonums, IPRINTLN, 2);
    vm_add_opcode_to_stack(hellonums, HALT, 3);
    vm = vm_create(hellonums, sizeof(hellonums), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    struct stack_base f[17];
    vm_add_opcode_to_stack(f, CONST, 0);
    vm_add_int_to_stack(f, 10, 1);
    vm_add_opcode_to_stack(f, CALL, 2);
    vm_add_func_to_stack(f, 6, 1, 1, x_void, x_native_t, 3);
    /*vm_add_int_to_stack(f, 8, 3);
    vm_add_int_to_stack(f, 1, 4);
    vm_add_int_to_stack(f, 1, 5);*/
    vm_add_opcode_to_stack(f, IPRINTLN, 4);
    vm_add_opcode_to_stack(f, HALT, 5);
    vm_add_opcode_to_stack(f, ILOAD, 6);
    vm_add_int_to_stack(f, 0, 7);
    vm_add_opcode_to_stack(f, ISTORE, 8);
    vm_add_int_to_stack(f, 1, 9);
    vm_add_opcode_to_stack(f, ILOAD, 10);
    vm_add_int_to_stack(f, 1, 11);
    vm_add_opcode_to_stack(f, CONST, 12);
    vm_add_int_to_stack(f, 2, 13);
    vm_add_opcode_to_stack(f, IMUL, 14);
    vm_add_opcode_to_stack(f, RET, 15);
    vm = vm_create(f, sizeof(f), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    struct stack_base hello[4];
    vm_add_opcode_to_stack(hello, CONST, 0);
    vm_add_string_to_stack(hello, "Hello World!", 1);
    vm_add_opcode_to_stack(hello, SPRINTLN, 2);
    vm_add_opcode_to_stack(hello, HALT, 3);
    vm = vm_create(hello, sizeof(hello), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    char *tmpstr = calloc(1, 10 * sizeof(char));
    strcpy(tmpstr, "\"okay\n\n\"");
    struct stack_base hellochar[14];
    vm_add_opcode_to_stack(hellochar, CONST, 0);
    vm_add_string_to_stack(hellochar, "and now with chars: ", 1);
    vm_add_opcode_to_stack(hellochar, SPRINT, 2);
    vm_add_opcode_to_stack(hellochar, CONST, 3);
    vm_add_char_to_stack(hellochar, 'h', 4);
    vm_add_opcode_to_stack(hellochar, CPRINT, 5);
    vm_add_opcode_to_stack(hellochar, CONST, 6);
    vm_add_char_to_stack(hellochar, 'i', 7);
    vm_add_opcode_to_stack(hellochar, CPRINTLN, 8);
    vm_add_opcode_to_stack(hellochar, CONST, 9);
    vm_add_string_to_stack(hellochar, vm_parse_string(tmpstr), 10);
    vm_add_opcode_to_stack(hellochar, SPRINT, 11);
    vm_add_opcode_to_stack(hellochar, HALT, 12);
    vm = vm_create(hellochar, sizeof(hellochar), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    free(tmpstr);
    struct stack_base get_input[6];
    vm_add_opcode_to_stack(get_input, CONST, 0);
    vm_add_string_to_stack(get_input, "enter some input: ", 1);
    vm_add_opcode_to_stack(get_input, SPRINT, 2);
    vm_add_opcode_to_stack(get_input, INPUT, 3);
    vm_add_opcode_to_stack(get_input, SPRINTLN, 4);
    vm_add_opcode_to_stack(get_input, HALT, 5);
    vm = vm_create(get_input, sizeof(get_input), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    struct stack_base func_test[7];
    vm_add_opcode_to_stack(func_test, 18, 0);
    vm_add_func_to_stack(func_test, 3, 0, 1, x_void, x_native_t, 1);
    vm_add_opcode_to_stack(func_test, HALT, 2);
    vm_add_opcode_to_stack(func_test, CONST, 3);
    vm_add_int_to_stack(func_test, 10, 4);
    vm_add_opcode_to_stack(func_test, IPRINTLN, 5);
    vm_add_opcode_to_stack(func_test, RET, 6);
    vm = vm_create(func_test, sizeof(func_test), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    return 0;
}
