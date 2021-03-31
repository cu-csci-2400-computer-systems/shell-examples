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
        printf("hello\n");
        exit(0);
    }
    return;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}
/* $end forkprob5 */
