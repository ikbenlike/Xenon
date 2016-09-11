int vm_add_int_to_stack(struct stack_base* stack, int value, int i);
int vm_add_string_to_stack(struct stack_base* stack, int i, char* value, int len);
int vm_add_char_to_stack(struct stack_base* stack, char value, int i);
int vm_add_float_to_stack(struct stack_base* stack, char value, int i);
int vm_add_bool_to_stack(struct stack_base* stack, bool value, int i);
int vm_add_opcode_to_stack(struct stack_base* stack, int value, int i);
char* vm_get_type(struct stack_base* stack, int i);