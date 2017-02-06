#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parser.h"
#include "preprocessor.h"
#include "repl.h"

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
            mpc_ast_delete(ast);
        }
    }
    free(a);
    return 0;
}
