# include "list.h"

const char DTYPE[3][7] = {"int\0", "double\0", "string\0"};

List *listInit(char *file_name, int dtype)
{
    FILE *ifile = fopen(file_name, "r");
    printf("reading %s\n", file_name);
    fflush(stdout);
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->length = 0;
    char *line = (char*)malloc(MAX_LINE * sizeof(char));
    while(1)
    {
        char *key = NULL, *val = NULL;
        void *val_new = NULL;
        fgets(line, MAX_LINE, ifile);
        if(strlen(line) < 1) break;
        key = strtok(line, "=");
        val = strtok(NULL, "\n");
        if(dtype == INT)
        {
            val_new = malloc(sizeof(int));
            *((int*)val_new) = (int)strtol(val, NULL, 10);
        }
        else if(dtype == DOUBLE)
        {
            val_new = malloc(sizeof(double));
            *((double*)val_new) = strtod(val, NULL);
        }
        else if(dtype == STRING)
        {
            val_new = malloc(sizeof(char) * strlen(val));
            strcpy((char *)val_new, val);
        }
        listInsert(l, key, val_new);
        l->length++;
        memset(line, '\0', MAX_LINE);
    }
    free(line);
    fclose(ifile);
    return l;
}

void listInsert(List *l, char *key, void *val)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = (char *)malloc(sizeof(char) * MAX_LINE);
    n->val = val;
    strcpy(n->key, key);
    if(l->head) n->next = l->head;
    else n->next = NULL;
    l->head = n;
}

void listSort(List *l, int dtype, int order)
{
    printf("sorting elements\n");
    if(l->length == 0) return;
    Node *node = l->head;
    Node *node_arr = (Node *)malloc((l->length) * sizeof(Node));
    for(int i = 0; i < l->length; i++)
    {
        memcpy((node_arr+i), node, sizeof(Node));
        node = node->next;
    }
    qsort(node_arr, l->length, sizeof(Node), comp[dtype][order]);
    node = l->head;
    for(int i = 0; i < l->length; i++)
    {
        node->key = (node_arr + i)->key;
        node->val = (node_arr + i)->val;
        node = node->next;
    }
    free(node_arr);
}

void listPrintToFile(List *l, char *file_name, int dtype)
{
    printf("writing %s\n", file_name);
    FILE *ofile = fopen(file_name, "w");
    Node *node = l->head;
    while(node)
    {
        if(dtype == INT) fprintf(ofile, "%s=%d\n", node->key, *((int *)(node->val)));
        else if(dtype == DOUBLE) fprintf(ofile, "%s=%lf\n", node->key, *((double *)(node->val)));
        else if(dtype == STRING) fprintf(ofile, "%s=%s\n", node->key, ((char *)(node->val)));
        else break;
        node = node->next;
    }
    fclose(ofile);
}
