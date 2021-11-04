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

void fill_list_from_file(List *list, char *file_path, ValueType value_t) {
  char *line = malloc(sizeof(char)*MAX_LINE);
  memset(line, 0, MAX_LINE);
  char *val_buffer = NULL, *key_buffer = NULL;
  FILE *fin = fopen(file_path, "r");
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
}

void listPrint(char *dest_file, List *list, ValueType value_t) {
  FILE *fout = fopen(dest_file, "w");
  Node *node = list->head;
  while (node) {
    if (value_t == CHAR) {
      fprintf(fout, "%s=%s\n", node->key, (char *)node->val);
    } else if (value_t == INT)
      fprintf(fout, "%s=%d\n", node->key, *((int *)(node->val)));
    else if (value_t == DOUBLE)
      fprintf(fout, "%s=%f\n", node->key, *((double *)(node->val)));
    node = node->next;
  }
  fclose(fout);
}

int ui_cmd(int argc, char *argv[]) {
  ValueType value_t = get_type(argv[1]);
  SortType sort_t = get_order(argv[2]);
  
  // read key value pair from file
  printf("reading %s\n", argv[1]);
  List *list = listInit();
  fill_list_from_file(list, argv[1], value_t);

  // sort list
  printf("Sorting elements\n");
  listSort(list, value_t, sort_t);

  char dest_file[MAX_ARG] = {0};
  sprintf(dest_file, "%s_%s.txt", sort_type[sort_t], value_type[value_t]);
  
  // write to file
  printf("writing %s\n", dest_file);
  listPrint(dest_file, list, value_t);
  listFree(list);
  return 0;
}

void ui_menu() {
  printf("===================================================\n");
  printf("Welcome to VE482 Lab5 EX1 UI Menu.\n");
  while (1) {
    printf("***************************************************\n"
        "usage: [ [input filename] [sort type] | exit ]\n"
        "input filename: <sorttype>_<datatype>.txt\n"
        "sort type: rand, inc, dec\n"
        "data type: int, double, char*\n"
        "exit: exit this program\n"
        "sample input: rand_int.txt inc\n"
        "***************************************************\n"
        "> ");
    fflush(NULL);

    // get user input
    char user_input[MAX_LINE];
    if (fgets(user_input, MAX_LINE, stdin) == NULL) {
      printf("Error: unable to get user input!\n");
      break;
    }

    // get first argument
    char *temp = strtok(user_input, " \n"), *argv[3];
    argv[0] = NULL;
    if (temp == NULL) {
      printf("Error: cannot get first argument!\n");
    }
    argv[1] = (char *)malloc(sizeof(char) * (strlen(temp)+1));
    strcpy(argv[1], temp);

    // exit command
    if (!strcmp(argv[1], "exit")) {
      free(argv[1]);
      break;
    }
    
    // get second argument
    temp = strtok(NULL, "\n");
    if (temp == NULL) {
      printf("Error: cannot get second argument!\n");
    }
    argv[2] = (char *)malloc(sizeof(char) * (strlen(temp)+1));
    strcpy(argv[2], temp);

    // execute
    ui_cmd(3, argv);
    free(argv[1]);
    free(argv[2]);
  }
}
