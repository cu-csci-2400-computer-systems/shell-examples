#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include "csapp.h"

/* $begin signalprob0 */
volatile long counter = 2;

void handler1(int sig)
{
    sigset_t mask, prev_mask;

    Sigfillset(&mask);
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask); /* Block sigs */
    fprintf(stderr,"decremented counter is %ld in process %d\n", --counter, getpid());
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL); /* Restore sigs */

    _exit(0);
}

int main()
{
    pid_t pid;
    sigset_t mask, prev_mask;

    fprintf(stderr, "Initial counter value is %ld in process %d\n", counter, getpid());
    fflush(stdout);

    signal(SIGUSR1, handler1);
    if ((pid = Fork()) == 0)
    {
        //
        // Child process starts infinite loop
        //
        fprintf(stderr,"Child process %d starts infinite loop\n", getpid());
        for (;;)
        {
        };
    }
    sleep(1);
    Kill(pid, SIGUSR1);
    Waitpid(-1, NULL, 0);

    Sigfillset(&mask);
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask); /* Block sigs */
    fprintf(stderr, "incremented counter value is %ld in process %d\n", ++counter, getpid());
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL); /* Restore sigs */

    exit(0);
}
/* $end signalprob0 */
