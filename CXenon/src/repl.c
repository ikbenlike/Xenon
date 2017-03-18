#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#ifndef __VM_H_
    #include "vm.h"
#endif
#ifndef __PARSER_H_
    #include "parser.h"
#endif
#ifndef __PREPROCESSOR_H_
    #include "preprocessor.h"
#endif
#ifndef __REPL_H_
    #include "repl.h"
#endif

int repl(){
    char *a = calloc(1, 1000 * sizeof(char));
    while(1){
        printf("Xenon> ");
        input(a, 1000);
        char *b = preprocessor(a);
        mpc_ast_t *ast = parse("stdin", b);
        free(b);
        if(ast != NULL){
            mpc_ast_print(ast);
            xenon_stack_item *stack = calloc(1, 1000*sizeof(xenon_stack_item));
            VM *vm = vm_create(stack, 1000, 0);
            vm_free(vm);
            mpc_ast_delete(ast);
        }
    }
    free(a);
    return 0;
}
