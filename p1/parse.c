#include "parse.h"

char* isLineNull(char* arg)
{
    if(!arg) return NULL;
    for(int i = 0; i < (int)strlen(arg); i++)
    {
        if(!isspace(arg[i])) return &arg[i];
    }
    return NULL;
}

char* lastCommand(char*** commands, int command_count)
{
    int i = 0;
    char* last = NULL;
    while(commands[command_count - 1][i] != NULL)
    {
        last = commands[command_count - 1][i];
    }
    return last;
}

int getArgNum(char** com)
{
    int num = 0;
    for(int i = 0; i < MAX_COM; i++)
    {
        if(com[i] == NULL)
        {
            num = i;
            break;
        }
    }
    return num;
}

int createCommand(char *current, int *command_count)
{
    int arg_count = 0;
    commands[*command_count] = malloc(MAX_COM*sizeof(char*));
    memset(commands[*command_count], '\0', MAX_COM);
    current = isLineNull(current);
    char *command = strtok(current, " ");
    while(command)
    {
        commands[*command_count][arg_count] = command;
        arg_count++;
        command = strtok(NULL, " ");
    }
    (*command_count)++;
    return arg_count;
}

void noSpaceProcess(char *left, char *middle)
{
    int pos = -1;
    for(int i = (int)strlen(left) - 1; i >= 0 ; i--)
    {
        if(isspace(left[i]))
        {
            pos = i;
            break;
        }
    }
    char temp[MAX_LINE];
    strcpy(temp, &left[pos+1]);
    strcpy(&temp[strlen(temp)], middle);
    strcpy(middle, temp);
    left[pos+1] = '\0';
    return;
}

char*** readCommand(char *line)
{
    int command_count = 0, arg_count = 0, new_command_flag = 1;
    commands = (char ***)malloc(MAX_COM*sizeof(char**));
    memset(commands, '\0', MAX_COM);
    if(isLineNull(line) == NULL)
    {
        commands[0] = NULL;
        return commands;
    }

    char *left, *middle, *right;
    for(int i = 0; i < quote_num; i++)
    {
        if(quote_pair[i] == 1)
        {
            left = strtok(line, "\'");
            middle = strtok(NULL, "\'");
            right = strtok(NULL, "");
        }
        else if(quote_pair[i] == 2)
        {
            left = strtok(line, "\"");
            middle = strtok(NULL, "\"");
            right = strtok(NULL, "");
        }
        if(isLineNull(left) != NULL)
        {
            if(!isspace(left[strlen(left) - 1]))
            {
                noSpaceProcess(left, middle);
            }
            if(isLineNull(left) != NULL)
            {
                char *current = strtok(left, "|");
                char *rest = strtok(NULL, "");
                current = isLineNull(current);
                if(new_command_flag == 0)
                {
                    char *temp = strtok(current, " ");
                    char *temp_rest = strtok(NULL, "");
                    while(temp)
                    {
                        commands[command_count - 1][arg_count] = temp;
                        arg_count++;
                        temp = strtok(temp_rest, " ");
                        temp_rest = strtok(NULL, "");
                    }
                    current = strtok(rest, "|");
                    rest = strtok(NULL, "");
                }
                while(current)
                {
                    arg_count = createCommand(current, &command_count);
                    current = strtok(rest, "|");
                    rest = strtok(NULL, "");
                }
                new_command_flag = 0;
            }
        }
        if(new_command_flag == 1)
        {
            arg_count = 0;
            commands[command_count] = malloc(MAX_COM*sizeof(char*));
            memset(commands[command_count], '\0', MAX_COM);
            commands[command_count][0] = middle;
            arg_count++;
            command_count++;
            new_command_flag = 0;
        }
        else
        {
            commands[command_count - 1][arg_count] = middle;
            arg_count++;
        }
        line = right;
        if(getFirst(line) == '|')
        {
            new_command_flag = 1;
            int j = 0;
            for(j = 0; j < (int)strlen(line); j++)
            {
                if(line[j] == '|') break;
            }
            char temp[MAX_LINE] = {'\0'};
            strcpy(temp, &line[j+1]);
            strcpy(&line[0], temp);
        }
        line = isLineNull(line);
        if(isLineNull(line) != NULL)
        {
            char temp[MAX_LINE] = {'\0'};
            strcpy(temp, line);
            strcpy(&line[1], temp);
            line[0] = ' ';
        }
    }
    if(getFirst(line) == '|') new_command_flag = 1;
    if(isLineNull(line) == NULL) return commands;
    char *current = strtok(line, "|");
    char *rest = strtok(NULL, "");
    if(isLineNull(current) == NULL)
    {
        current = strtok(rest, "|");
        rest = strtok(NULL, "");
    }
    while(current)
    {
        if(new_command_flag)
        {
            commands[command_count] = malloc(MAX_COM*sizeof(char*));
            memset(commands[command_count], '\0', MAX_COM);
            arg_count = 0;
            command_count++;
        }
        current = isLineNull(current);
        char *command = strtok(current, " ");
        while(command)
        {
            commands[command_count - 1][arg_count] = command;
            arg_count++;
            command = strtok(NULL, " ");
        }
        current = strtok(rest, "|");
        rest = strtok(NULL, "");
        new_command_flag = 1;
    }
    // printf("%s %s \n", commands[0][0], commands[0][1]);
    return commands;
}
