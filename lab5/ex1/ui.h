#ifndef UI_H
#define UI_H

#define MAX_ARG 1024
#define MAX_LINE 2048

#include "sort.h"

extern char *sort_type[3];
extern char *value_type[3];

void ui_menu();
int ui_cmd(int argc, char *argv[]);
void ui_menu();
ValueType get_type(char *arg);
SortType get_order(char *arg);
void fill_list_from_file(List *list, char *file_path, ValueType value_t);
void listPrint(char *dest_file, List *list, ValueType value_t);

#endif // UI_H
