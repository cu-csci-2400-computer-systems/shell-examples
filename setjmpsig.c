#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <setjmp.h>
#include <time.h>

static void                         sig_int(int), sig_alrm(int);
static sigjmp_buf                   jmpbuf;
static volatile sig_atomic_t        canjump;

int
main(void)
{
  if (signal(SIGINT, sig_int) == SIG_ERR) {
    perror("signal(SIGUSR1) error");
  }

  fprintf(stderr, "starting main:\n");

  if (sigsetjmp(jmpbuf, 1)) {
    fprintf(stderr, "ending main:\n");
    exit(0);
  }

  for ( ; ; )
    pause();
}
static void
sig_int(int signo)
{
  time_t  starttime;

  fprintf(stderr, "starting sig_int:\n");
  fprintf(stderr, "finishing sig_int:\n");

  siglongjmp(jmpbuf, 1);  /* jump back to main, don't return */
}
