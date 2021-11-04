#include "ui.h"

char *sort_type[3] = {"inc", "dec", "rand"};
char *value_type[3] = {"int", "double", "char*"};

ValueType get_type(const char *arg) {
  if (arg == NULL) {
    fprintf(stderr, "Error: cannot get type, NULL char!\n"); 
    return -1;
  }
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

int get_column_count(char *first) {
  int count = 1;
  for (size_t i = 0; i < strlen(first); i++)
    if (first[i] == ',') count++;
  return count;
}

void initialize_dtype_array(int *data_type, char *first, int count) {
  char temp[2048], buffer[2048];
  strcpy(temp, first);
  temp[strlen(temp)-1] = '\0';
  for (int i = 0; i < count - 1; i++) {
    int j = 0;
    while (temp[j] != ',') j++;
    temp[j] = '\0';
    data_type[i] = (int)get_type(temp);
    strcpy(buffer, &temp[j+1]);
    strcpy(temp, buffer);
  }
  data_type[count - 1] = (int)get_type(temp);
}

void get_keyval_insert(List *list, int data_type, char *key_buffer, char *val_buffer) {
  // get key to insert
  if (key_buffer == NULL) return;
  char *key = malloc(sizeof(char) * (strlen(key_buffer)+1));
  strcpy(key, key_buffer);

  // get value to insert
  void *value = NULL;
  if (data_type == INT) {
    value = malloc(sizeof(int));
    *(int *)value = atoi(val_buffer);
  } else if (data_type == DOUBLE) {
    value = malloc(sizeof(double));
    *(double *)value = atof(val_buffer);      
  } else if (data_type == CHAR) {
    value = malloc(sizeof(char) * (strlen(val_buffer)+1));
    strcpy(value, val_buffer);
  }

  // insert key-value pair into designated list
  listInsert(list, key, value);
}

void initialize_list_array(List **list_array, FILE *fin, int *data_type, int count) {
  for (int i = 0; i < count; i++) list_array[i] = listInit();
  char *line = malloc(2048 * sizeof(char)), *buffer = malloc(2048 * sizeof(char));
  char *val_buffer = NULL, *key_buffer = NULL;
  while (fgets(line, 2048, fin)) {
    if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
    for (int i = 0; i < count - 1; i++) {
      int j = 0;
      while (line[j] != ',') j++;
      line[j] = '\0';
      strcpy(buffer, line);
      key_buffer = strtok(buffer, "=");
      val_buffer = strtok(NULL, "");
      get_keyval_insert(list_array[i], data_type[i], key_buffer, val_buffer);
      strcpy(buffer, &line[j+1]);
      strcpy(line, buffer);
    }
    strcpy(buffer, line);
    key_buffer = strtok(buffer, "=");
    val_buffer = strtok(NULL, "");
    get_keyval_insert(list_array[count-1], data_type[count-1], key_buffer, val_buffer);
  }
  free(line);
  free(buffer);
}

void sort_list_array(List **list_array, int *data_type, SortType sort_t, int count) {
  for (int i = 0; i < count; i++) {
    listSort(list_array[i], data_type[i], sort_t);
  }
}

void print_list_array(List **list_array, int *data_type, int count) {
  int flag = 1;
  
  // save the head nodes of the lists
  Node **list_heads = malloc(sizeof(Node*));  // to be freed!!!!
  for (int i = 0; i < count; i++) {
    list_heads[i] = list_array[i]->head;
  }

  while (flag) {
    flag = 0;
    Node *node = NULL;
    for (int i = 0; i < count; i++) {
      node = list_array[i]->head;
      if (node) flag = 1;
      else {
        continue;
      }
      list_array[i]->head = list_array[i]->head->next;

      if (data_type[i] == CHAR)
        printf("%s=%s", node->key, (char *)node->val);
      else if (data_type[i] == INT) 
        printf("%s=%d", node->key, *((int *)(node->val)));
      else if (data_type[i] == DOUBLE)
        printf("%s=%f", node->key, *((double *)(node->val)));
      
      if (i == count-1) printf("\n");
      else printf(",");
    }
  }
  
  // recover head nodes of lists
  for (int i = 0; i < count; i++) {
    list_array[i]->head = list_heads[i];
  }
  free(list_heads);
}

void free_list_array(List **list_array, int count) {
  for (int i = 0; i < count; i++)
    listFree(list_array[i]);
}

int ui_cmd(char *argv[]) {
  SortType sort_t = get_order(argv[2]);
  FILE *fin = fopen(argv[1], "r");
  if (fin == NULL) {
    fprintf(stderr, "Error opening file: %s\n", argv[1]);
    return -1;
  }
  char *line = malloc(sizeof(char) * 2048);
  if (fgets(line, 2048, fin) == NULL) {
    free(line);
    return 0;
  }
  printf("%s", line); // output the firstline of the sorted csv
  int column = get_column_count(line);
  int *data_type = malloc((size_t)column * sizeof(int));
  List **list_array = malloc((size_t)column * sizeof(List*));
  initialize_dtype_array(data_type, line, column);
  initialize_list_array(list_array, fin, data_type, column);
  sort_list_array(list_array, data_type, sort_t, column);
  print_list_array(list_array, data_type, column);
  free_list_array(list_array, column);
  free(line);
  free(data_type);
  free(list_array);
  return 0;
}

void init_plugin(Manager *m) {
  // exposing
  register_hook(m, ui_cmd, "csv");
  fprintf(stderr, "plugin-csv: Registration successful\n");
}
