#include "plugin_manager.h"

typedef struct _Handle {
  hook_t hook; // function that gets the job done
  char type[32]; // name of the file type (txt or csv)
  Handle *next;
} Handle;

/**
 * a linked list that stores all the handle
 */
typedef struct _Manager {
  Handle *first;
} Manager;

Manager *new_manager() {
  Manager *m = malloc(sizeof(Manager));
  m->first = NULL;
  return m;
}

void free_manager(Manager *m) {
  Handle *first = m->first;
  while (first) {
    Handle *temp = first;
    first = first->next;
    free(temp);
  }
  free(m);
}

void register_hook(Manager *m, hook_t hook, char *type) {
  Handle *handle_node = malloc(sizeof(Handle));
  handle_node->hook = hook;
  strcpy(handle_node->type, type);
  handle_node->next = m->first;
  m->first = handle_node;
}

int apply_hook(Manager *m, char *type, char **argv) {
  Handle *handle_node = m->first;
  while (handle_node) {
    if (!strcmp(handle_node->type, type)) {
      int rt_val = handle_node->hook(argv);
      return rt_val;
    }
    handle_node = handle_node->next;
  }
  printf("Manager: failed to find plugin suitable for file type: .%s\n", type);
  return -1;
}
