
#include "../include/list.h"

#include <stddef.h>
#include <stdlib.h>

#include "../include/printing.h"





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
    lnode_t *next_node;

    while(curr != NULL){
        next_node = curr -> next;
        
        if(item_free != NULL){
            item_free(curr -> data);
        }

        free(curr);
        curr = next_node;

    }

    free(list);

    


    
}

size_t list_length(list_t *list) {
    if (list == NULL){
        return 0;
    }

    return list -> length;
}

int list_addfirst(list_t *list, void *item) {
    if (list == NULL){
        return -1;
    }
    
    lnode_t *node = newnode(item);
    if (node == NULL){
        return -2;
    }

    if(list-> head == NULL){
        list -> head = node;
        list -> tail = node;
    }else {
    node -> next = list -> head;
    list -> head -> prev = node;
    list -> head = node;

    }

    list -> length++;

    return 0;
    
    

}

int list_addlast(list_t *list, void *item) {
    if(list == NULL){
        return -1;
    }

    lnode_t *node = newnode(item);
    if(node == NULL){
        return -2;
    }

    if (list -> head == NULL){
        list -> head = node;
        list -> tail = node;
    } else {
        list -> tail -> next = node;
        node -> prev = list -> tail;
        list -> tail = node;
    }

    list -> length++;

    return 0;



}

void *list_popfirst(list_t *list) {
    if(list == NULL || list->head == NULL){
        PANIC("List is empty");
        return NULL;
    }

    lnode_t *temp = list -> head;
    void *item = temp -> data;

    list -> head = list -> head -> next;

    if(list -> head != NULL){
        list -> head -> prev = NULL;
    }else{
        list -> tail = NULL;
    }

    free(temp);
    list -> length--;



    return item;

    
}

void *list_poplast(list_t *list) {
    if(list == NULL || list -> tail == NULL){
        PANIC("List is empty");
        return NULL;
    }

    void *item = list -> tail -> data;
    lnode_t *temp = list -> tail;

    list -> tail = list -> tail -> prev;

    if(list -> tail != NULL){
        list -> tail -> next = NULL;
    }else{
        list -> head = NULL;
    }

    free(temp);
    list -> length--;



    return item;


}

int list_contains(list_t *list, void *item) {
    if(list == NULL){
        pr_error("List is empty, cannot check for item in list");
        return 0;
    }

    lnode_t *curr = list -> head;
    

    while(curr != NULL){
        if(list -> cmpfn(curr -> data, item) == 0){
            return 1;
        }else{
            curr = curr -> next;
        }
    }
    
    return 0;
  
}

static void swap(lnode_t *a, lnode_t *b){
    void *temp = a -> data;
    a -> data = b -> data;
    b -> data = temp;

}

//Bruke cmpfn for å kutte liste i 2 for å legge til pivot #Eller bruke rndint og time
static lnode_t *partition(list_t *list, lnode_t *low, lnode_t *high){
    //Velge pivot, den siste i listen
    void *pivot = high -> data;

    //Setter j som det som kommer før første i listen
    lnode_t *i = low -> prev;

    //J blir første i listen
    lnode_t *j = low;

    //Loopen for byttet
    while(j != high){
        //Dersom j er mindre enn pivot
        if (list -> cmpfn (j -> data, pivot) < 0){
            if ( i == NULL){
                i = low;
            } else {
                i = i -> next;
            }

            swap(i,j);

        }
        j = j -> next;
    
      }

      swap(i, high);
      return i;
    


}

static void sort_recursive(list_t* list, lnode_t* low, lnode_t* high);

void list_sort(list_t *list){
    //Gjøres
}
  
    



list_iter_t *list_createiter(list_t *list) {
    list_iter_t *iter = malloc(sizeof(list_iter_t));
    if(iter == NULL){
        return NULL;
    }
    
    iter -> list = list;
    iter -> node = list -> head;

    return iter;

}

void list_destroyiter(list_iter_t *iter) {
    if(iter != NULL){
        free(iter);
    }
    
    
}

int list_hasnext(list_iter_t *iter) {
    //Check if iterator or current node is NULL
    if(iter == NULL || iter -> node == NULL){
        //Done with the round
        return 0;
    }
    //More to iterate
    return 1;

}


void *list_next(list_iter_t *iter) {
    if(iter == NULL || iter -> node == NULL){
        return NULL;
    }

    //Get the value from current node
    void *item = iter -> node -> data;

    //Move iter to next node
    iter -> node = iter -> node -> next;

    return item;

}

void list_resetiter(list_iter_t *iter) {
    if(iter == NULL){
        return;
    }
    //Reseter: Goes back to the head of the list
    if(iter -> list != NULL){
        iter -> node = iter -> list -> head;
    }

   // iter -> node = iter -> list -> head;    

    
}
