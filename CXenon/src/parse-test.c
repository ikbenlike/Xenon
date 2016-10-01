/*
    CXenon VM v0.0.5
*/

// compile with: gcc mpc/mpc.c parser.c parse-test.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "parser.h"

int main(int argc, char **argv){
    if (argc < 2){
        puts("please provide a file to parse");
        return 0;
    }
    else {
        parse(argv[1]);
        return 0;
    }
}
