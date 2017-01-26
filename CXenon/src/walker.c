/*
*    CXenon VM v0.0.5
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "preprocessor.h"
#include "parser.h"
//#include "vm.h"
//#include "types.h"
#include "mpc/mpc.h"

int number_of_nodes(mpc_ast_t* t){
    if(t->children_num == 0){
        return 1;
    }
    if(t->children_num >= 1){
        int total = 1;
        for(int i = 0; i < t->children_num; i++){
            total = total + number_of_nodes(t->children[i]);
        }
        return total;
    }
    return 0;
}

/*int tree_walker(mpc_ast_t* tree){
    int stack_pointer = 0;
    struct stack_base* stack = calloc(1, DEFAULT_STACK_SIZE * sizeof(struct stack_base));
    int nodes_in_tree = number_of_nodes(tree);
    if(nodes_in_tree == 0){
        vm_add_opcode_to_stack(stack, HALT, 0);
    }
    else{
        for(int i = 0; i < nodes_in_tree; i++){
            //if(strcmp())
        }
    }
    return 0;
}*/

int main(int argc, char **argv){
    puts("entering main");
    if(argc < 2){
        puts("please provide a file to parse");
        return 1;
    }
    else{
        mpc_ast_t *ast = parse(argv[1], preprocessor(argv[1]));
        mpc_ast_print(ast);
        mpc_ast_delete(ast);
    }
    puts("exiting main");
    return 0;
}
