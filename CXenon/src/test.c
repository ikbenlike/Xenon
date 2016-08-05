/*
*    CXenon VM v0.0.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "vm.h"

int main(void){
    struct stack_base loop[] = {
        {.anint = ICONST}, {.anint = 10},
        {.anint = IGSTORE}, {.anint = 0},
        {.anint = ICONST}, {.anint = 0},
        {.anint = IGSTORE}, {.anint = 1},
        {.anint = IGLOAD}, {.anint = 1},
        {.anint = IGLOAD}, {.anint = 0},
        {.anint = ILT},
        {.anint = BRF}, {.anint = 24},
        {.anint = IGLOAD}, {.anint = 1},
        {.anint = ICONST}, {.anint = 1},
        {.anint = IADD},
        {.anint = IGSTORE}, {.anint = 1},
        {.anint = BR}, {.anint = 8},
        {.anint = IGLOAD}, {.anint = 0},
        {.anint = IPRINTLN},
        {.anint = HALT}
    };
    VM *vm = vm_create(loop, sizeof(loop), 2);
    vm_exec(vm, 0, false);
    vm_print_data(vm->globals, vm->nglobals);
    vm_free(vm);
    struct stack_base hellonums[] = {
        {.anint = ICONST}, {.anint = 1234},
        {.anint = IPRINTLN},
        {.anint = HALT}
    };
    vm = vm_create(hellonums, sizeof(hellonums), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    struct stack_base f[] = {
        {.anint = ICONST}, {.anint = 10},
        {.anint = CALL}, {.anint = 8}, {.anint = 1}, {.anint = 1},
        {.anint = IPRINTLN},
        {.anint = HALT},
        {.anint = ILOAD}, {.anint = 0},
        {.anint = ISTORE}, {.anint = 1},
        {.anint = ILOAD}, {.anint = 1},
        {.anint = ICONST}, {.anint = 2},
        {.anint = IMUL},
        {.anint = RET}
    };
    vm = vm_create(f, sizeof(f), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    struct stack_base hello[] = {
        {.anint = SCONST}, {.astring = "Hello world!"},
        {.anint = SPRINTLN},
        {.anint = HALT}
    };
    vm = vm_create(hello, sizeof(hello), 0);
    vm_exec(vm, 0, false);
    vm_free(vm);
    return 0;
}
