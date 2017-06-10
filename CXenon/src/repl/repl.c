#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#ifndef __VM_H_
    #include "../vm/vm.h"
#endif
#ifndef __VM_UTILS_H_
    #include "../vm/vm_utils.h"
#endif
#ifndef __PARSER_H_
    #include "../parser/parser.h"
#endif
#ifndef __PREPROCESSOR_H_
    #include "../preprocessor/preprocessor.h"
#endif
#ifndef __REPL_H_
    #include "repl.h"
#endif
#ifndef __WALKER_H_
    #include "../walker/walker.h"
#endif

int repl(){
    char *a = calloc(1, 1000 * sizeof(char));
    xenon_stack_vector stack;
    stack.size = 1000;
    while(1){
        stack.vector = calloc(1, 1000 * sizeof(xenon_stack_item));
        printf("Xenon> ");
        input(a, 1000);
        if(strcmp(a, ".exit") == 0){
            return 0;
        }
        char *b = preprocessor(a);
        mpc_ast_t *ast = parse("stdin", b);
        free(b);
        if(ast != NULL){
            stack.cursor = 0;
            mpc_ast_print(ast);
            //vm_add_opcode_to_stack(&stack, HALT);
            tree_walker(ast, stack);
            vm_add_opcode_to_stack(&stack, CONST);
            vm_add_int_to_stack(&stack, 10);
            printf("%i\n", stack.cursor);
            VM *vm = vm_create(stack, 0);
            mpc_ast_delete(ast);
            vm_exec(vm, 0, false);
            vm_free(vm);
        }
        if(stack.vector != NULL){
            free(stack.vector);
        }
    }
    free(a);
    return 0;
}
