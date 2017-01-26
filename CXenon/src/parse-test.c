/*
    CXenon VM v0.0.5
*/

// compile with: gcc mpc/mpc.c parser.c parse-test.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "mpc/mpc.h"
#include "parser.h"
#include "preprocessor.h"

int main(int argc, char **argv){
    if (argc < 2){
        puts("please provide a file to parse");
        return 1;
    }
    else {
        mpc_ast_t* ast = parse(argv[1], preprocessor(argv[1]));
        mpc_ast_print(ast);
        mpc_ast_delete(ast);
        return 0;
    }
}
