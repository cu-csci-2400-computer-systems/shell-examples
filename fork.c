#include "csapp.h"

/* $begin fork */
/* $begin wasidefork */
int main() 
{
    pid_t pid;
    int x = 1;

    pid = Fork(); //line:ecf:forkreturn
    if (pid == 0) {  /* Child */
        x = x + 1;
        printf("child : x=%d\n", x); //line:ecf:childprint
        exit(0);
    }

    /* Parent */
    x = x - 1;
    printf("parent: x=%d\n", x); //line:ecf:parentprint
    exit(0);
}
/* $end fork */
/* $end wasidefork */

