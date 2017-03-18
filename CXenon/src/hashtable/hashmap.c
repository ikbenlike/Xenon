#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef __VM_H_
    #include "../vm.h"
#endif
#ifndef __HASHMAP_H_
    #include "hashmap.h"
#endif



hashmap_element_vector *hashmap_resize_vector(hashmap_element_vector *hev){
    hev->len *= 2;
    hashmap_element *a = realloc(hev->list, hev->len * sizeof(hashmap_element));
    if(a != NULL){
        hev->list = a;
    }
    else{
        return NULL;
    }
    return hev;
}



hashmap *hashmap_init(int size){
    hashmap *hm = calloc(1, sizeof(hashmap));
    hm->table = calloc(1, sizeof(hashmap_element_vector) * size);
    hm->size = size;
    for(int i = 0; i < hm->size; i++){
        hm->table[i].len = 1;
        hm->table[i].list = calloc(1, sizeof(hashmap_element));
    }
    return hm;
}



int hashmap_free(hashmap *hm){
    for(int i = 0; i < hm->size; i++){
        free(hm->table[i].list);
    }
    free(hm->table);
    free(hm);
    return 0;
}



long hashmap_hasher(hashmap *hm, char* inp){
    int output = 0;
    int i = 0;
    int l = strlen(inp);
    while((i + 1) <= l){
        output = output*17 + inp[i++];
    }
    return output % hm->size;
}



long hashmap_hasher_nc(char* inp){
    int output = 0;
    int i = 0;
    int l = strlen(inp);
    while((i + 1) <= l){
        output = output*17 + inp[i++];
    }
    return output;
}



int *hashmap_item_exists(hashmap *hm, char *inp){
    int *r = calloc(1, 2 * sizeof(int));
    int c = hashmap_hasher_nc(inp);
    int n = c % hm->size;
    hashmap_element_vector a = hm->table[n];
    for(int i = 0; i < a.len; i++){
        if(a.list[i].key == c){
            r[0] = 1;
            r[1] = i;
            return r;
        }
    }
    r[0] = 0;
    r[1] = 0;
    return r;
}



int hashmap_set(hashmap *hm, char* name, xenon_stack_item val){
    int *e = hashmap_item_exists(hm, name);
    long hn = hashmap_hasher(hm, name);
    long key = hashmap_hasher_nc(name);
    if(e[0] == 1){
        if(e[1] >= hm->table[hn].len){
            if(hashmap_resize_vector(&hm->table[hn]) == NULL){
                free(e);
                return 1;
            }
        }
        hm->table[hn].list[e[1] + 1].key = key;
        hm->table[hn].list[e[1] + 1].value = val;
    }
    else{
        hm->table[hn].list[0].key = key;
        hm->table[hn].list[0].value = val;
    }
    free(e);
    return 0;
}



xenon_stack_item *hashmap_get(hashmap *hm, char *name){
    long n = hashmap_hasher(hm, name);
    int *e = hashmap_item_exists(hm, name);
    if(e[0] == 1){
        int x = e[1];
        free(e);
        return &hm->table[n].list[x].value;
    }
    else{
        free(e);
        return NULL;
    }
}
