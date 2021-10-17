#ifndef IO_H
#define IO_H

#include "global.h"
#include "parse.h"
#include "mumsh.h"

void initQuote();

char* readInit();
// mallocs and memsets line

char getFirst(char *line);

char getLast(char *line);
// returns the last character

char getLastLast(char *line);
// returns the second to last character



int checkQuotes(char *line);
// checks if any quotes unfinished
// returns 1 if quotes unfinished
// quote_pair is a queue that contains paired quotes
// 1 stands for single quotes, 2 stands for double quotes

void readInput(char *line);
// reads input to line

void readPreProcess(char *line);
// preprocesses the line
// changes "\n" to "\0"

void insertSpace(char* l, int pos);

void readPostProcess();
// postprocesses the line
// adds spaces to identify redirection symbols

void prompt();
// prints prompt

void exitPrompt(int code, char* error_msg);
// prints exit prompt according to code
// then exits

#endif
