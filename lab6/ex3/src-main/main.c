#include <dlfcn.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plugin_manager.h"
// #include "plugin_manager.c"

typedef void(*regfn_t)(Manager *);

int pluginRegister(Manager *m) {
  DIR *dir;
  struct dirent *dp;
  int plugin_found = -1;
  
  // discover all plugins in the folder ./plugins/
  if ((dir = opendir("./plugins/")) != NULL) {
    char *file_name = malloc(2048*sizeof(char));
    while ((dp = readdir(dir)) != NULL) {
      memset(file_name, '\0', 2048);
      strcpy(file_name, "./plugins/");
      strcat(file_name, dp->d_name);
      // look for .so files in directory ./plugins
      if (!strcmp(&file_name[strlen(file_name)-3], ".so")) {
        plugin_found = 1;
        // obtain library handle
        void *handle = dlopen(file_name, RTLD_NOW);
        if (handle == NULL) {
          fprintf(stderr, "Error opening library:\n");
          fprintf(stderr, "%s\n", dlerror());
          closedir(dir);
          free(file_name);
          return(-1);
        }
        dlerror();   // empty previous errors
        void (*funcp)(void);
        *(void **)(&funcp) = dlsym(handle, "init_plugin");
        if (funcp == NULL) {
          fprintf(stderr, "Error obtaining address of symbol:\n");
          fprintf(stderr, "%s\n", dlerror());
          closedir(dir);
          free(file_name);
          return -1;
        }
        ((regfn_t)funcp)(m); // register
      }
    }
    free(file_name);
  } else { // cannot open directory
    fprintf(stderr, "Error opening folder \"./plugins\", make sure it exists!\n");
    return -1;
  }
  closedir(dir);
  return plugin_found;
}

int main(int argc, char *argv[]) {
  if (argc < 0) {
    fprintf(stderr, 
      "Eror: missing arguments!\n"
      "Usage: ./main [Input File Name] [Sorting Type]\n"
      "Supported file types: .txt\n"
    );
    return -1;
  }

  // discover and register plugins
  Manager *m = new_manager();
  if(!pluginRegister(m)) {
    free_manager(m);
    return -1;
  }

  // get file type
  char temp[2048], type[32];
  strcpy(temp, argv[1]);
  strtok(temp, ".");
  strcpy(type, strtok(NULL, ""));

  // start execution
  int ret_val = apply_hook(m, type, argv);
  if (ret_val < 0) fprintf(stderr, "Error: execution failed!\n");
  
  // free manager
  free_manager(m);
  return 0;
}
