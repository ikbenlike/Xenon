/*
*   CXenon VM v0.0.5
*/
#ifndef __TYPES_H_
    #define __TYPES_H_
#endif

char* vm_parse_string(char* str);
int vm_add_int_to_stack(xenon_stack_item* stack, long int value, int i);
xenon_stack_item vm_generate_int(long int value);
int vm_add_string_to_stack(xenon_stack_item* stack, char* value, int i);
xenon_stack_item vm_generate_string(char *value);
int vm_add_char_to_stack(xenon_stack_item* stack, char value, int i);
xenon_stack_item vm_generate_char(char value);
int vm_add_float_to_stack(xenon_stack_item* stack, float value, int i);
xenon_stack_item vm_generate_float(float value);
int vm_add_bool_to_stack(xenon_stack_item* stack, bool value, int i);
xenon_stack_item vm_generate_bool(bool value);
int vm_add_void_to_stack(xenon_stack_item *stack, int i);
xenon_stack_item vm_generate_void();
int vm_add_opcode_to_stack(xenon_stack_item* stack, int value, int i);
xenon_stack_item vm_generate_opcode(int value);
int vm_add_func_to_stack(xenon_stack_item* stack, int addr, int nargs, int nlocals, int xret_t, int xfunc_t, int i);
xenon_stack_item vm_generate_func(int addr, int nargs, int nlocals, int xret_t, int xfunc_t);
char* vm_get_type(xenon_stack_item* stack, int i);
