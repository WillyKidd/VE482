#include "exec.h"

void execCD(char **com)
{
    int ret, argc = getArgNum(com);
    if(argc < 2 || strcmp(com[1], "~") == 0)
    {
        getcwd(old_dir, MAX_LINE);
        ret = chdir(getenv("HOME"));
        return;
    }
    if(strcmp(com[1], "-") == 0)
    {
        if(old_dir[0] == '\0')
        {
            printf("cd : OLDPWD not set\n");
            return;
        }
        else
        {
            char temp[MAX_LINE];
            strcpy(temp, old_dir);
            getcwd(old_dir, MAX_LINE);
            ret = chdir(temp);
            execPWD();
            return;
        }
    }
    else
    {
        ret = chdir(com[1]);
    }
    if(ret == -1) exitPrompt(EXIT_NO_DIRECTORY, com[1]);
    return;
}

void execPWD()
{
    char dir[MAX_LINE];
    getcwd(dir, MAX_LINE);
    printf("%s\n", dir);
    fflush(stdout);
}

void shiftByTwo(char **com, int begin_point, int arg_num)
{
    for(int i = begin_point; i < arg_num - 2; i++)
    {
        com[i] = com[i + 2];
    }
    com[arg_num - 2] = NULL;
}

void executeRedirect(char **com)
{
    int arg_num = getArgNum(com);
    for(int i = 0; i < arg_num; i++)
    {
        if(strcmp(com[i], "<") == 0)
        {
            if(com[i+1] == NULL) exitPrompt(EXIT_SYNTAX, "|");
            if(!strcmp(com[i+1], ">") || !strcmp(com[i+1], ">>") || !strcmp(com[i+1], "<"))
            {
                exitPrompt(EXIT_SYNTAX, com[i+1]);
                return;
            }
            if(in_redir == 1)
            {
                exitPrompt(EXIT_DUP_INPUT_REDIR, NULL);
                return;
            }
            int fdin = open(com[i+1], O_RDONLY);
            if(fdin < 0)
            {
                exitPrompt(EXIT_NO_INPUT_FILE, com[i+1]);
                return;
            }
            dup2(fdin, STDIN_FILENO);
            close(fdin);
            in_redir++;
            shiftByTwo(com, i, arg_num);
            i--;
            arg_num -= 2;
            fd_recovered = 0;
        }
        else if(strcmp(com[i], ">") == 0 || strcmp(com[i], ">>") == 0)
        {
            if(com[i+1] == NULL)
            {
                exitPrompt(EXIT_SYNTAX, "|");
                return;
            }
            if(!strcmp(com[i+1], ">") || !strcmp(com[i+1], ">>") || !strcmp(com[i+1], "<"))
            {
                exitPrompt(EXIT_SYNTAX, com[i+1]);
                return;
            }
            if(out_redir == 1)
            {
                exitPrompt(EXIT_DUP_OUTPUT_REDIR, NULL);
                return;
            }
            int fdout = -1;
            if(!strcmp(com[i], ">")) fdout = open(com[i+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
            else if(!strcmp(com[i], ">>")) fdout = open(com[i+1], O_APPEND | O_CREAT | O_WRONLY, S_IRWXU);
            if(fdout < 0)
            {
                exitPrompt(EXIT_NO_PERMISSION, com[i+1]);
                return;
            }
            int dupret = dup2(fdout, STDOUT_FILENO);
            if(dupret == -1) perror("Dup2 failed\n");
            close(fdout);
            out_redir++;
            shiftByTwo(com, i, arg_num);
            i--;
            arg_num -= 2;
            fd_recovered = 0;
        }
    }
}

int execute(struct sigaction *s_act, struct sigaction *old_act)
{
    char **com;
    forks = 0;
    int fpipe[2];
    int fpin_temp = 0;
    int command_count = 0;
    for(int i = 0; i < MAX_COM; i++)
    {
        if(commands[i] == NULL)
        {
            command_count = i;
            break;
        }
    }
    for(int i = 0; i < command_count; i++)
    {
        if(commands[i] == NULL) break;
        tmpin = dup(0);
        tmpout = dup(1);
        pid_t pid;
        com = commands[i];
        if(com[0] ==  NULL)
        {
            exitPrompt(EXIT_MM_PROGRAM, NULL);
            return 0;
        }
        in_redir = 0;
        out_redir = 0;
        pipe(fpipe);
        if(i != 0)
        {
            dup2(fpin_temp, STDIN_FILENO);
            in_redir++;
            fd_recovered = 0;
        }
        if(i != command_count - 1)
        {
            dup2(fpipe[1], STDOUT_FILENO);
            out_redir++;
            fd_recovered = 0;
        }
        executeRedirect(com);
        fd_recovered = 0;
        if(com[0] ==  NULL)
        {
            exitPrompt(EXIT_MM_PROGRAM, NULL);
            return 0;
        }
        if(status_ok)
        {
            if(strcmp(com[0], "jobs") == 0)
            {
                for(int i = 0; i < job_id - 1; i++)
                {
                    if(waitpid(bg_pid[i], NULL, WNOHANG) == 0) // still running
                    {
                        printf("[%d] running %s\n", i+1, bg_line[i]);
                    }
                    else
                    {
                        printf("[%d] done %s\n", i+1, bg_line[i]);
                    }
                }
                fflush(stdout);
                return 0;
            }
            if(strcmp(com[0], "exit") == 0)
            {
                for(int i = 0; i < forks; i++)
                {
                    wait(NULL);
                }
                exitPrompt(0, NULL);
            }
            if(strcmp(com[0], "cd") == 0) execCD(com);
            else
            {
                pid = fork();
                if(is_background)
                {
                    bg_pid[job_id - 1] = pid;
                }
                forks++;
                if(pid == -1)
                {
                    perror("Error forking\n");
                    return -1;
                }
                if(pid == 0) // child
                {
                    if(!is_background) sigaction(SIGINT, s_act, old_act);
                    else signal(SIGINT, SIG_IGN);
                    if(strcmp(com[0], "pwd") == 0) execPWD();
                    else
                    {
                        int ret = execvp(com[0], com);
                        if(ret < 0)
                        {
                            exitPrompt(EXIT_NO_PROGRAM, com[0]);
                            exit(EXIT_NO_PROGRAM);
                            return 0;
                        }
                    }
                    exit(0);
                }
                if(pid > 0) // parent
                {
                    if(fpin_temp) close(fpin_temp);
                    close(fpipe[1]);
                    fpin_temp = fpipe[0];
                    if(i == command_count - 1)
                    {
                        fpin_temp = 0;
                        close(fpipe[0]);
                    }
                    dup2(tmpin, 0);
                    dup2(tmpout, 1);
                    close(tmpin);
                    close(tmpout);
                    fd_recovered = 1;
                }
            }
        }
    }
    if(is_background) return 1;
    if(!is_background)
    {
        for(int i = 0; i < forks; i++)
        {
            wait(NULL);
        }
    }
    return 1;
}
