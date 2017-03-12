#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef __HASHMAP_H_
    #include "hashmap.h"
#endif
#ifndef __VM_H_
    #include "../vm.h"
#endif

int main(void){
    struct stack_base val;
    val.type = x_integer;
    val.data.anint = 10;
    hashmap *hm = hashmap_init(100);
    hashmap_set(hm, "a", val);
    struct stack_base *sb = hashmap_get(hm, "a");
    if(sb != NULL){
        printf("'a' = %ld\n", sb->data.anint);
    }
    hashmap_free(hm);
}
