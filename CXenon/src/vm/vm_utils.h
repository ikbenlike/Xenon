#ifndef __XENON_VM_UTILS_H_
    #define __XENON_VM_UTILS_H_

    xenon_vm_t *xenon_vm_generate(int startip, int stacksize, int codesize, int cstacksize);
    xenon_stack_item_t xenon_int_generate(int value);
    xenon_stack_item_t xenon_opcode_generate(enum xenon_opcodes opcode);
    xenon_stack_item_t xenon_float_generate(float value);
    xenon_stack_item_t xenon_string_generate(char *value);
    xenon_stack_item_t xenon_func_generate(int nargs, int nlocals, int addr);
    void xenon_stack_append(xenon_stack_t *stack, xenon_stack_item_t item);
    size_t xenon_print_xstring(xenon_string_t str);
    int xenon_print_stack_item(xenon_stack_item_t item);
    void vm_free(xenon_vm_t *vm);

#endif
