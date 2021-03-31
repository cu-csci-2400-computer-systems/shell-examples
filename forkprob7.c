/* $begin forkprob7 */
#include "csapp.h"

//
// Demonstrate the use of wait() to wait for a child.
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
    int pid = fork();
       int delay = getRandU8() % 5;

    sleep ( delay );

    if (pid == 0) 
    {
        // child
        fprintf(stderr,"Child with pid %d exits\n", getpid());
        exit(0);
    }
    else
    {
        // parent
        fprintf(stderr,"Parent with pid %d waits for child\n", getpid());
        Wait(NULL);
        fprintf(stderr,"Parent with pid %d continues execution\n", getpid());
    }
    exit(0);
}
/* $end forkprob7 */
