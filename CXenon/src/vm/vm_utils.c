#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "vm.h"
#include "vm_utils.h"

/*
    xenon_vm_t *xenon_vm_generate(int startip, int stacksize, int codesize);

    This function allocates and populates a xenon_vm_t struct and returns a 
    pointer to it. It sets the `startip` to `startip`, and the `stacksize` to 
    `stacksize`. If `codesize` is 0, it uses `stacksize * 1.5` as `codesize`.

    Return type:
    NULL on error; `xenon_vm_t*` on succes.
*/

xenon_vm_t *xenon_vm_generate(int startip, int stacksize, int codesize){
    xenon_vm_t *vm = calloc(1, sizeof(xenon_vm_t));
    if(vm == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    vm->stack.stack = calloc(stacksize, sizeof(xenon_stack_item_t));
    if(vm->stack.stack == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    if(codesize == 0){
        codesize = stacksize * 1.5;
    }
    vm->code.stack = calloc(codesize, sizeof(xenon_stack_item_t));
    if(vm->code.stack == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    return vm;
}
