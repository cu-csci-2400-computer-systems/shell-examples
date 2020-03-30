/* $begin kill */
#include "csapp.h"
#include <stdio.h>

int main() 
{
    pid_t pid;

    /* Child sleeps until SIGKILL signal received, then dies */   
    if ((pid = Fork()) == 0) {
        fprintf(stderr, "Child about to pause..\n");
        Pause();  /* Wait for a signal to arrive */  
        fprintf(stderr, "control should never reach here!\n");
        exit(0);
    }

    /* Parent sends a SIGKILL signal to a child */
    fprintf(stderr,"Parent about to kill child %d\n", pid);
    Kill(pid, SIGKILL);
    exit(0);
}
/* $end kill */
