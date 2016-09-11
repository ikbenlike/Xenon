/*
*    CXenon VM v0.0.3
*/

// compile with: "gcc test.c vm.c -std=c99 "

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "vm.h"
#include "types.h"

int main(void){
    /*struct stack_base loop[] = {
        {.data.anint = ICONST}, {.data.anint = 10},
        {.data.anint = IGSTORE}, {.data.anint = 0},
        {.data.anint = ICONST}, {.data.anint = 0},
        {.data.anint = IGSTORE}, {.data.anint = 1},
        {.data.anint = IGLOAD}, {.data.anint = 1},
        {.data.anint = IGLOAD}, {.data.anint = 0},
        {.data.anint = ILT},
        {.data.anint = BRF}, {.data.anint = 24},
        {.data.anint = IGLOAD}, {.data.anint = 1},
        {.data.anint = ICONST}, {.data.anint = 1},
        {.data.anint = IADD},
        {.data.anint = IGSTORE}, {.data.anint = 1},
        {.data.anint = BR}, {.data.anint = 8},
        {.data.anint = IGLOAD}, {.data.anint = 0},
        {.data.anint = IPRINTLN},
        {.data.anint = HALT}
    };*
    struct stack_base loop[28];
    vm_add_opcode_to_stack(loop, ICONST, 0);
    vm_add_int_to_stack(loop, 10, 1);
    vm_add_opcode_to_stack(loop, IGSTORE, 2);
    vm_add_int_to_stack(loop, 0, 3);
    vm_add_opcode_to_stack(loop, ICONST, 4);
    vm_add_int_to_stack(loop, 0, 5);
    vm_add_opcode_to_stack(loop, IGSTORE, 6);
    vm_add_int_to_stack(loop, 1, 7);
    vm_add_opcode_to_stack(loop, IGLOAD, 8);
    vm_add_int_to_stack(loop, 1, 9);
    vm_add_opcode_to_stack(loop, IGLOAD, 10);
    vm_add_int_to_stack(loop, 0, 11);
    vm_add_opcode_to_stack(loop, ILT, 12);
    vm_add_opcode_to_stack(loop, BRF, 13);
    vm_add_int_to_stack(loop, 24, 14);
    vm_add_opcode_to_stack(loop, IGLOAD, 15);
    vm_add_int_to_stack(loop, 1, 16);
    vm_add_opcode_to_stack(loop, ICONST, 17);
    vm_add_int_to_stack(loop, 1, 18);
    vm_add_opcode_to_stack(loop, IADD, 19);
    vm_add_opcode_to_stack(loop, IGSTORE, 20);
    vm_add_int_to_stack(loop, 1, 21);
    vm_add_opcode_to_stack(loop, BR, 22);
    vm_add_int_to_stack(loop, 8, 23);
    vm_add_opcode_to_stack(loop, IGLOAD, 24);
    vm_add_int_to_stack(loop, 0, 25);
    vm_add_opcode_to_stack(loop, IPRINTLN, 26);
    vm_add_opcode_to_stack(loop, HALT, 27);
    VM *vm = vm_create(loop, sizeof(loop), 2);
    vm_exec(vm, 0, false);
    //vm_print_data(vm->globals, vm->nglobals);
    vm_free(vm);
    /*struct stack_base hellonums[]; = {
        {.anint = ICONST}, {.anint = 1234},
        {.anint = IPRINTLN},
        {.anint = HALT}
    };
    struct stack_base hellonums[4];
    vm_add_opcode_to_stack(hellonums, ICONST, 0);
    vm_add_int_to_stack(hellonums, 1234, 1);
    vm_add_opcode_to_stack(hellonums, IPRINTLN, 2);
    vm_add_opcode_to_stack(hellonums, HALT, 3);
    vm = vm_create(hellonums, sizeof(hellonums), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);*/
    /*struct stack_base f[] = {
        {.data.anint = ICONST}, {.data.anint = 10},
        {.data.anint = CALL}, {.data.anint = 8}, {.data.anint = 1}, {.data.anint = 1},
        {.data.anint = IPRINTLN},
        {.data.anint = HALT},
        {.data.anint = ILOAD}, {.data.anint = 0},
        {.data.anint = ISTORE}, {.data.anint = 1},
        {.data.anint = ILOAD}, {.data.anint = 1},
        {.data.anint = ICONST}, {.data.anint = 2},
        {.data.anint = IMUL},
        {.data.anint = RET}
    };
    vm = vm_create(f, sizeof(f), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    struct stack_base hello[] = {
        {.data.anint = SCONST}, {.data.astring.content = "Hello world!"},
        {.data.anint = SPRINTLN},
        {.data.anint = HALT}
    };*/
    struct stack_base* hello;
    hello = malloc(4 * sizeof(struct stack_base));
    vm_add_opcode_to_stack(hello, SCONST, 0);
    vm_add_string_to_stack(hello, 1, "Hello World!", 12);
    vm_add_opcode_to_stack(hello, SPRINTLN, 2);
    vm_add_opcode_to_stack(hello, HALT, 3);
    VM* vm = vm_create(hello, sizeof(hello), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    return 0;
}
