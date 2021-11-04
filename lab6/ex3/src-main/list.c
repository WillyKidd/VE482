#include "list.h"

// constructor and destructor
List *listInit(void) {
  List *list = malloc(sizeof(List));
  list->head = NULL;
  list->length = 0;
  return list;
}

Node *nodeInit(char *key, void *value) {
  Node *node = malloc(sizeof(Node));
  node->key = key;
  node->val = value;
  node->next = NULL;
  return node;
}

void listFree(List *list) {
  Node *node = list->head;
  while (node) {
    Node *temp = node;
    nodeFree(node);
    node = node->next;
    free(temp);
  }
  free(list);
}

void nodeFree(Node *node) {
  free(node->key);
  free(node->val);
}

// dynamic methods
void listInsert(List *list, char *key, void *val) {
  Node *node = nodeInit(key, val);
  if (list->head) node->next = list->head;
  else node->next = NULL;
  list->head = node;
  list->length++;
}
