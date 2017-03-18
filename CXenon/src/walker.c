/*
*    CXenon VM v0.0.5
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef __PREPROCESSOR_H_
    #include "preprocessor.h"
#endif
#ifndef __PARSER_H_
    #include "parser.h"
#endif
#ifndef __VM_H_
    #include "vm.h"
#endif
#ifndef __TYPES_H_
    #include "types.h"
#endif
#ifndef __REPL_H_
    #include "repl.h"
#endif
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

int lexp_handler(mpc_ast_t node, xenon_stack_item* stack, int *stack_pointer){
    //int nodes_in_tree = number_of_nodes(*node.children);
    //printf("%d\n", *stack_pointer);
    if(node.children_num == 0){
        long int a = strtol(node.contents, NULL, 10);
        vm_add_opcode_to_stack(stack, ICONST, *stack_pointer += 1);
        vm_add_int_to_stack(stack, a, *stack_pointer += 1);
    }
    for(int i = 0; i < node.children_num; i++){
        if(strcmp(node.children[i]->tag, "term|factor|number|regex") == 0){
            if(strstr(node.children[i]->contents, ".") == 0){
                vm_add_opcode_to_stack(stack, FCONST, *stack_pointer += 1);
                vm_add_float_to_stack(stack, strtof(node.children[i]->contents, NULL), *stack_pointer += 1);
            }
            else {
                vm_add_opcode_to_stack(stack, ICONST, *stack_pointer += 1);
                vm_add_int_to_stack(stack, strtol(node.children[i]->contents, NULL, 10), *stack_pointer += 1);
            }
        }
        //else if(strcmp(node.children[i]->tag, ""))
    }
    return 0;
}

int math_handler(mpc_ast_t node, xenon_stack_item *stack, int *stack_pointer){
    /*puts("math_handler");
    //mpc_ast_print(node.children[0]);
    //int nodes_in_tree = number_of_nodes(*node.children);
    if(node.children == NULL){
        puts("yes");
    }*/
    lexp_handler(*node.children[0], stack, stack_pointer);
    return 0;
}

int function_handler(mpc_ast_t node, xenon_stack_item* stack, int *stack_pointer){
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
    vm_add_func_to_stack(stack, 0, narg, 0, ret, x_native_t, *stack_pointer += 1);
    return 0;
}

int tree_walker(mpc_ast_t* tree, xenon_stack_item* stack){
    //puts("tree_walker");
    int stack_pointer = 0;
    //printf("%d\n", stack_pointer);
    //xenon_stack_item* stack = calloc(1, DEFAULT_STACK_SIZE * sizeof(xenon_stack_item));
    int nodes_in_tree = number_of_nodes(tree);
    if(tree[0].children_num == 0){
        vm_add_opcode_to_stack(stack, HALT, stack_pointer++);
    }
    else{
        //puts("loop-1");
        for(int i = 0; i < tree[0].children_num; i++){
            //puts("loop");
            //puts(tree->children[i]->tag);
            if(strcmp(tree->children[i]->tag, "procedure|>") == 0){
                continue;
            }
            else if(strcmp(tree->children[i]->tag, "maths|>") == 0){
                math_handler(*tree->children[i], stack, &stack_pointer);
            }
        }
    }
    vm_add_opcode_to_stack(stack, HALT, stack_pointer += 1);
    //printf("%d\n", stack_pointer);
    return 0;
}

int main(int argc, char **argv){
    if (argc < 2){
        repl();
    }
    else {
        //puts("main");
        xenon_stack_item *stack = calloc(1, 1000*sizeof(xenon_stack_item));
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
        VM *vm = vm_create(stack, 1000, 0);
        mpc_ast_delete(ast);
        //printf("%s\n", vm_instructions[stack[0].data.anint].name);
        vm_exec(vm, 1, false);
        vm_free(vm);
        return 0;
    }
}
