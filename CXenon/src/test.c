/*
*    CXenon VM v0.0.5
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#ifndef __VM_H_
    #include "vm/vm.h"
#endif
#ifndef __VM_UTILS_H_
    #include "vm/vm_utils.h"
#endif

int main(void){
    VM *vm;
    xenon_stack_vector loop;
    loop.size = 28;
    loop.cursor = 0;
    loop.vector = calloc(1, 28 * sizeof(xenon_stack_item));
    vm_add_opcode_to_stack(&loop, CONST);
    vm_add_int_to_stack(&loop, 10);
    vm_add_opcode_to_stack(&loop, GSTORE);
    vm_add_int_to_stack(&loop, 0);
    vm_add_opcode_to_stack(&loop, CONST);
    vm_add_int_to_stack(&loop, 0);
    vm_add_opcode_to_stack(&loop, GSTORE);
    vm_add_int_to_stack(&loop, 1);
    vm_add_opcode_to_stack(&loop, GLOAD);
    vm_add_int_to_stack(&loop, 1);
    vm_add_opcode_to_stack(&loop, GLOAD);
    vm_add_int_to_stack(&loop, 0);
    vm_add_opcode_to_stack(&loop, ILT);
    vm_add_opcode_to_stack(&loop, BRF);
    vm_add_int_to_stack(&loop, 24);
    vm_add_opcode_to_stack(&loop, GLOAD);
    vm_add_int_to_stack(&loop, 1);
    vm_add_opcode_to_stack(&loop, CONST);
    vm_add_int_to_stack(&loop, 1);
    vm_add_opcode_to_stack(&loop, IADD);
    vm_add_opcode_to_stack(&loop, GSTORE);
    vm_add_int_to_stack(&loop, 1);
    vm_add_opcode_to_stack(&loop, BR);
    vm_add_int_to_stack(&loop, 8);
    vm_add_opcode_to_stack(&loop, GLOAD);
    vm_add_int_to_stack(&loop, 0);
    vm_add_opcode_to_stack(&loop, IPRINTLN);
    vm_add_opcode_to_stack(&loop, HALT);
    vm = vm_create(loop, 2);
    vm_exec(vm, 0, false);
    vm_free(vm);
    xenon_stack_vector hellonums;
    hellonums.size = 4;
    hellonums.cursor = 0;
    hellonums.vector = calloc(1, sizeof(xenon_stack_item) * 4);
    vm_add_opcode_to_stack(&hellonums, CONST);
    vm_add_int_to_stack(&hellonums, 1234);
    vm_add_opcode_to_stack(&hellonums, IPRINTLN);
    vm_add_opcode_to_stack(&hellonums, HALT);
    vm = vm_create(hellonums, 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    xenon_stack_vector f;
    f.size = 17;
    f.cursor = 0;
    f.vector = calloc(1, sizeof(xenon_stack_item) * 17);
    vm_add_opcode_to_stack(&f, CONST);
    vm_add_int_to_stack(&f, 10);
    vm_add_opcode_to_stack(&f, CALL);
    vm_add_func_to_stack(&f, 6, 1, 1, x_void, x_native_t);
    /*vm_add_int_to_stack(f, 8, 3);
    vm_add_int_to_stack(f, 1, 4);
    vm_add_int_to_stack(f, 1, 5);*/
    vm_add_opcode_to_stack(&f, IPRINTLN);
    vm_add_opcode_to_stack(&f, HALT);
    vm_add_opcode_to_stack(&f, ILOAD);
    vm_add_int_to_stack(&f, 0);
    vm_add_opcode_to_stack(&f, ISTORE);
    vm_add_int_to_stack(&f, 1);
    vm_add_opcode_to_stack(&f, ILOAD);
    vm_add_int_to_stack(&f, 1);
    vm_add_opcode_to_stack(&f, CONST);
    vm_add_int_to_stack(&f, 2);
    vm_add_opcode_to_stack(&f, IMUL);
    vm_add_opcode_to_stack(&f, RET);
    vm = vm_create(f, 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    xenon_stack_vector hello;
    hello.size = 4;
    hello.cursor = 0;
    hello.vector = calloc(1, sizeof(xenon_stack_item) * 4);
    vm_add_opcode_to_stack(&hello, CONST);
    vm_add_string_to_stack(&hello, "Hello World!");
    vm_add_opcode_to_stack(&hello, SPRINTLN);
    vm_add_opcode_to_stack(&hello, HALT);
    vm = vm_create(hello, 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    char *tmpstr = calloc(1, 10 * sizeof(char));
    strcpy(tmpstr, "\"okay\n\n\"");
    xenon_stack_vector hellochar;
    hellochar.size = 14;
    hellochar.cursor = 0;
    hellochar.vector = calloc(1, sizeof(xenon_stack_item) * 14);
    vm_add_opcode_to_stack(&hellochar, CONST);
    vm_add_string_to_stack(&hellochar, "and now with chars: ");
    vm_add_opcode_to_stack(&hellochar, SPRINT);
    vm_add_opcode_to_stack(&hellochar, CONST);
    vm_add_char_to_stack(&hellochar, 'h');
    vm_add_opcode_to_stack(&hellochar, CPRINT);
    vm_add_opcode_to_stack(&hellochar, CONST);
    vm_add_char_to_stack(&hellochar, 'i');
    vm_add_opcode_to_stack(&hellochar, CPRINTLN);
    vm_add_opcode_to_stack(&hellochar, CONST);
    vm_add_string_to_stack(&hellochar, vm_parse_string(tmpstr));
    vm_add_opcode_to_stack(&hellochar, SPRINT);
    vm_add_opcode_to_stack(&hellochar, HALT);
    vm = vm_create(hellochar, 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    free(tmpstr);
    xenon_stack_vector get_input;
    get_input.size = 6;
    get_input.cursor = 0;
    get_input.vector = calloc(1, sizeof(xenon_stack_item) * 6);
    vm_add_opcode_to_stack(&get_input, CONST);
    vm_add_string_to_stack(&get_input, "enter some input: ");
    vm_add_opcode_to_stack(&get_input, SPRINT);
    vm_add_opcode_to_stack(&get_input, INPUT);
    vm_add_opcode_to_stack(&get_input, SPRINTLN);
    vm_add_opcode_to_stack(&get_input, HALT);
    vm = vm_create(get_input, 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    xenon_stack_vector func_test;
    func_test.size = 7;
    func_test.cursor = 0;
    func_test.vector = calloc(1, sizeof(xenon_stack_item) * 7);
    vm_add_opcode_to_stack(&func_test, 18);
    vm_add_func_to_stack(&func_test, 3, 0, 1, x_void, x_native_t);
    vm_add_opcode_to_stack(&func_test, HALT);
    vm_add_opcode_to_stack(&func_test, CONST);
    vm_add_int_to_stack(&func_test, 10);
    vm_add_opcode_to_stack(&func_test, IPRINTLN);
    vm_add_opcode_to_stack(&func_test, RET);
    vm = vm_create(func_test, 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    return 0;
}
