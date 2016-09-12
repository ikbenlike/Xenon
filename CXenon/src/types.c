/*
*    CXenon VM v0.0.3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "vm.h"

char* new_string(char* the_shit, int len) {
    char* the_string = (char*)malloc(sizeof(char)*len+1);
    for (int i  = 0; i < len; i++) { // not equal to
        the_string[i] = the_shit[i];
    }
    the_string[len] = '\0';
    printf("%s\n", the_string);
    return the_string;
}

int vm_add_int_to_stack(struct stack_base* stack, int value, int i){
    strcpy(stack[i].type, "int");
    stack[i].data.anint = value;
    return 0;
}

int vm_add_string_to_stack(struct stack_base* stack, int i, char* value, int len){
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
}

int vm_add_opcode_to_stack(struct stack_base* stack, int value, int i){
    strcpy(stack[i].type, "opcode");
    stack[i].data.anint = value;
}

char* vm_get_type(struct stack_base* stack, int i){
    return stack[i].type;
}
