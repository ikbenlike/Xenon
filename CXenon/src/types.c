/*
*    CXenon VM v0.0.5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "vm.h"

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

int vm_add_int_to_stack(struct stack_base *stack, int value, int i){
    stack[i].type = x_integer;
    stack[i].data.anint = value;
    return 0;
}

int vm_add_string_to_stack(struct stack_base *stack, char* value, int i){
    stack[i].type = x_string;
    stack[i].data.astring = value;
    return 0;
}

int vm_add_char_to_stack(struct stack_base *stack, char value, int i){
    stack[i].type = x_character;
    stack[i].data.achar = value;
    return 0;
}

int vm_add_float_to_stack(struct stack_base *stack, char value, int i){
    stack[i].type = x_floating;
    stack[i].data.afloat = value;
    return 0;
}

int vm_add_bool_to_stack(struct stack_base *stack, bool value, int i){
    stack[i].type = x_boolean;
    stack[i].data.abool = value;
    return 0;
}

int vm_add_void_to_stack(struct stack_base *stack, int i){
    stack[i].type = x_void;
    return 0;
}

int vm_add_opcode_to_stack(struct stack_base *stack, int value, int i){
    stack[i].type = x_opcode;
    stack[i].data.anint = value;
    return 0;
}

int vm_add_func_to_stack(struct stack_base *stack, int addr, int nargs, int nlocals, int xret_t, int xfunc_t, /*char *name,*/ int i){
    stack[i].type = x_function;
    stack[i].data.func.addr = addr;
    stack[i].data.func.nargs = nargs;
    stack[i].data.func.nlocals = nlocals;
    stack[i].data.func.xret_t = xret_t;
    stack[i].data.func.xfunc_t = xfunc_t;
    //stack[i].data.func.name = calloc(1, (strlen(name) + 1) * sizeof(char));
    //strncpy(stack[i].data.func.name, name, strlen(name) + 1);
    return 0;
}

int vm_get_type(struct stack_base *stack, int i){
    return stack[i].type;
}
