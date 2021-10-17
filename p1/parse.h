#ifndef PARSE_H
#define PARSE_H

#include "mumsh.h"

char* isLineNull(char* arg);

char* lastCommand(char*** commands, int command_count);

int getArgNum(char** com);

char*** readCommand(char *line);

#endif
