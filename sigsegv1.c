#include "csapp.h"
#include <string.h>

//
// Demonstrates catching a SIGSEV from a null pointer dereference.
//
// When the signal handler returns, the memory access is "replayed"
// and since we didn't take any steps to fix the problem, we'll get
// another SIGSEGV
//

void handler1(int sig)
{
    fprintf(stderr, "Ow! I got signal \"%s\"(#%d)\n",
            strsignal(sig), sig);
    // exit(0);
}

int main()
{
    int i, n;
    char buf[MAXBUF];
    char *ptr;

    if (signal(SIGSEGV, handler1) == SIG_ERR)
        unix_error("signal error");

    fprintf(stderr, "About to poke main..\n");
    ptr = (char *)0;
    *ptr = '\n';
}
/* $end signal1 */
