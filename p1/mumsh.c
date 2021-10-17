#include "mumsh.h"

__pid_t parent_id;
int forks = 0;
int ctrl_c = 0;
int quote_pair[QUO_PAIR];
int in_quotes[MAX_LINE];
int quote_num = 0;
int status_ok = 1;
int tmpin, tmpout;
int fd_recovered;
int job_id = 1;
int is_background = 0;
__pid_t bg_pid[MAX_LINE];
char *bg_line[MAX_LINE];
static volatile sig_atomic_t jump_active = 0;
static sigjmp_buf env;
char ***commands = NULL;
char *line = NULL;
int in_redir = 0, out_redir = 0;

void sigintHandler()
{
    ctrl_c = 1;
    pid_t self_id = getpid();
    if(self_id != parent_id)
    {
        exit(0);
    }
    else
    {
        fflush(stdout);
        if(!fd_recovered)
        {
            dup2(tmpin, 0);
            dup2(tmpout, 1);
            close(tmpin);
            close(tmpout);
            fd_recovered = 1;
        }
        printf("\n");
        fflush(stdout);
        for(int i = 0; i < forks; i++)
        {
            wait(NULL);
        }
        if(line != NULL){
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
        siglongjmp(env, 42);
    }
}

void initializeVariables()
{
    fd_recovered = 1;
    status_ok = 1;
    ctrl_c = 0;
    is_background = 0;
    forks = 0;
    in_redir = 0;
    out_redir = 0;
}

int main()
{
    
    int loop = 0;
    struct sigaction s_act, old_act;
    parent_id = getpid();
    line = NULL;
    s_act.sa_handler = sigintHandler;
    old_dir[0] = '\0';
    while(1)
    {
        if (sigsetjmp(env, 1) == 42) 
        {
            if(line != NULL) free(line);
            if(commands != NULL)
            {
                for(int i = 0; i < MAX_COM; i++)
                {
                    if(commands[i] == NULL) break;
                    free(commands[i]);
                }
                free(commands);
            }
        }
        jump_active = 1; 
        for(int i = 0; i < job_id - 1; i++)
        {
            pid_t pid_temp;
            pid_temp = waitpid(-1, NULL, WNOHANG);
        }
        fflush(stdout);
        initializeVariables();
        sigaction(SIGINT, &s_act, &old_act);
        line = readInit();
        prompt();
        readInput(line);
        commands = readCommand(line);
        if(status_ok) execute(&s_act, &old_act);
        for(int i = 0; i < MAX_COM; i++)
        {
            if(commands[i] == NULL) break;
            free(commands[i]);
        }
        clearerr(stdin);
        free(commands);
        commands = NULL;
        free(line);
        line = NULL;
        if(is_background) job_id++;
        loop++;
        if(!fd_recovered)
        {
            dup2(tmpin, 0);
            dup2(tmpout, 1);
            close(tmpin);
            close(tmpout);
            fd_recovered = 1;
        }
    }
    return 0;
}
