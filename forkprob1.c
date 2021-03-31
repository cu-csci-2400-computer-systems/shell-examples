/* $begin forkprob1 */
#include "csapp.h"

//
// Question on how many processes
//
// Both child and parent continue execution in the loop
//

int main()
{
    int i;

    for (i = 0; i < 2; i++)
        Fork();
    printf("hello from %d\n", getpid());
    exit(0);
}
/* $end forkprob1 */
