/* $begin forkprob7 */
#include "csapp.h"
int counter = 1;

int main() 
{
    if (fork() == 0) {
        counter--; 
        fprintf(stderr,"Child counter is %d\n", counter);
        exit(0);
    }
    else {
	Wait(NULL); 
        counter = counter + 1;
	fprintf(stderr,"Parent counter = %d\n", counter);
    }
    exit(0);
}
/* $end forkprob7 */
