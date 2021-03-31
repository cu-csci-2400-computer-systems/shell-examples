/* $begin forkprob2 */
#include "csapp.h"

//
// The C library actually as a way to run "hooks" when you call exit
// because it's often useful to "clean up" some resource when your process exits.
//
// However, these are only called if exit() is called. If your process dies
// they aren't called.
//

void end(void)
{
    fprintf(stderr,"Process %d exits from end()\n", getpid());
}

int main()
{
    int pid = fork();

    if (pid == 0) {
        fprintf(stderr,"Child %d sets atexit routine\n", getpid());
        atexit(end);
    }

    if (Fork() == 0)
    {
        fprintf(stderr,"Process in if-then %d executes\n", getpid());
    }
    else
    {
        fprintf(stderr,"Process %d executes else\n", getpid());
    }
    exit(0);
}
/* $end forkprob2 */
