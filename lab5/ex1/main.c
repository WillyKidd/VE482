#include "lab5_dlist.h"

int run(char *fileName, char *order) {
  FILE *fp = fopen(fileName, "r");
  if (fp == NULL) exit(EXIT_FAILURE);
  dlistValueType type = getValueType(fileName);
  dlistSortMethod method = getSortMethod(order);
  if (type == DLIST_UNKOWN || method == DLIST_SORT_UNKOWN) exit(EXIT_FAILURE);
  dlist listDst = createDlist(type), list = createDlist(type);
  char line[1024], key[256];
  dlistValue value;
  while (fgets(line, sizeof(line), fp)) {
    getKeyFromLine(&key, line);
    getValueFromLine(&value, line, type);
    dlistAppend(list, key, value);
  }
  fclose(fp);
  dlistSort(list, listDst, method);
  dlistSort(list, listDst, method);
  dlistPrint(listDst);
  dlistFree(list);
  dlistFree(listDst);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 3) return -1;
  run(argv[1], argv[2]);
  return 0;
}
