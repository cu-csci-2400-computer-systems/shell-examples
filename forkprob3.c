/* $begin forkprob3 */
#include "csapp.h"
#include <stdlib.h>

//
// Illustrates that the state of the parent (including global variables) is
// duplicated on a fork, but that each child has separate copy of that state.
//
//

//
// To demonstrate a race condition, we need a source of truely random numbers.
// The rand() and random() calls use a pseudo-RNG from a seed shared by the
// parent and child
//
uint8_t getRandU8()
{
    uint8_t rnum = 0;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd != -1)
    {
        (void)read(fd, (void *)&rnum, sizeof(uint8_t));
        (void)close(fd);
    }
    return rnum;
}

int main()
{
    int x = 1;

    int pid = Fork();
    int delay = getRandU8() % 5;

    sleep(delay);

    if (pid == 0)
    {
        fprintf(stderr, "child: x=%d\n", ++x);
        exit(0);
    }

    fprintf(stderr, "parent: x=%d\n", --x);
    exit(0);
}
/* $end forkprob3 */
