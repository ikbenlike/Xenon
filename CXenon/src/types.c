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

int vm_add_int_to_stack(xenon_stack_item *stack, long int value, int i){
    stack[i].type = x_integer;
    stack[i].data.anint = value;
    return 0;
}

xenon_stack_item vm_generate_int(long int value){
    xenon_stack_item item;
    item.type = x_integer;
    item.data.anint = value;
    return item;
}

int vm_add_string_to_stack(xenon_stack_item *stack, char* value, int i){
    stack[i].type = x_string;
    stack[i].data.astring = value;
    return 0;
}

xenon_stack_item vm_generate_string(char *value){
    xenon_stack_item item;
    item.type = x_string;
    item.data.astring = calloc(1, (strlen(value) + 1) * sizeof(char));
    strcpy(item.data.astring, value);
    return item;
}

int vm_add_char_to_stack(xenon_stack_item *stack, char value, int i){
    stack[i].type = x_character;
    stack[i].data.achar = value;
    return 0;
}

xenon_stack_item vm_generate_char(char value){
    xenon_stack_item item;
    item.type = x_character;
    item.data.achar = value;
    return item;
}

int vm_add_float_to_stack(xenon_stack_item *stack, float value, int i){
    stack[i].type = x_floating;
    stack[i].data.afloat = value;
    return 0;
}

xenon_stack_item vm_generate_float(float value){
    xenon_stack_item item;
    item.type = x_floating;
    item.data.afloat = value;
    return item;
}

int vm_add_bool_to_stack(xenon_stack_item *stack, bool value, int i){
    stack[i].type = x_boolean;
    stack[i].data.abool = value;
    return 0;
}

xenon_stack_item vm_generate_bool(bool value){
    xenon_stack_item item;
    item.type = x_boolean;
    item.data.abool = value;
    return item;
}

int vm_add_void_to_stack(xenon_stack_item *stack, int i){
    stack[i].type = x_void;
    return 0;
}

xenon_stack_item vm_generate_void(){
    xenon_stack_item item;
    item.type = x_void;
    return item;
}

int vm_add_opcode_to_stack(xenon_stack_item *stack, int value, int i){
    stack[i].type = x_opcode;
    stack[i].data.anint = value;
    return 0;
}

xenon_stack_item vm_generate_opcode(int value){
    xenon_stack_item item;
    item.type = x_opcode;
    item.data.anint = value;
    return item;
}

int vm_add_func_to_stack(xenon_stack_item *stack, int addr, int nargs, int nlocals, int xret_t, int xfunc_t, int i){
    stack[i].type = x_function;
    stack[i].data.func.addr = addr;
    stack[i].data.func.nargs = nargs;
    stack[i].data.func.nlocals = nlocals;
    stack[i].data.func.xret_t = xret_t;
    stack[i].data.func.xfunc_t = xfunc_t;
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

int vm_get_type(xenon_stack_item *stack, int i){
    return stack[i].type;
}
