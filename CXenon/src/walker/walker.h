#ifndef __WALKER_H_
    #define __WALKER_H_
#endif


#ifndef __VM_H_
    #include "../vm/vm.h"
#endif
#ifndef __VM_UTILS_H_
    #include "../vm/vm_utils.h"
#endif
#include "../mpc/mpc.h"

int number_of_nodes(mpc_ast_t *tree);
int lexp_handler(mpc_ast_t node, xenon_stack_vector stack);
int math_handler(mpc_ast_t node, xenon_stack_vector stack);
int function_handler(mpc_ast_t node, xenon_stack_vector stack);
int tree_walker(mpc_ast_t *tree, xenon_stack_vector stack);
