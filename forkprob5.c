/* $begin forkprob5 */
#include "csapp.h"

//
// Illustrates that the control flow of the parent is duplicated as well
//

void doit()
{
    if (Fork() == 0)
    {
        Fork();
        fprintf(stderr, "Process %d exits from doit()\n", getpid());
        exit(0);
    }
    fprintf(stderr, "Process %d does a return from doit()\n", getpid());

    return;
}

int main()
{
    doit();
    fprintf(stderr, "Process %d exits in main\n", getpid());
    exit(0);
}
/* $end forkprob5 */
