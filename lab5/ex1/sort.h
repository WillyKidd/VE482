#ifndef SORT_H
#define SORT_H

#include "list.h"
#include <string.h>
#include <stdlib.h>

typedef enum SortType{
  INC = 0,
  DEC = 1,
  RAN = 2,
  ERROR_SORT_TYPE = -1
} SortType;

typedef enum ValueType {
  INT = 0,
  DOUBLE = 1,
  CHAR = 2,
  ERROR_VALUE_TYPE = -1
} ValueType;

void listSort(List *l, ValueType dtype, SortType order);

#endif // SORT_H
