/*
*   CXenon VM v0.0.5
*/
#ifndef __TYPES_H_
    #define __TYPES_H_
#endif

char* vm_parse_string(char* str);
int vm_add_int_to_stack(struct stack_base* stack, long int value, int i);
int vm_add_string_to_stack(struct stack_base* stack, char* value, int i);
int vm_add_char_to_stack(struct stack_base* stack, char value, int i);
int vm_add_float_to_stack(struct stack_base* stack, char value, int i);
int vm_add_bool_to_stack(struct stack_base* stack, bool value, int i);
int vm_add_opcode_to_stack(struct stack_base* stack, int value, int i);
int vm_add_void_to_stack(struct stack_base *stack, int i);
int vm_add_func_to_stack(struct stack_base* stack, int addr, int nargs, int nlocals, int xret_t, int xfunc_t, /*char *name,*/ int i);
//struct stack_base *vm_get_func_body(struct stack_base *stack, int i);
char* vm_get_type(struct stack_base* stack, int i);
