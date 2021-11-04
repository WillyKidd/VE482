#include "lab5_dlist.h"
// #include "lab5_dlist.c"

dlistValueType getValueType(char *fileName)
{
  char arg[1024], *type;
  strcpy(arg, fileName);
  type = strtok(arg, "_");
  type = strtok(NULL, ".");
  if(!strcmp(type, "int")) return DLIST_INT;
  if(!strcmp(type, "double")) return DLIST_DOUBLE;
  if(!strcmp(type, "char*")) return DLIST_STR;
  return DLIST_UNKOWN;
}

dlistSortMethod getSortMethod(char *fileName)
{
  unsigned int pos = 0;
  dlistSortMethod order = DLIST_SORT_UNKOWN;
  for(; pos < strlen(fileName); pos++)
  {
      if(fileName[pos] == '_')
      {
          fileName[pos] = '\0';
          break;
      }
  }
  if(!strcmp(fileName, "inc")) order = DLIST_SORT_INC;
  else if(!strcmp(fileName, "dec")) order = DLIST_SORT_DEC;
  else if(!strcmp(fileName, "rand")) order = DLIST_SORT_RAND;
  if(pos > 0) fileName[pos] = '_';
  return order;
}

void getKeyFromLine(char *key, char *line)
{
  char arg[1024], *temp;
  strcpy(arg, line);
  temp = strtok(arg, "=");
  strcpy(key, temp);
}

void getValueFromLine(dlistValue *value, char *line, dlistValueType type)
{
  char arg[1024], *temp;
  strcpy(arg, line);
  strtok(arg, "=");
  temp = strtok(NULL, "\n");
  if(type == DLIST_INT) value->intValue = (int)strtol(temp, NULL, 10);
  else if (type == DLIST_DOUBLE) value->doubleValue = (double)strtod(temp, NULL);
  else if (type == DLIST_STR) strcpy(value->strValue, temp);
}

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
    getKeyFromLine(key, line);
    getValueFromLine(&value, line, type);
    dlistAppend(list, key, value);
  }
  fclose(fp);
  dlistSort(list, listDst, method);
  // dlistSort(list, listDst, method);
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
