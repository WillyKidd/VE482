#include "ui.h"

char *sort_type[3] = {"inc", "dec", "rand"};
char *value_type[3] = {"int", "double", "char*"};

ValueType get_type(char *arg) {
  char temp[MAX_ARG] = {0}, *type;
  strcpy(temp, arg);
  type = strtok(temp, "_");
  type = strtok(NULL, ".");
  if (strcmp(type, "char*") == 0)
    return CHAR;
  if (strcmp(type, "int") == 0)
    return INT;
  if (strcmp(type, "double") == 0)
    return DOUBLE;
  return ERROR_VALUE_TYPE;
}

SortType get_order(char *arg) {
  if (strcmp(arg, "inc") == 0)
    return INC;
  if (strcmp(arg, "dec") == 0)
    return DEC;
  if (strcmp(arg, "rand") == 0)
    return RAN;
  return ERROR_SORT_TYPE;
}

int fill_list_from_file(List *list, char *file_path, ValueType value_t) {
  char *line = malloc(sizeof(char)*MAX_LINE);
  memset(line, 0, MAX_LINE);
  char *val_buffer = NULL, *key_buffer = NULL;
  FILE *fin = fopen(file_path, "r");
  if (fin == NULL) {
    fprintf(stderr, "Error opening file!\n");
    return -1;
  }
  while (fgets(line, MAX_LINE, fin)) {
    key_buffer = strtok(line, "=");
    val_buffer = strtok(NULL, "\n");
    
    // get key to insert
    char *key = malloc(sizeof(char) * (strlen(key_buffer)+1));
    strcpy(key, key_buffer);

    // get value to insert
    void *value = NULL;
    if (value_t == INT) {
      value = malloc(sizeof(int));
      *(int *)value = atoi(val_buffer);
    } else if (value_t == DOUBLE) {
      value = malloc(sizeof(double));
      *(double *)value = atof(val_buffer);      
    } else if (value_t == CHAR) {
      value = malloc(sizeof(char) * (strlen(val_buffer)+1));
      strcpy(value, val_buffer);
    }

    // insert key-value pair into list
    listInsert(list, key, value);
    memset(line, 0, MAX_LINE);
  }
  fclose(fin);
  free(line);
  return 1;
}

void listPrint(List *list, ValueType value_t) {
  Node *node = list->head;
  while (node) {
    if (value_t == CHAR) {
      printf("%s=%s\n", node->key, (char *)node->val);
    } else if (value_t == INT)
      printf("%s=%d\n", node->key, *((int *)(node->val)));
    else if (value_t == DOUBLE)
      printf("%s=%f\n", node->key, *((double *)(node->val)));
    node = node->next;
  }
}

int ui_cmd(char *argv[]) {
  ValueType value_t = get_type(argv[1]);
  SortType sort_t = get_order(argv[2]);
  List *list = listInit();
  if (fill_list_from_file(list, argv[1], value_t) < 0) return -1;
  listSort(list, value_t, sort_t);
  listPrint(list, value_t);
  listFree(list);
  return 0;
}

void init_plugin(Manager *m) {
  // exposing
  register_hook(m, ui_cmd, "txt");
  fprintf(stderr, "plugin-txt: Registration successful\n");
}
