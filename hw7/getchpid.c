#include "pm.h"
#include "mproc.h"

int getnchpid(int n, pid_t *childpid) {
register struct mproc *rmc; // pointer to nth child process
if (childpid == NULL) return -1;
if (n > NR_PROCS) return -1;
rmc = &mproc[n];
if (rmc->mp_parent != who_p) return -1;
*childpid = rmc->mp_pid;
return OK;
}

int getnchpid(int n, pid_t *childpid) {
    register struct mproc *rmc; // pointer to nth child process
    if (childpid == NULL) return -1;
    if (n > NR_PROCS) return -1;
    rmc = &mproc[n];
    if (rmc->mp_parent != who_p) return -1;
    *childpid = rmc->mp_pid;
    return OK;
}

int do_getchpids(int n, pid_t *childpid) {
    int index;
    for (index = 0; index < n; index++) {
        if (getnchpid(index, childpid+index) != OK) {
            index = -1;
            break;
        }
    }
    return index;
}

int main() {
    int n = 10;
    pid_t pid_children[10];
    pid_t pid_result[10];
    for (int i = 0; i < n; i++) {
        pid_t pid_c = fork();
        if (pid_c == 0) {
            sleep(10);
            return 0;
        } else {
            pid_children[i] = pid_c;
        }
    }
    do_getchpids(n, pid_result);
    for (int i = 0; i < n; i++) {
        printf("The number %d child with pid: %d,
        do_getchpids returned %d\n",
        i+1, pid_children[i], pid_result[i]);
    }
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }
    return 0;
}
