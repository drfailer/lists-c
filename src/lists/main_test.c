#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct container {
  int x;
} container_t;


container_t * createContainer(int a) {
  container_t * new = malloc(sizeof(container_t));

  if (new == NULL) {
    fprintf(stderr, "Error can't create container\n");
    exit(1);
  } else {
    new->x = a;
  }
  return new;
}

void freeContainer(void *a) {
  container_t* elt = (container_t*) a;
  if (elt != NULL) {
    free(elt);
  }
}

void showContainer(void *a) {
  container_t* elt = (container_t*) a;
  if (elt != NULL) {
    printf("%d", elt->x);
  } else {
    printf("NULL");
  }
}

int main(void)
{
  list_t *l = createlst();

  for (int i = 0; i < 10; ++i) {
    pushlst(l, createContainer(i));
  }

  printlst(l, &showContainer);

  printf("-----------------------\n");
  printf("TEST INSERTION\n");
  printf("-----------------------\n");

  printf("insertion tete de 50\n");
  pushlst(l, createContainer(50));
  printlst(l, &showContainer);
  printf("insertion fin de 60\n");
  appendlst(l, createContainer(60));
  printlst(l, &showContainer);
  printf("insertion de 70 à l'indice 5\n");
  insertlst(l, createContainer(70), 5);
  printlst(l, &showContainer);
  printf("insertion de 80 à l'indice 0\n");
  insertlst(l, createContainer(80), 0);
  printlst(l, &showContainer);

  printf("-----------------------\n");
  printf("TEST ACCESS\n");
  printf("-----------------------\n");
  printf("elst 0: ");
  showContainer(datalst(l, 0));
  printf("\nelst 1: ");
  showContainer(datalst(l, 1));
  printf("\nelst 2: ");
  showContainer(datalst(l, 2));
  printf("\nelst 3: ");
  showContainer(datalst(l, 3));
  printf("\n");

  printf("-----------------------\n");
  printf("TEST SUPPRESSION\n");
  printf("-----------------------\n");
  printlst(l, &showContainer);
  printf("-----------------------\n");
  printf("suppression de l'element d'indice 6\n");
  freeContainer(removeNodelst(l, 6));
  printlst(l, &showContainer);
  printf("last : [ ");
  showContainer(l->last->data);
  printf(" ]\n");
  printf("suppression de l'element d'indice 4\n");
  freeContainer(removeNodelst(l, 4));
  printlst(l, &showContainer);
  printf("last : [ ");
  showContainer(l->last->data);
  printf(" ]\n");
  printf("suppression de l'element d'indice 11\n");
  freeContainer(removeNodelst(l, 11));
  printlst(l, &showContainer);
  printf("last : [ ");
  showContainer(l->last->data);
  printf(" ]\n");
  printf("suppression de l'element d'indice 10\n");
  freeContainer(removeNodelst(l, 10));
  printlst(l, &showContainer);
  printf("last : [ ");
  showContainer(l->last->data);
  printf(" ]\n");
  printf("suppression de l'element d'indice 9\n");
  freeContainer(removeNodelst(l, 9));
  printlst(l, &showContainer);
  printf("last : [ ");
  showContainer(l->last->data);
  printf(" ]\n");
  printf("suppression de l'element d'indice 0\n");
  freeContainer(removeNodelst(l, 0));
  printlst(l, &showContainer);
  printf("suppression de l'element d'indice 0\n");
  freeContainer(removeNodelst(l, 0));
  printlst(l, &showContainer);
  printf("suppression de la tête\n");
  freeContainer(poplst(l));
  printlst(l, &showContainer);
  printf("suppression du dernier\n");
  freeContainer(removeLastlst(l));
  printlst(l, &showContainer);
  printf("suppression du dernier\n");
  freeContainer(removeLastlst(l));
  printlst(l, &showContainer);

  freelst(&l, &freeContainer);

  return 0;
}
