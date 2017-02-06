/*
*    CXenon VM v0.0.5
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "preprocessor.h"
#include "parser.h"
#include "vm.h"
#include "types.h"
#include "repl.h"
#include "mpc/mpc.h"

int number_of_nodes(mpc_ast_t* tree){
    if(tree->children_num == 0){
        return 1;
    }
    if(tree->children_num >= 1){
        int total = 1;
        for(int i = 0; i < tree->children_num; i++){
            total = total + number_of_nodes(tree->children[i]);
        }
        return total;
    }
    return 0;
}

int function_handler(mpc_ast_t node, int stack_pointer){
    int nodes_in_tree = number_of_nodes(*node.children);
    int narg = 0;
    int ret = x_void;
    if(nodes_in_tree == 6){
        narg = 0;
    }
    else{
        narg = nodes_in_tree - 6;
    }
    if(strcmp(node.children[0]->contents, "int") == 0){
        ret = x_integer;
    }
    else if(strcmp(node.children[0]->contents, "float") == 0){
        ret = x_floating;
    }
    else if(strcmp(node.children[0]->contents, "char") == 0){
        ret = x_character;
    }
    else if(strcmp(node.children[0]->contents, "str") == 0){
        ret = x_string;
    }
    else if(strcmp(node.children[0]->contents, "bool") == 0){
        ret = x_boolean;
    }
    else if(strcmp(node.children[0]->contents, "void") == 0){
        ret = x_void;
    }
    //vm_add_func_to_stack(/**/, 0, narg, 0, ret, x_native_t, stack_pointer);
    return 0;
}

int tree_walker(mpc_ast_t* tree){
    int stack_pointer = 0;
    struct stack_base* stack = calloc(1, DEFAULT_STACK_SIZE * sizeof(struct stack_base));
    int nodes_in_tree = number_of_nodes(tree);
    if(nodes_in_tree == 0){
        vm_add_opcode_to_stack(stack, HALT, stack_pointer++);
    }
    else{
        for(int i = 0; i < nodes_in_tree; i++){
            if(strcmp(tree->children[i]->tag, "procedure|>") == 0){

            }
        }
    }
    return 0;
}

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
        puts(ast->children[1]->tag);
        mpc_ast_delete(ast);
        return 0;
    }
}
