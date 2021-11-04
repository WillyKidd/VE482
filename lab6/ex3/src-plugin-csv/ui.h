#ifndef UI_H
#define UI_H

#define MAX_ARG 1024
#define MAX_LINE 2048

#include "sort.h"
#include "../src-main/plugin_manager.h"

extern char *sort_type[3];
extern char *value_type[3];

int ui_cmd(char *argv[]);

ValueType get_type(const char *arg);

SortType get_order(char *arg);

int get_column_count(char *first);

void initialize_dtype_array(int *data_type, char *first, int count);

void initialize_list_array(List **list_array, FILE *fin, int *data_type, int count);

void get_keyval_insert(List *list, int data_type, char *key_buffer, char *val_buffer);

void init_plugin(Manager *m);

#endif // UI_H
