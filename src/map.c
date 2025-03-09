
#include "../include/map.h"
#include "../include/defs.h"
#include <stdio.h>
#include <stdint.h>


#define START_SIZE 1000000

//Hashmap, contains an array of linked lists
struct map {
    //Compare function to compare keys
    cmp_fn cmpfn;
    //Hash function: Converts a key to a bucket index
    hash64_fn hashfn;
    //Size that decides how many "buckets" we got
    size_t size;
    //A counter for how many elements that are in the hashmap
    size_t capacity;
    //Bundle of pointer(Linked list)
    struct entry_t **buckets;
};

//Nodes in each bucket
typedef struct entry_t {
    //Our key and value pair
    void *key;
    void *value;
    //Pointers for our doubly linked list
    struct entry_t *next;
    struct entry_t *prev;
}entry_t;



map_t *map_create(cmp_fn cmpfn, hash64_fn hashfn) {
    map_t *map = malloc(sizeof(map_t));
    if(map == NULL){
        return NULL;
    }
    
    map -> cmpfn = cmpfn;
    map -> hashfn = hashfn;
    map -> size = START_SIZE;
    map -> capacity = 0;
    
    map -> buckets = malloc(sizeof(entry_t*) * START_SIZE);
    if(map -> buckets == NULL){
        free(map);
        return NULL;
    }

    for(int i = 0; i < START_SIZE; i++){
        map -> buckets[i] = NULL;
    }

    return map;
   
}

void map_destroy(map_t *map, free_fn val_freefn){
    for ( int i = 0; i < map->size; ++i){
        entry_t *curr = map -> buckets[i];
        while(curr != NULL){
            entry_t *next = curr -> next;
            if(val_freefn){
                val_freefn(curr -> value);
            }
            free(curr);
            curr = next;
        }
    }
    free(map -> buckets);
    free(map);
}


size_t map_length(map_t *map){
    if (map == NULL){
        return 0;
    }
    return map-> capacity;
}


void *map_insert(map_t *map, void *key, size_t key_size, void *value){
    if(map == NULL){
        return NULL;
    }
    
    
    //Finner bucket index
    uint64_t hash = map -> hashfn(key);
    uint64_t index = hash % map -> size;
    entry_t *curr = map -> buckets[index];

    //Loop if the key already exist
    while(curr != NULL){
        if(map -> cmpfn(curr -> key, key) == 0){
            void *old = curr -> value;
            curr -> value = value;
            return old;
        }
        curr = curr -> next;
    }

    //Key doesnt exist:
    entry_t *new_entry = malloc(sizeof(entry_t));
    if(new_entry == NULL){
        return NULL;
    }

    new_entry -> key = key;
    new_entry -> value = value;
    new_entry -> prev = NULL;
    new_entry -> next = map -> buckets[index];
    if (map -> buckets[index]){
        map -> buckets[index] -> prev = new_entry;
    }
    map ->buckets[index] = new_entry;

    map -> capacity++;

    return NULL;


}



void *map_remove(map_t *map, void *key){
    

    uint64_t hash = map -> hashfn(key);
    uint64_t index = hash % map -> size;
    
    entry_t *curr = map -> buckets[index];
    entry_t *prev = NULL;

    while(curr != NULL){
        if(map -> cmpfn(curr -> key, key) == 0){
            break;
        }
        prev = curr;
        curr = curr -> next;
    }
    if(curr == NULL){
        return NULL;
    }

    if(prev == NULL){
        map -> buckets[index] = curr -> next;
    }else{
        prev -> next = curr -> next;
    }

    if(curr -> next != NULL){
        curr -> next -> prev = prev;
    }

    void *value = curr -> value;
    free(curr);
    
    map -> capacity--;
    
    return value;

}


void *map_get(map_t *map, void *key){
    uint64_t hash = map -> hashfn(key);
    uint64_t index = hash % map -> size;

    entry_t *curr = map -> buckets[index];

    while(curr != NULL){
        if(map -> cmpfn(curr -> key, key) == 0){
            return curr -> value;
        }
        curr = curr -> next;
    }
    return NULL;
}





