/* $begin forkprob3 */
#include "csapp.h"

//
// Illustrates that the state of the parent (including global variables) is 
// duplicated on a fork, but that each child has separate copy of that state.
//

int main()
{
    int x = 3;

    if (Fork() != 0)
        printf("x=%d\n", ++x);

    printf("x=%d\n", --x);
    exit(0);
}
/* $end forkprob3 */
