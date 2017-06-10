/*
*    CXenon VM v0.0.5
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef __PREPROCESSOR_H_
    #include "../preprocessor/preprocessor.h"
#endif
#ifndef __PARSER_H_
    #include "../parser/parser.h"
#endif
#ifndef __VM_H_
    #include "../vm/vm.h"
#endif
#ifndef __VM_UTILS_H_
    #include "../vm/vm_utils.h"
#endif
#ifndef __REPL_H_
    #include "../repl/repl.h"
#endif
#ifndef __WALKER_H_
    #include "../walker/walker.h"
#endif
#include "../mpc/mpc.h"

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

int lexp_handler(mpc_ast_t node, xenon_stack_vector stack){
    //int nodes_in_tree = number_of_nodes(*node.children);
    //printf("%d\n", *stack_pointer);
    if(node.children_num == 0){
        long int a = strtol(node.contents, NULL, 10);
        //printf("%s\n", node.contents);
        vm_add_opcode_to_stack(&stack, CONST);
        vm_add_int_to_stack(&stack, a);
        puts("done thing");
    }
    for(int i = 0; i < node.children_num; i++){
        if(strcmp(node.children[i]->tag, "term|factor|number|regex") == 0){
            if(strstr(node.children[i]->contents, ".") == 0){
                vm_add_opcode_to_stack(&stack, FCONST);
                vm_add_float_to_stack(&stack, strtof(node.children[i]->contents, NULL));
            }
            else {
                vm_add_opcode_to_stack(&stack, ICONST);
                vm_add_int_to_stack(&stack, strtol(node.children[i]->contents, NULL, 10));
            }
        }
        //else if(strcmp(node.children[i]->tag, ""))
    }
    puts("handled lexp");
    vm_add_opcode_to_stack(&stack, IPRINTLN);
    return 0;
}

int math_handler(mpc_ast_t node, xenon_stack_vector stack){
    /*puts("math_handler");
    //mpc_ast_print(node.children[0]);
    //int nodes_in_tree = number_of_nodes(*node.children);
    if(node.children == NULL){
        puts("yes");
    }*/
    lexp_handler(*node.children[0], stack);
    return 0;
}

int function_handler(mpc_ast_t node, xenon_stack_vector stack){
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
    vm_add_func_to_stack(&stack, 0, narg, 0, ret, x_native_t);
    return 0;
}

int tree_walker(mpc_ast_t* tree, xenon_stack_vector stack){
    //puts("tree_walker");
    //printf("%d\n", stack_pointer);
    //xenon_stack_item* stack = calloc(1, DEFAULT_STACK_SIZE * sizeof(xenon_stack_item));
    //int nodes_in_tree = number_of_nodes(tree);
    if(tree[0].children_num == 0){
        puts("aids");
        vm_add_opcode_to_stack(&stack, HALT);
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
                math_handler(*tree->children[i], stack);
            }
        }
    }
    vm_add_opcode_to_stack(&stack, HALT);
    //printf("%d\n", stack_pointer);
    return 0;
}

/*int main(int argc, char **argv){
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
}*/
