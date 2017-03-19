#include <stdbool.h>
#ifndef __VM_H_
    #include "../vm/vm.h"
#endif
#ifndef __HASHMAP_H_
    #define __HASHMAP_H_
#endif

typedef struct {
    int key;
    xenon_stack_item value;
} hashmap_element;



typedef struct {
    int len;
    hashmap_element *list;
} hashmap_element_vector;



typedef struct {
    int size;
    hashmap_element_vector *table;
} hashmap;



hashmap_element_vector *hashmap_resize_vector(hashmap_element_vector *hev);
hashmap *hashmap_init(int size);
int hashmap_free(hashmap *hm);
long hashmap_hasher(hashmap *hm, char* inp);
long hashmap_hasher_nc(char* inp);
int *hashmap_item_exists(hashmap *hm, char *inp);
int hashmap_set(hashmap *hm, char* name, xenon_stack_item val);
xenon_stack_item *hashmap_get(hashmap *hm, char *name);
