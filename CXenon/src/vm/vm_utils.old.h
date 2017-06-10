/*
*   CXenon VM v0.0.5
*/
#ifndef __VM_UTILS_H_
    #define __VM_UTILS_H_
#endif

char* vm_parse_string(char* str);
int vm_check_stack_size(xenon_stack_vector *stack);
int vm_add_int_to_stack(xenon_stack_vector *stack, long int value);
xenon_stack_item vm_generate_int(long int value);
int vm_add_string_to_stack(xenon_stack_vector *stack, char* value);
xenon_stack_item vm_generate_string(char *value);
int vm_add_char_to_stack(xenon_stack_vector *stack, char value);
xenon_stack_item vm_generate_char(char value);
int vm_add_float_to_stack(xenon_stack_vector *stack, float value);
xenon_stack_item vm_generate_float(float value);
int vm_add_bool_to_stack(xenon_stack_vector *stack, bool value);
xenon_stack_item vm_generate_bool(bool value);
int vm_add_void_to_stack(xenon_stack_vector *stack);
xenon_stack_item vm_generate_void();
int vm_add_opcode_to_stack(xenon_stack_vector *stack, int value);
xenon_stack_item vm_generate_opcode(int value);
int vm_add_func_to_stack(xenon_stack_vector *stack, int addr, int nargs, int nlocals, int xret_t, int xfunc_t);
xenon_stack_item vm_generate_func(int addr, int nargs, int nlocals, int xret_t, int xfunc_t);
char* vm_get_type(xenon_stack_vector stack, int i);
