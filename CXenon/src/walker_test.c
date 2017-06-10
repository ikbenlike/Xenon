#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef __PREPROCESSOR_H_
    #include "preprocessor/preprocessor.h"
#endif
#ifndef __PARSER_H_
    #include "parser/parser.h"
#endif
#ifndef __VM_H_
    #include "vm/vm.h"
#endif
#ifndef __VM_UTILS_H_
    #include "vm/vm_utils.h"
#endif
#ifndef __REPL_H_
    #include "repl/repl.h"
#endif
#ifndef __WALKER_H_
    #include "walker/walker.h"
#endif
#include "mpc/mpc.h"



int main(int argc, char **argv){
    if (argc < 2){
        repl();
    }
    else {
        //puts("main");
        xenon_stack_vector stack;
        stack.size = 1000;
        stack.cursor = 0;
        stack.vector = calloc(1, 1000 * sizeof(xenon_stack_item));
        char *a = calloc(1, 1000*sizeof(char));
        finput(a, argv[1], 1000*sizeof(char));
        printf("%s\n", a);
        char *b = preprocessor(a);
        puts(b);
        free(a);
        mpc_ast_t* ast = parse(argv[1], b);
        free(b);
        mpc_ast_print(ast);
        //puts(ast->children[1]->tag);
        tree_walker(ast, stack);
        VM *vm = vm_create(stack, 0);
        mpc_ast_delete(ast);
        //printf("%s\n", vm_instructions[stack[0].data.anint].name);
        vm_exec(vm, 1, false);
        vm_free(vm);
        return 0;
    }
}
