/*
    CXenon VM v0.0.5
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "mpc/mpc.h"
#include "parser/parser.h"
#include "preprocessor/preprocessor.h"
#include "repl/repl.h"

int main(int argc, char **argv){
    if (argc < 2){
        repl();
    }
    else {
        char *a = calloc(1, 1000*sizeof(char));
        printf("%s\n", finput(a, argv[1], 1000*sizeof(char)));
        char *b = preprocessor(a);
        free(a);
        mpc_ast_t* ast = parse(argv[1], b);
        free(b);
        mpc_ast_print(ast);
        mpc_ast_delete(ast);
        return 0;
    }
}
