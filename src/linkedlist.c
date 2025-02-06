
#include "../include/list.h"

#include <stdlib.h>


typedef struct lnode lnode_t;
struct lnode {
    void *data;
    lnode_t *next;
    lnode_t *prev;
};

struct list {
    lnode_t *head;
    lnode_t *tail;
    size_t length;
    cmp_fn cmpfn;
    
};

struct list_iter {
    list_t *list;
    lnode_t *node;

};


static lnode_t *newnode(void *item) {
    lnode_t *node = malloc(sizeof(lnode_t));
    if(node == NULL){
        return NULL;
    }

    node -> data = item;
    node -> next = NULL;
    node -> prev = NULL;

    return node;

}

list_t *list_create(cmp_fn cmpfn) {
    list_t *list = malloc(sizeof(list_t));
    if(list == NULL){
        return NULL;
    }

    list -> head = NULL;
    list -> tail = NULL;
    list -> cmpfn = cmpfn;
    list -> length = 0;

    return list;

}

void list_destroy(list_t *list, free_fn item_free) {
    if(list == NULL){
        return;
    }
    
    lnode_t *curr = list -> head;


    
}

size_t list_length(list_t *list) {

}

int list_addfirst(list_t *list, void *item) {
    lnode_t *node = newnode(item);

    //Sette inn verdi
    //
    
    if//null
    list -> head = node;
    list -> tail = node;

    if//det er andre

    //returnere 0 eller negativ error 

}

int list_addlast(list_t *list, void *item) {

}

void *list_popfirst(list_t *list) {

}

void *list_poplast(list_t *list) {

}

int list_contains(list_t *list, void *item) {

}

void list_sort(list_t *list) {

}

list_iter_t *list_createiter(list_t *list) {

}

void list_destroyiter(list_iter_t *iter) {
    
}

int list_hasnext(list_iter_t *iter) {

}

void *list_next(list_iter_t *iter) {

}

void list_resetiter(list_iter_t *iter) {
    
}
