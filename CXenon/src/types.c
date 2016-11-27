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
    printf("%d", 1);
    memmove(str, str+1, strlen(str)+1);
    printf("%s", str);
    str[strlen(str) - 1] = '\0';
    printf("%s", str);
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
    printf("%s", str);
    printf("%s", tmp);
    return str;
}

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
