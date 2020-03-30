#include "csapp.h"

/* $begin forkprob0 */
int main() 
{
    int x = 1;

    int pid = Fork();
    fprintf(stderr,"I got pid=%d\n", pid);
    
    if (pid == 0) {
        x = x + 1;
        printf("p1: pid = %d, x=%d\n", pid, x);  //line:ecf:forkprob0:childfork
    }
    
    x = x-1;
    printf("p2: pid = %d, x=%d\n", pid, x);      //line:ecf:forkprob0:parentfork
    exit(0);
}
/* $end forkprob0 */

