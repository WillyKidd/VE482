#ifndef UI_H
#define UI_H

#define MAX_ARG 1024
#define MAX_LINE 2048

#include "sort.h"
#include "../src-main/plugin_manager.h"

extern char *sort_type[3];
extern char *value_type[3];

int ui_cmd(char *argv[]);

ValueType get_type(char *arg);

SortType get_order(char *arg);

int fill_list_from_file(List *list, char *file_path, ValueType value_t);

void listPrint(List *list, ValueType value_t);

void init_plugin(Manager *m);

#endif // UI_H
