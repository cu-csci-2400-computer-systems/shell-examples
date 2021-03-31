/* $begin forkprob6 */
#include "csapp.h"

//
// The child processes also have the same return stack -- 
// so they can also return from functions called by the parent.
//

void doit()
{
    if (Fork() == 0)
    {
        Fork();
        printf("hello from %d in doit\n", getpid());
        return;
    }
    return;
}

int main()
{
    doit();
    printf("hello from %d in main\n", getpid());
    exit(0);
}
/* $end forkprob6 */
