#ifndef GLOBAL_H
#define GLOBAL_H

#include "mumsh.h"

#define _XOPEN_SOURCE 700
#define MAX_LINE 1025
#define MAX_COM 1025
#define QUO_PAIR 255

// define error prompt
#define EP_NO_PROGRAM ": command not found\n"
#define EP_NO_INPUT_FILE ": No such file or directory\n"
#define EP_NO_PERMISSION ": Permission denied\n"
#define EP_DUP_INPUT_REDIR "error: duplicated input redirection\n"
#define EP_DUP_OUTPUT_REDIR "error: duplicated output redirection\n"
#define EP_SYNTAX "syntax error near unexpected token `"
#define EP_MM_PROGRAM "error: missing program\n"
#define EP_NO_DIRECTORY ": No such file or directory\n"

#define PARENT 0
#define CHILD 1

extern int in_redir, out_redir;
static char old_dir[MAX_LINE];
extern __pid_t parent_id;
extern int forks;
extern int ctrl_c;
extern int in_quotes[MAX_LINE];
extern int quote_pair[QUO_PAIR];
extern int quote_num;
extern int status_ok;
extern int tmpin, tmpout;
extern int fd_recovered;
extern int job_id;
extern int is_background;
extern __pid_t bg_pid[MAX_LINE];
extern char *bg_line[MAX_LINE];
extern char ***commands;
extern char *line;

enum Exit_Code
{
    EXIT_NORMAL,
    EXIT_NO_PROGRAM,
    EXIT_NO_INPUT_FILE,
    EXIT_NO_PERMISSION,
    EXIT_DUP_INPUT_REDIR,
    EXIT_DUP_OUTPUT_REDIR,
    EXIT_SYNTAX,
    EXIT_MM_PROGRAM,
    EXIT_NO_DIRECTORY
};

#endif
