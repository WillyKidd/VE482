#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARG 1024
#define MAX_LINE 255

enum Dtype
{
    INT,
    DOUBLE,
    STRING
};

enum ORDER
{
    INC,
    DEC,
    RAN
};

extern const char DTYPE[3][7];

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

static int intInc(const void *a, const void *b)
{
    return (*((int *)(((Node *)a)->val)) > *((int *)(((Node *)b)->val)));
}

static int doubleInc(const void *a, const void *b)
{
    return (*((double *)(((Node *)a)->val)) > *((double *)(((Node *)b)->val)));
}

static int strInc(const void *a, const void *b)
{
    return strcmp((char *)(((Node *)a)->val), (char *)(((Node *)b)->val));
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
    {intInc, intDec, anyRand},
    {doubleInc, doubleDec, anyRand},
    {strInc, strDec, anyRand}
};

List *listInit(char *file_name, int dtype);
void listInsert(List *l, char *key, void *val);
void listSort(List *l, int dtype, int order);
void listPrintToFile(List *l, char *file_name, int dtype);

#endif
