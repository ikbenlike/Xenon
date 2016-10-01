/*
*    CXenon VM v0.0.5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "vm.h"

int vm_add_int_to_stack(struct stack_base* stack, int value, int i){
    strcpy(stack[i].type, "int");
    stack[i].data.anint = value;
    return 0;
}

int vm_add_string_to_stack(struct stack_base* stack, char* value, int i){
    strcpy(stack[i].type, "string");
    stack[i].data.astring = value;
    return 0;
}

int vm_add_char_to_stack(struct stack_base* stack, char value, int i){
    strcpy(stack[i].type, "char");
    stack[i].data.achar = value;
    return 0;
}

int vm_add_float_to_stack(struct stack_base* stack, char value, int i){
    strcpy(stack[i].type, "float");
    stack[i].data.afloat = value;
    return 0;
}

int vm_add_bool_to_stack(struct stack_base* stack, bool value, int i){
    strcpy(stack[i].type, "bool");
    stack[i].data.abool = value;
    return 0;
}

int vm_add_opcode_to_stack(struct stack_base* stack, int value, int i){
    strcpy(stack[i].type, "opcode");
    stack[i].data.anint = value;
    return 0;
}

char* vm_get_type(struct stack_base* stack, int i){
    return stack[i].type;
}
