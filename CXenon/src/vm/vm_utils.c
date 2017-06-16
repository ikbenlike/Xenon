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
    vm->stack.len = stacksize;
    if(codesize == 0){
        codesize = stacksize * 1.5;
    }
    vm->code.stack = calloc(codesize, sizeof(xenon_stack_item_t));
    if(vm->code.stack == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    vm->code.len = codesize;
    return vm;
}

xenon_stack_item_t xenon_int_generate(int value){
    xenon_stack_item_t i;
    i.type = integer;
    i.integer = value;
    return i;
}

xenon_stack_item_t xenon_opcode_generate(enum xenon_opcodes opcode){
    xenon_stack_item_t i;
    i.type = opcode;
    i.opcode = opcode;
    return i;
}

xenon_stack_item_t xenon_float_generate(float value){
    xenon_stack_item_t i;
    i.type = floating;
    i.floating = value;
    return i;
}

xenon_stack_item_t xenon_string_generate(char *value){
    xenon_stack_item_t i;
    i.type = string;
    i.string.len = strlen(value);
    i.string.contents = calloc(i.string.len, sizeof(char));
    strncpy(i.string.contents, value, i.string.len);
    return i;
}

inline void xenon_stack_append(xenon_stack_t stack, xenon_stack_item_t item){
    stack.stack[stack.cursor++] = item;
    return;
}

size_t xenon_print_xstring(xenon_string_t str){
    size_t i = 0;
    for( ; i < str.len; i++){
        putchar(str.contents[i]);
    }
    return i;
}
