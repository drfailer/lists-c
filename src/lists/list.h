#ifndef __LIB_LIST__
#define __LIB_LIST__

/* STRUCTURES: */

typedef struct node {
  void* data;
  struct node* next;
} node_t;

typedef struct list {
  node_t* head;
  node_t* last;
} list_t;

/* FONCTION: */

list_t* createlst();
void freelst(list_t ** l, void (*freeData) (void*));

void pushlst(list_t ** l, void * data);
void appendlst(list_t ** l, void * data);
int insertlst(list_t ** l, void * data, int index);

void* removeHeadlst(list_t ** l);
void* removeLast(list_t ** l);
void* removeNodelst(list_t ** l, int index);

void *nodelst(list_t *l, int index);
void* datalst(list_t * l, int index);
void* head(list_t * l);
list_t* tail(list_t * l);

void sortlst(list_t ** l, int (*cmp) (void*, void*)); // merge sort

void printlst(list_t *l, void (*printData) (void * data));

#endif
