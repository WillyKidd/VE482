#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} List;

// constructor and destructor
List *listInit(void);
Node *nodeInit(char *key, void *value);
void listFree(List *list);
void nodeFree(Node *node);

// dynamic methods
void listInsert(List *list, char *key, void *val);

#endif // LIST_H
