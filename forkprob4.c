/* $begin forkprob4 */
#include "csapp.h"

//
// Demonstrate tha fork() duplicates the stack. Processes created
// in routine doit() will return (to main) an print a message there
// as well.
//

void doit()
{
    Fork();
    Fork();
    fprintf(stderr, "Process %d does a return from funciton doit\n", getpid());
    return;
}

int main()
{
    doit();
    fprintf(stderr, "Process %d exits in main\n", getpid());
    exit(0);
}
/* $end forkprob4 */
