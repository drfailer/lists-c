/******************************************************************************
 * NAME: liblist
 * DESCRIPTION: library whiche provide linked lists data structures.
 * AUTHOR: drfailer
 * DATE: Sun Dec 12 12:56:15 PM CET 2021
 *
 *****************************************************************************/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/
/* ALLOCATION AND FREE                                                       */
/*****************************************************************************/

/**
 * Create a new empty list using `malloc`.
 *
 * ERROR: exit with an error message if the allocation failed.
 */
list_t *createlst() {
  list_t *new = malloc(sizeof(list_t));

  if (new == NULL) {
    fprintf(stderr, "Allocation error\n");
    exit(EXIT_FAILURE);
  } else {
    new->head = NULL;
  }

  return new;
}

/**
 * Delete a list and free the allocated memory. The function take a function
 * pointer as parameter which is used to free the memory allocated for the data
 * (take NULL if the data is not dynamically allocated or already freed).
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

/*****************************************************************************/
/* ADDING ELEMENTS                                                           */
/*****************************************************************************/

/**
 * Create a new element using `createElement` and put it on the head of the
 * list.
 *
 * RETURN: return 1 if the inputted list is NULL, 0 otherwise.
 */
int pushlst(list_t *l, void *data) {
  node_t *newNode = createNode(data);
  int err = 0;

  if (l != NULL) {
    newNode->next = l->head;
    l->head = newNode;
  } else {
    fprintf(stderr, "Error: the list doesn't exist.\n");
    err = 1;
  }

  return err;
}

/**
 * Create a new element using `createElement` and put it at the end of the
 * list.
 *
 * RETURN: return 1 if the inputted list is NULL, 0 otherwise.
 */
int appendlst(list_t *l, void *data) {
  void *newNode = NULL;
  node_t **prev;
  int err = 0;

  if (l != NULL) {
    prev = &(l->head);
    while (*prev != NULL) {
      prev = &(*prev)->next;
    }
    newNode = createNode(data);
    *prev = newNode;
  } else {
    fprintf(stderr, "Error: the list doesn't exist.\n");
    err = 1;
  }

  return err;
}

/**
 * Create a new element using `createElement` and put it at the `index`
 * position.
 *
 * RETURN: 0 if the element is correctly inserted in the list, 1 if the index
 * was invalid.
 * ERROR: if the index is invalid, the function returns 1 but don't free the
 * data given as parameter, this operation should be made manually by the user
 * if the function return an error.
 */
int insertlst(list_t *l, void *data, int index) {
  node_t **curr = NULL;
  node_t *new = NULL;
  int cpt = 0;
  int err = 0;

  if (l != NULL) {
    curr = &l->head;
    while (*curr != NULL && cpt < index) {
      curr = &(*curr)->next;
      ++cpt;
    }
    // if the index is valid, the data is added to the list:
    if (cpt == index) {
      new = createNode(data);
      new->next = *curr;
      *curr = new;
    } else {
      fprintf(stderr, "Error: non valid index for insertion.\n");
      err = 1;
    }
  } else {
    fprintf(stderr, "Error: the list doesn't exist.\n");
    err = 1;
  }

  return err;
}

/*****************************************************************************/
/* REMOVE ELEMENTS                                                           */
/*****************************************************************************/

/**
 * Remove the head of the list `l` and return the data stored inside of it to
 * free the node without causing memory leak.
 *
 * IMPORTANT: the data has to be freed manually by the user.
 * RETURN: old data stored in the head node.
 */
void *poplst(list_t *l) {
  node_t *tmp = NULL;
  void *oldData = NULL;

  if (l != NULL && l->head != NULL) {
    tmp = l->head;
    l->head = tmp->next;
    oldData = tmp->data;
    tmp->data = NULL;
    free(tmp);
  }

  return oldData;
}

/**
 * Remove the last element of the list `l` and return the data stored inside of
 * it to free the node without causing memory leak.
 *
 * IMPORTANT: the data has to be freed manually by the user.
 * RETURN: old data stored in the head node.
 */
// TODO: rewrite
void *removeLastlst(list_t *l) {
  node_t *curr = NULL;
  node_t **prev = NULL;
  void *oldData = NULL;

  if (l != NULL && l->head != NULL) {
    curr = l->head;
    prev = &(l->head);
    while (curr->next != NULL) {
      prev = &(curr->next);
      curr = curr->next;
    }
    *prev = NULL;
    oldData = curr->data;
    free(curr);
  }

  return oldData;
}

/**
 * Remove the element at the `index` position and return the removed data.
 *
 * RETURN: NULL if `l` is NULL or if the index is not in the list, otherwise,
 * it return the old data
 */
void *removeNodelst(list_t *l, int index) {
  node_t **prev = NULL; // pointer on the field `next` of the previous node
  node_t *tmp = NULL;
  node_t *oldData = NULL;
  int cpt = 0;

  if (l != NULL) {
    prev = &l->head;
    while (*prev != NULL && cpt < index) {
      prev = &(*prev)->next;
      ++cpt;
    }
    // if the index is valid, the data is added to the list:
    if (cpt == index) {
      tmp = *prev; // *prev is the address of the current node, stored in the
                   // field `next` of the previous node. So after that, `tmp`
                   // point on the current node which we want to remove.
      *prev = tmp->next;
      oldData = tmp->data;
      tmp->data = NULL;
      tmp->next = NULL;
      free(tmp);
    }
  }

  return oldData;
}

/*****************************************************************************/
/* ACCESSORS                                                                 */
/*****************************************************************************/

/**
 * Find the element at the `index` position and return the address of the node.
 *
 * NOTE: if the index is not in the list, the function returns NULL
 */
node_t *nodelst(list_t *l, int index) {
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
 * Find the element at the `index` position and return the address of the data
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

/**
 * Return the data stored in the head of the list.
 */
void* headlst(list_t * l) {
  void *headData = NULL;

  if (l != NULL && l->head != NULL) {
    headData = l->head->data;
  }

  return headData;
}

/*****************************************************************************/
/* UTILS FUNCTIONS                                                           */
/*****************************************************************************/

/**
 * Return the number of elements stored in the list `l`.
 *
 * ERROR: return 0 if the list is null.
 */
int lengthlst(list_t *l) {
  int length = 0;
  node_t *curr = NULL;

  if (l != NULL) {
    curr = l->head;
    while (curr != NULL) {
      ++length;
      curr = curr->next;
    }
  }

  return length;
}

/**
 * Print the list this way:
 * [ elt0 ] -> [ elt1 ] -> [ ]
 * Take a function pointer as parameter which is used for printing the data.
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
