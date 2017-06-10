/*
*    CXenon VM v0.0.5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#ifndef __VM_H_
    #include "vm.h"
#endif

char* vm_parse_string(char* str){
    //printf("%d", 1);
    memmove(str, str+1, strlen(str)+1);
    //printf("%s", str);
    str[strlen(str) - 1] = '\0';
    //printf("%s", str);
    char* tmp = malloc((strlen(str)+1) * sizeof(char));
    strncpy(tmp, str, strlen(str)+1);
    for(int i = 1; i < strlen(str); i++){
        if(str[i] == '\\'){
            if(str[i-1] != '\\'){
                if(str[i+1] == 'n'){
                    str[i] = '\n';
                    str[i+1] = '\0';
                }
                else if(str[i+1] == 't'){
                    str[i] = '\t';
                    str[i+1] = '\0';
                }
                else if(str[i+1] == 'b'){
                    str[i] = '\b';
                    str[i+1] = '\0';
                }
                memmove(tmp, tmp + i, strlen(tmp)+1);
                strcat(str, tmp);
            }
        }
    }
    //printf("%s", str);
    //printf("%s", tmp);
    free(tmp);
    return str;
}

int vm_check_stack_size(xenon_stack_vector *stack){
    if(stack->size - stack->cursor <= 10){
        stack->size += 100;
        xenon_stack_item *tmp = realloc(stack->vector, stack->size);
        if(tmp == NULL){
            puts("A fatal error occured while resizing the stack. Check how much free RAM you have.");
            exit(1);
        }
        else{
            stack->vector = tmp;
        }
    }
    return 0;
}

int vm_add_int_to_stack(xenon_stack_vector *stack, long int value){
    //vm_check_stack_size(stack);
    //printf("%d\n", stack->cursor);
    stack->vector[stack->cursor].type = x_integer;
    stack->vector[stack->cursor++].data.anint = value;
    //printf("%i :: %li\n", stack->cursor, value);
    return 0;
}

xenon_stack_item vm_generate_int(long int value){
    xenon_stack_item item;
    item.type = x_integer;
    item.data.anint = value;
    return item;
}

int vm_add_string_to_stack(xenon_stack_vector *stack, char* value){
    vm_check_stack_size(stack);
    stack->vector[stack->cursor].type = x_string;
    stack->vector[stack->cursor++].data.astring = value;
    return 0;
}

xenon_stack_item vm_generate_string(char *value){
    xenon_stack_item item;
    item.type = x_string;
    item.data.astring = calloc(1, (strlen(value) + 1) * sizeof(char));
    strcpy(item.data.astring, value);
    return item;
}

int vm_add_char_to_stack(xenon_stack_vector *stack, char value){
    vm_check_stack_size(stack);
    stack->vector[stack->cursor].type = x_character;
    stack->vector[stack->cursor++].data.achar = value;
    return 0;
}

xenon_stack_item vm_generate_char(char value){
    xenon_stack_item item;
    item.type = x_character;
    item.data.achar = value;
    return item;
}

int vm_add_float_to_stack(xenon_stack_vector *stack, float value){
    vm_check_stack_size(stack);
    stack->vector[stack->cursor].type = x_floating;
    stack->vector[stack->cursor++].data.afloat = value;
    return 0;
}

xenon_stack_item vm_generate_float(float value){
    xenon_stack_item item;
    item.type = x_floating;
    item.data.afloat = value;
    return item;
}

int vm_add_bool_to_stack(xenon_stack_vector *stack, bool value){
    vm_check_stack_size(stack);
    stack->vector[stack->cursor].type = x_boolean;
    stack->vector[stack->cursor++].data.abool = value;
    return 0;
}

xenon_stack_item vm_generate_bool(bool value){
    xenon_stack_item item;
    item.type = x_boolean;
    item.data.abool = value;
    return item;
}

int vm_add_void_to_stack(xenon_stack_vector *stack){
    vm_check_stack_size(stack);
    stack->vector[stack->cursor++].type = x_void;
    return 0;
}

xenon_stack_item vm_generate_void(){
    xenon_stack_item item;
    item.type = x_void;
    return item;
}

int vm_add_opcode_to_stack(xenon_stack_vector *stack, long int value){
    //vm_check_stack_size(stack);
    stack->vector[stack->cursor].type = x_opcode;
    stack->vector[stack->cursor++].data.anint = value;
    return 0;
}

xenon_stack_item vm_generate_opcode(int value){
    xenon_stack_item item;
    item.type = x_opcode;
    item.data.anint = value;
    return item;
}

int vm_add_func_to_stack(xenon_stack_vector *stack, int addr, int nargs, int nlocals, int xret_t, int xfunc_t){
    vm_check_stack_size(stack);
    stack->vector[stack->cursor].type = x_function;
    stack->vector[stack->cursor].data.func.addr = addr;
    stack->vector[stack->cursor].data.func.nargs = nargs;
    stack->vector[stack->cursor].data.func.nlocals = nlocals;
    stack->vector[stack->cursor].data.func.xret_t = xret_t;
    stack->vector[stack->cursor++].data.func.xfunc_t = xfunc_t;
    return 0;
}

xenon_stack_item vm_generate_func(int addr, int nargs, int nlocals, int xret_t, int xfunc_t){
    xenon_stack_item item;
    item.type = x_function;
    item.data.func.addr = addr;
    item.data.func.nargs = nargs;
    item.data.func.nlocals = nlocals;
    item.data.func.xret_t = xret_t;
    item.data.func.xfunc_t = xfunc_t;
    return item;
}

int vm_get_type(xenon_stack_vector stack, int i){
    return stack.vector[i].type;
}
