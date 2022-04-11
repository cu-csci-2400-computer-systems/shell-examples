/* $begin sigint */
#include "csapp.h"

void sigint_handler(int sig)
{
  fprintf(stderr, "Caught SIGINT in %s!\n", __FILE__);
    exit(0);
}

int main()
{
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");

    for (;;)
    {
        fprintf(stderr, "Waiting for something to happen\n");
        pause(); /* Wait for the receipt of a signal */
    }

    return 0;
}
