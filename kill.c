/* $begin kill */
#include "csapp.h"
#include <stdio.h>

int main()
{
    pid_t pid = fork();

    /* Child sleeps until SIGKILL signal received, then dies */
    if (pid  == 0)
    {
        fprintf(stderr, "Child about to pause..\n");
        Pause(); /* Wait for a signal to arrive */
        fprintf(stderr, "control should never reach here!\n");
        exit(0);
    }

    sleep(3);
    /* Parent sends a SIGKILL signal to a child */
    fprintf(stderr, "Parent about to kill child %d\n", pid);
    Kill(pid, SIGKILL);
    exit(0);
}
/* $end kill */
