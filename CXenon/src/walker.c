#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "parser.h"
#include "mpc/mpc.h"

int number_of_nodes(mpc_ast_t* t) {
    if (t->children_num == 0) { return 1; }
    if (t->children_num >= 1) {
        int total = 1;
        for (int i = 0; i < t->children_num; i++) {
            total = total + number_of_nodes(t->children[i]);
        }
        return total;
    }
    return 0;
}

int main(int argc, char **argv){
    if (argc < 2){
        puts("please provide a file to parse");
        return 1;
    }
    else {
        mpc_ast_print(parse(argv[1]));
    }
    return 0;
}
