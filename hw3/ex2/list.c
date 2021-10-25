# include "list.h"

const char DTYPE[3][7] = {"int\0", "double\0", "char*\0"};

List *listInit(char *file_name, int dtype)
{
    FILE *ifile = fopen(file_name, "r");
    printf("reading %s\n", file_name);
    fflush(stdout);
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->length = 0;
    char *line = (char*)malloc(MAX_LINE * sizeof(char));
    while(fgets(line, MAX_LINE, ifile))
    {
        char *key = NULL, *val = NULL;
        void *val_new = NULL;
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
            val_new = malloc(sizeof(char) * (strlen(val)+1));
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
    size_t key_length = strlen(key) + 1;
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = (char *)malloc(sizeof(char) * key_length);
    n->val = val;
    strcpy(n->key, key);
    if(l->head) n->next = l->head;
    else n->next = NULL;
    l->head = n;
}

void listSort(List *l, int dtype, int order)
{
    printf("sorting elements\n");
    fflush(NULL);
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

void listPrintToFile(List *l, char *file_name, int dtype)
{
    printf("writing %s\n", file_name);
    FILE *ofile = fopen(file_name, "w");
    Node *node = l->head;
    while(node)
    {
        if(dtype == INT) 
        {
            fprintf(ofile, "%s=%d\n", node->key, *((int *)(node->val)));
            // fprintf(stderr, "%s=%d\n", node->key, *((int *)(node->val)));
            fflush(NULL);
        }
        else if(dtype == DOUBLE)
        {
            fprintf(ofile, "%s=%lf\n", node->key, *((double *)(node->val)));
            // fprintf(stderr, "%s=%lf\n", node->key, *((double *)(node->val)));
            fflush(NULL);
        }
        else if(dtype == STRING)
        {
            fprintf(ofile, "%s=%s\n", node->key, ((char *)(node->val)));
            // fprintf(stderr, "%s=%s\n", node->key, ((char *)(node->val)));
            fflush(NULL);
        }
        else break;
        node = node->next;
    }
    fclose(ofile);
}

void listFree(List *l)
{
    Node *node = l->head, *temp;
    while(node)
    {
        temp = node;
        node = node->next;
        free(temp->val);
        free(temp->key);
        free(temp);
    }
    free(l);
}
