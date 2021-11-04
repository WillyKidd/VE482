#include "sort.h"

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
  assert(a!=NULL);
  assert(b!=NULL);
  return (rand() % 2);
}

/**
 * 3d array of function pointers
 */
int (*const comp[3][3])(const void *, const void *) = 
{
  {intInc, intDec, anyRand},
  {doubleInc, doubleDec, anyRand},
  {strInc, strDec, anyRand}
};

void listSort(List *l, ValueType dtype, SortType order) {
  if(l->length == 0) return;
  Node *node = l->head;
  Node *node_arr = (Node *)malloc((size_t)(l->length) * sizeof(Node));
  for(int i = 0; i < l->length; i++)
  {
    memcpy((node_arr+i), node, sizeof(Node));
    node = node->next;
  }
  qsort(node_arr, (size_t)l->length, sizeof(Node), comp[dtype][order]);
  node = l->head;
  for(int i = 0; i < l->length; i++)
  {
    node->key = (node_arr + i)->key;
    node->val = (node_arr + i)->val;
    node = node->next;
  }
  free(node_arr);
}
