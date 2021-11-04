#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "list.h"

typedef int (*hook_t)(char *argv[]);
typedef struct _Handle Handle;
typedef struct _Manager Manager;

Manager *new_manager();

void free_manager(Manager *m);

void register_hook(Manager *m, hook_t hook, char *type);

int apply_hook(Manager *m, char *type, char **argv);

#endif // PLUGIN_MANAGER_H
