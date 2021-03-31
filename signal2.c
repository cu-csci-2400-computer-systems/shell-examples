#include "csapp.h"

/* $begin signal2 */
void handler2(int sig)
{
    int olderrno = errno;
    fprintf(stderr,"Enter SIGCHL handler\n");
    for (;;)
    {
        pid_t pid = waitpid(-1, NULL, 0);

        if (pid < 0)
        {
            if (errno != ECANCELED)
            {
                fprintf(stderr, "Done reaping children\n");
            }
            else
            {
                fprintf(stderr, "waitpid returned error %d\n", pid);
            }

            break;
        }

        fprintf(stderr, "Handler reaped child %d\n", pid);
    }
    Sleep(1);
    errno = olderrno;
}
/* $end signal2 */

int main()
{
    int i, n;
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler2) == SIG_ERR)
        unix_error("signal error");

    /* Parent creates children */
    for (i = 0; i < 3; i++)
    {
        if (Fork() == 0)
        {
            printf("Hello from child %d\n", (int)getpid());
            exit(0);
        }
    }

    /* Parent waits for terminal input and then processes it */
    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
        unix_error("read");

    printf("Parent processing input\n");
    while (1)
        ;

    exit(0);
}
