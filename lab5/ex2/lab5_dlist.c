#include "lab5_dlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARG 1024
#define MAX_LINE 255

typedef struct Node
{
  char *key;
  dlistValue val;
  struct Node *next;
} Node;

typedef struct List
{
  Node *head;
  int length;
  dlistValueType type;
} List;

void dlistFreeNodes(dlist this) {
  if (((List *)this)->length == 0) return;
  Node *node_it = ((List *)this)->head;
  while (node_it) {
    Node *temp = node_it;
    free(temp->key);
    if (((List *)this)->type == DLIST_STR)
      free(temp->val.strValue);
    node_it = node_it->next;
    free(temp);
  }
  ((List *)this)->length = 0;
}

static int intInc(const void *a, const void *b)
{
  // return (((Node *)a)->val.intValue - ((Node *)b)->val.intValue) >= 0;
  return ((*(Node **)a)->val.intValue - (*(Node **)b)->val.intValue) >= 0;
}

static int doubleInc(const void *a, const void *b)
{
  return ((*(Node **)a)->val.doubleValue - (*(Node **)b)->val.doubleValue) >= 0;
}

static int strInc(const void *a, const void *b)
{
  return strcmp((*(Node **)a)->val.strValue, (*(Node **)b)->val.strValue) >= 0;
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
int (*const comp[3][3])(const void *, const void *) = 
{
    {anyRand, intInc, intDec},
    {anyRand, strInc, strDec},
    {anyRand, doubleInc, doubleDec}
};

dlist createDlist(dlistValueType type)
{
  dlist *l = (dlist *)malloc(sizeof(List));
  ((List *)l)->head = NULL;
  ((List *)l)->length = 0;
  ((List *)l)->type = type;
  if (type == DLIST_UNKOWN) return NULL;
  return l;
}

int dlistIsEmpty(dlist_const this)
{
  return (((List *)this)->length == 0);
}

void dlistAppend(dlist this, const char* key, dlistValue value)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = malloc(strlen(key)+1);
  strcpy(node->key, key);
  if (((List *)this)->type == DLIST_INT)
    node->val.intValue = value.intValue;
  else if (((List *)this)->type == DLIST_DOUBLE)
    node->val.doubleValue = value.doubleValue;
  else if (((List *)this)->type == DLIST_STR) {
    node->val.strValue = malloc(sizeof(char)*(strlen(value.strValue)+1));
    strcpy(node->val.strValue, value.strValue);
  }
  // set new node as head;
  if (((List *)this)->length == 0) {
    node->next = NULL;
  } else node->next = ((List *)this)->head;
  ((List *)this)->head = node;
  ((List *)this)->length++;
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method)
{
  // printf("sorting elements\n");
  size_t length = (size_t)((List *)this)->length;
  if (length == 0) return;
  Node **node_arr = malloc(sizeof(Node *) * length);
  Node *node_it = ((List *)this)->head;
  size_t arr_it = 0;
  
  // store pointers to node iterators using an array
  while (node_it) {
    node_arr[arr_it] = node_it;
    arr_it++;
    node_it = node_it->next;
  }

  // printf("Before: \n");
  // for(int i = 0; i < (int)length; i++)
  // {
  //   printf("%d\n", node_arr[i]->val.intValue);
  // }

  // sort
  qsort(node_arr, length, sizeof(Node *), comp[((List *)this)->type-1][method-1]);

  // printf("After: \n");
  // for(int i = 0; i < (int)length; i++)
  // {
  //   printf("%d\n", node_arr[i]->val.intValue);
  // }
  
  // work on destination list
  if (((List *)listDst)->length != 0) {
    dlistFreeNodes(listDst);
  }
  ((List *)listDst)->head = node_arr[0];
  ((List *)listDst)->length = (int)length;
  node_it = node_arr[0];
  for (size_t i = 1 ; i < length; i++) {
    node_it->next = node_arr[i];
    node_it = node_it->next;
  }
  node_it->next = NULL;
  ((List *)this)->length = 0;
  free(node_arr);
}

void dlistPrint(dlist_const this)
{
  if (((List *)this)->length == 0) return;
  Node *node_it = ((List *)this)->head;
  int flag = 0;
  while (node_it) {
    if (flag)
    {
      printf("\n");
    }
    if (((List *)this)->type == DLIST_INT)
      printf("%s=%d", node_it->key, node_it->val.intValue);
    else if (((List *)this)->type == DLIST_DOUBLE)
      printf("%s=%lf", node_it->key, node_it->val.doubleValue);
    else if (((List *)this)->type == DLIST_STR)
      printf("%s=%s", node_it->key, (node_it->val.strValue));
    node_it = node_it->next;
    flag = 1;
  }
}

void dlistFree(dlist this)
{
  dlistFreeNodes(this);
  free(this);
}
