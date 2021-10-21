/*******************************************************************************
 * NAME: liblist
 * DESCRIPTION: library whiche provide linked lists data structurs.
 * AUTHOR: drfailer
 * DATE: Wed Oct 20 07:10:56 PM CEST 2021
 *
 ******************************************************************************/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Create a new empty list using `malloc`.
 */
list_t *createlst() {
  list_t *new = malloc(sizeof(list_t));

  if (new == NULL) {
    fprintf(stderr, "Allocation error\n");
    exit(EXIT_FAILURE);
  } else {
    new->head = NULL;
    new->last = NULL;
  }

  return new;
}

/**
 * Delete a list and free the allocated memory. The function take a function
 * pointer as parameter which is used to free the memory allocated for the data
 * (take NULL if the data is not dynamicaly allocated or already freed).
 */
void freelst(list_t **l, void (*freeData)(void *)) {
  node_t *curr = NULL;
  node_t *tmp = NULL;

  if (l != NULL && *l != NULL) {
    // free nodes:
    curr = (*l)->head;
    while (curr != NULL) {
      tmp = curr;
      curr = curr->next;
      if (freeData != NULL) {
        (*freeData)(tmp->data); // free the data stored in the node
        tmp->data = NULL;
      }
      free(tmp);
    }
    free(*l);
    *l = NULL;
  }
}

/**
 * Create a new node using dynamic allocation.
 *
 * RETURN: newElt
 * ERROR: exit if the allocation failed.
 */
node_t *createNode(void *data) {
  node_t *newNode = malloc(sizeof(node_t));

  if (newNode == NULL) {
    fprintf(stderr, "Error Allocation on new element.\n");
    exit(EXIT_FAILURE); // NOTE: may change
  } else {
    newNode->data = data;
    newNode->next = NULL;
  }

  return newNode;
}

/**
 * Create a new element using `createElement` and put it on the head of the
 * list.
 */
void pushlst(list_t **l, void *data) {
  node_t *newNode = createNode(data);

  if (l != NULL && *l != NULL) {
    if ((*l)->last == NULL) { // the list has no elements
      (*l)->last = newNode;
    }
    newNode->next = (*l)->head;
    (*l)->head = newNode;
  }
}

/**
 * Create a new element using `createElement` and put it at the end of the
 * list.
 */
void appendlst(list_t **l, void *data) {
  void *newNode = createNode(data);

  if (l != NULL && *l != NULL) {
    if ((*l)->last != NULL) {
      (*l)->last->next = newNode;
      (*l)->last = newNode;
    }
  }
}

/**
 * Create a new element using `createElement` and put it at the `index`
 * position.
 *
 * RETURN: 0 if the element is correctly inserted in the list, 1 if the index
 * was invalid.
 * ERROR: if the index is invalide, the function returns 1 but don't free the
 * data given as parameter, this operation should be made manualy by the user
 * if the function return an error.
 *
 * FIXME: whene the indice is 0, the node is not correctly inserted on the head
 */
int insertlst(list_t **l, void *data, int index) {
  node_t *newNode = NULL;
  node_t *curr = NULL;
  int cpt = 0, err = 0;

  if (l != NULL && *l != NULL && index >= 0) {
    curr = (*l)->head;
    while (curr != NULL && cpt < index - 1) {
      curr = curr->next;
      ++cpt;
    }
    if (curr != NULL) {
      newNode = createNode(data);
      newNode->next = curr->next;
      curr->next = newNode;
    } else {
      err = 1;
      fprintf(stderr, "Error: invalid index\n");
    }
  } else {
    err = 1;
    fprintf(stderr, "Error: invalid index\n");
  }

  return err;
}

/**
 * Find the element at the `index` position and return the adress of the node.
 *
 * NOTE: if the index is not in the list, the function returns NULL
 */
void *nodelst(list_t *l, int index) {
  node_t *curr = NULL;
  int cpt = 0;

  if (l != NULL && index >= 0) {
    curr = l->head;
    while (curr != NULL && cpt != index) {
      curr = curr->next;
      ++cpt;
    }
  }

  return curr;
}

/**
 * Find the element at the `index` position and return the adress of the data
 * stored in the node. Use the function to access the value stored in the list.
 *
 * NOTE: if the index is not in the list, the function returns NULL
 */
void *datalst(list_t *l, int index) {
  node_t *curr = NULL;
  int cpt = 0;

  if (l != NULL && index >= 0) {
    curr = l->head;
    while (curr != NULL && cpt != index) {
      curr = curr->next;
      ++cpt;
    }
  }

  return (curr != NULL) ? curr->data : NULL;
}

void *removeHeadlst(list_t **l);

void *removeLast(list_t **l);

void *removeNodelst(list_t **l, int index);

/**
 * Print the list this way:
 * [ elt0 ] -> [ elt1 ] -> [ ]
 * Take a function pointeur as parameter which is used for printing the data.
 *
 * NOTE: may change the printing function to a to string function
 */
void printlst(list_t *l, void (*printData)(void *data)) {
  node_t *curr = NULL;

  if (l != NULL) {
    curr = l->head;
    while (curr != NULL) {
      printf("[ ");
      (*printData)(curr->data);
      printf(" ] -> ");
      curr = curr->next;
    }
  }
  printf("[ ]\n");
}
