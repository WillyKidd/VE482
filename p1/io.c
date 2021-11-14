#include "io.h"

void initQuote()
{
    for(int i = 0; i < MAX_LINE; i++) in_quotes[i] = 0;
}

char* readInit()
{
    char * line = (char*)malloc(sizeof(char)*MAX_LINE);
    memset(line, '\0', MAX_LINE);
    return line;
}

char getFirst(char *line)
{
    if(!line) return '\0';
    for(unsigned int i = 0; i < strlen(line); i++)
    {
        if(!isspace(line[i])) return line[i];
    }
    return '\0';
}

char getLast(char *line)
{
    char last = 0;
    for(unsigned int i = 0; i < strlen(line); i++)
    {
        if(!isspace(line[i])) last = line[i];
    }
    return last;
}

char getLastLast(char *line)
{
    char last = 0, lastlast = 0;
    for(unsigned int i = 0; i < strlen(line); i++)
    {
        if(!isspace(line[i]))
        {
            char temp = last;
            last = line[i];
            lastlast = temp;
        }
    }
    return lastlast;
}

void markInside(int begin, int end)
{
    for(int i = begin; i <= end; i++) in_quotes[i] = 1;
}

int checkQuotes(char *line)
{
    initQuote();
    quote_num = 0;
    int sq = 0, dq = 0, pair_num = 0, sq_pos = 0, dq_pos = 0;
    for(int i = 0; i < (int)strlen(line); i++)
    {
        if(line[i] == '\"' && sq != 1)
        {
            dq++;
            if(dq == 1) dq_pos = i;
            if(dq == 2)
            {
                dq = 0;
                quote_pair[pair_num] = 2;
                markInside(dq_pos, i);
                pair_num++;
                quote_num++;
            }
        }
        if(line[i] == '\'' && dq != 1)
        {
            sq++;
            if(sq == 1) sq_pos = i;
            if(sq == 2)
            {
                sq = 0;
                quote_pair[pair_num] = 1;
                markInside(sq_pos, i);
                pair_num++;
                quote_num++;
            }
        }
    }
    if(sq || dq) return 1;
    else return 0;
}

void readInput(char *line)
{
    char last, lastlast;
    if(fgets(line, MAX_LINE, stdin) == NULL)
    {
        if(ctrl_c == 0)
        {
            exitPrompt(EXIT_NORMAL, NULL);
            exit(0);
        }
        line[0] = '\0';
        return;
    }
    last = getLast(line);
    lastlast = getLastLast(line);
    char *ret_fgets;
    int cq = checkQuotes(line);
    while((last == '<' || last == '|' || (last == '>' && lastlast != '>')) || cq == 1)
    {
        printf("> ");
        fflush(stdout);
        char temp[MAX_LINE];
        ret_fgets = fgets(temp, MAX_LINE, stdin);
        while(ret_fgets == NULL)
        {
            clearerr(stdin);
            ret_fgets = fgets(temp, MAX_LINE, stdin);
        }
        if(cq != 1) line[strlen(line) - 1] = '\0';
        strcat(line, temp);
        last = getLast(line);
        lastlast = getLastLast(line);
        cq = checkQuotes(line);
    }
    if(strlen(line) >= 2)
    {
        if(line[strlen(line) - 2] == '&')
        {
            printf("[%d] %s\n", job_id, line);
            fflush(stdout);
            is_background = 1;
            bg_line[job_id - 1] = (char *)malloc(sizeof(char) * MAX_LINE);
            memset(bg_line[job_id - 1], 0, MAX_LINE);
            line[strlen(line) - 1] = '\0';
            strcpy(bg_line[job_id - 1], line);
        }
    }
    if(strlen(line) >= 1) line[strlen(line) - 1] = '\0';
    readPreProcess(line);
    checkQuotes(line);
    readPostProcess(line);
    checkQuotes(line);
}

void readPreProcess(char *line)
{
    int length = 0;
    while(length < MAX_LINE)
    {
        if(line[length] == '\0') break;
        if(line[length] == line[length+1] && (line[length] == '\'' || line[length] == '\"'))
        {
            char temp[MAX_LINE];
            strcpy(temp, &line[length+2]);
            strcpy(&line[length], temp);
        }
        length++;
    }
}

void insertSpace(char* l, int pos)
{
    char temp[MAX_LINE];
    strcpy(temp, &l[pos + 1]);
    l[pos + 1] = ' ';
    l[pos+ 2] = '\0';
    strcpy(&l[pos + 2], temp);
}

void readPostProcess(char *line)
{
    char temp[MAX_LINE];
    strcpy(temp, line);
    strcpy(&line[1], temp);
    line[0] = ' ';
    for(int i = 0; i < (int)strlen(line); i++)
    {
        if(line[i] != '>' && line[i] != '<') continue;
        if(line[i] == '<')
        {
            if(in_quotes[i] == 1) continue;
            if(i != 0)
            {
                if(!isspace(line[i - 1]))
                {
                    insertSpace(line, i - 1);
                    checkQuotes(line);
                    i++;
                }
            }
            if(!isspace(line[i + 1]))
            {
                insertSpace(line, i);
                checkQuotes(line);
                i++;
            };
        }
        if(line[i] == '>')
        {
            if(in_quotes[i] == 1) continue;
            if(i != 0)
            {
                if(!isspace(line[i - 1]))
                {
                    insertSpace(line, i - 1);
                    checkQuotes(line);
                    i++;
                }
            }
            if(line[i+1] == '>') i++;
            if(!isspace(line[i + 1]))
            {
                insertSpace(line, i);
                checkQuotes(line);
                i++;
            }
        }
    }
}

void prompt()
{
    fputs("mumsh $ ", stdout);
    fflush(stdout);
}

void exitPrompt(int code, char* error_msg)
{
    status_ok = 0;
    if(!fd_recovered)
    {
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
    }
    switch(code)
    {
        case EXIT_NORMAL:
        {
            status_ok = 1;
            fputs("exit\n", stdout);
            fflush(stdout);
            if(line != NULL)
            {
                free(line);
                line = NULL;
            }
            if(commands != NULL)
            {
                for(int i = 0; i < MAX_COM; i++)
                {
                    if(commands[i] == NULL) break;
                    free(commands[i]);
                }
                free(commands);
                commands = NULL;
            }
            for(int i = 0; i < job_id - 1; i++)
            {
                if(bg_line[i] == NULL) break;
                free(bg_line[i]);
            }
            exit(0);
            break;
        }
        case EXIT_NO_PROGRAM:
            printf("%s", error_msg);
            printf(EP_NO_PROGRAM);
            break;
        case EXIT_NO_INPUT_FILE:
            printf("%s", error_msg);
            printf(EP_NO_INPUT_FILE);
            break;
        case EXIT_NO_PERMISSION:
            printf("%s", error_msg);
            printf(EP_NO_PERMISSION);
            break;
        case EXIT_DUP_INPUT_REDIR:
            printf(EP_DUP_INPUT_REDIR);
            break;
        case EXIT_DUP_OUTPUT_REDIR:
            printf(EP_DUP_OUTPUT_REDIR);
            break;
        case EXIT_SYNTAX:
            printf(EP_SYNTAX);
            printf("%s", error_msg);
            printf("'\n");
            break;
        case EXIT_MM_PROGRAM:
            printf(EP_MM_PROGRAM);
            break;
        case EXIT_NO_DIRECTORY:
            printf("%s", error_msg);
            printf(EP_NO_DIRECTORY);
            break;
    }
    fflush(stdout);
    // exit(code);
}
