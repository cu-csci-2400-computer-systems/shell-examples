#include "csapp.h"
/* $begin signal1 */
/* WARNING: This code is buggy! */

void handler1(int sig)
{
    int olderrno = errno;

    int pid = waitpid(-1, NULL, 0);
    if (pid < 0)
        sio_error("waitpid error");
    fprintf(stderr, "Handler reaped child %d\n", pid);
    errno = olderrno;
}

int main()
{
    int i, n;
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler1) == SIG_ERR)
        unix_error("signal error");

    /* Parent creates children */
    for (i = 0; i < 3; i++)
    {
        if (Fork() == 0)
        {
            fprintf(stderr, "Starting child %d\n", (int)getpid());
            exit(0);
        }
    }



    /* Parent waits for terminal input and then processes it */
    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
        unix_error("read");

    printf("Parent processing input\n");
    for (;;)
    {
        // infinite loop
    }

    exit(0);
}
/* $end signal1 */
