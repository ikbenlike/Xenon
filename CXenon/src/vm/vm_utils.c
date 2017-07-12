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

xenon_vm_t *xenon_vm_generate(int startip, int stacksize, int codesize, int cstacksize){
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
    if(cstacksize == 0){
        cstacksize = stacksize * 0.5;
    }
    vm->ctx = calloc(cstacksize, sizeof(xenon_context_t));
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

xenon_stack_item_t xenon_bool_generate(bool value){
    xenon_stack_item_t i;
    i.type = boolean;
    i.boolean = value;
    return i;
}

xenon_stack_item_t xenon_func_generate(int nargs, int nlocals, int addr){
    xenon_stack_item_t i;
    i.type = function;
    i.func.nargs = nargs;
    i.func.nlocals = nlocals;
    i.func.addr = addr;
    return i;
}

void xenon_stack_append(xenon_stack_t *stack, xenon_stack_item_t item){
    stack->stack[stack->cursor++] = item;
    if(((float)stack->cursor / (float)stack->len) * 100 > 80){
        void *tmp = realloc(stack->stack, (int)(stack->len * 1.75));
        if(tmp == NULL){
            puts("Xenon: invalid stack resize");
            return;
        }
        else {
            stack->stack = tmp;
        }
    }
    return;
}

size_t xenon_print_xstring(xenon_string_t str){
    size_t i = 0;
    for( ; i < str.len; i++){
        putchar(str.contents[i]);
    }
    return i;
}

int xenon_print_stack_item(xenon_stack_item_t item){
    if(item.type == integer){
        printf("%d\n", item.integer);
    }
    else if(item.type == floating){
        printf("%f\n", item.floating);
    }
    else if(item.type == boolean){
        if(item.boolean){
            puts("true");
        }
        else {
            puts("false");
        }
    }
    else if(item.type == character){
        printf("%c\n", item.character);
    }
    else if(item.type == string){
        xenon_print_xstring(item.string);
    }
    else if(item.type == function){
        printf("function {\n\tnargs: %d\n\tnlocals: %d\n\taddr: %d\n}\n", item.func.nargs, item.func.nlocals, item.func.addr);
    }
    return 0;
}

void vm_free(xenon_vm_t *vm){
    free(vm->stack.stack);
    free(vm->code.stack);
    free(vm->ctx);
    free(vm);
}
