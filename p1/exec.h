#ifndef EXEC_H
#define EXEC_H

#include "io.h"

void execCD(char **com);

void execPWD();

void executeRedirect(char **com);

int execute(struct sigaction *s_act, struct sigaction *old_act);

#endif
