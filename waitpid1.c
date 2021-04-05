/* $begin waitpid1 */
#include "csapp.h"
#define N 2

//
// Run N processes and each will return a value using exit status
//
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
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)
    {
        if ((pid = Fork()) == 0)
        {
            sleep(getRandU8() % 4);
            /* Child */
            exit(100 + i);
        }
    }

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status))
        {
            printf("child %d terminated normally with exit status=%d\n",
                   pid, WEXITSTATUS(status));
        }
        else
        {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
    {
        unix_error("waitpid error");
    }

    exit(0);
}