#include "lab5_dlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARG 1024
#define MAX_LINE 255

typedef struct Node
{
  char *key;
  void *val;
  struct Node *next;
} Node;

typedef struct List
{
  Node *head;
  int length;
  dlistValueType type;
} List;

static int intInc(const void *a, const void *b)
{
    return (*((int *)(((Node *)a)->val)) >= *((int *)(((Node *)b)->val)));
}

static int doubleInc(const void *a, const void *b)
{
    return (*((double *)(((Node *)a)->val)) >= *((double *)(((Node *)b)->val)));
}

static int strInc(const void *a, const void *b)
{
    return (strcmp((char *)(((Node *)a)->val), (char *)(((Node *)b)->val)) >= 0);
}

static int intDec(const void *a, const void *b){return intInc(b, a);}

static int doubleDec(const void *a, const void *b){return doubleInc(b, a);}

static int strDec(const void *a, const void *b){return strInc(b, a);}

static int anyRand(const void *a, const void *b)
{
    a = b = NULL;
    return (rand() % 2);
}

/**
 * 3d array of function pointers
 */
static int (*const comp[3][3])(const void *, const void *) = 
{
    {anyRand, intInc, intDec},
    {anyRand, strInc, strDec},
    {anyRand, doubleInc, doubleDec}
};

dlist createDlist(dlistValueType type)
{
  List *l = (List *)malloc(sizeof(List));
  l->head = NULL;
  l->length = 0;
  l->type = type;
  return l;
}

int dlistIsEmpty(dlist_const this)
{
  return (((List *)this)->length == 0);
}

void dlistAppend(dlist this, const char* key, dlistValue value)
{
  Node *n = (Node *)malloc(sizeof(Node));
  n->key = (char *)malloc(sizeof(char) * MAX_LINE);
  strcpy(n->key, key);
  if (((List*)this)->type == DLIST_INT)
  {
    n->val = malloc(sizeof(int));
    *((int *)n->val) = value.intValue;
  }
  else if (((List*)this)->type == DLIST_DOUBLE)
  {
    n->val = malloc(sizeof(double));
    *((double *)n->val) = value.doubleValue;
  }
  else if (((List*)this)->type == DLIST_STR)
  {
    n->val = malloc(sizeof(char)*(strlen(value.strValue)+1));
    strcpy((char *)(n->val), value.strValue);
  }
  if(((List *)this)->head) n->next = ((List *)this)->head;
  else n->next = NULL;
  ((List *)this)->head = n;
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method)
{
  printf("sorting elements\n");
  if (((List *)this)->length == 0) return;
  auto comp_func =  comp[((List *)this)->type-1][method-1];
  Node *node = ((List *)this)->head;
  Node *node_arr = (Node *)malloc((size_t)(((List *)this)->length) * sizeof(Node));
  for (int i = 0; i < ((List *)this)->length; i++)
  {
      memcpy((node_arr+i), node, sizeof(Node));
      node = node->next;
  }
  qsort(node_arr, (size_t)(((List *)this)->length), sizeof(Node), comp_func);
  for (int i = 0; i < ((List *)this)->length; i++)
  {
    dlistValue temp;
    if(((List *)this)->type == DLIST_INT) temp.intValue = (*(int *)((node_arr+i)->val));
    dlistAppend(listDst, (node_arr+i)->key, temp);
  }
  free(node_arr);
}

dlistPrint(dlist list)
{
 Node *node = ((List *)list)->head;
 while (node)
 {
   
 }
}
