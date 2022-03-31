#include "csapp.h"

int main(int argc, char *argv[])
{
  if ( argc < 2 ) {
    fprintf(stderr,"usage: %s <filename> <program> [options]\n", argv[0]);
    fprintf(stderr,"A process is created that used 'cat' to pipe the file contents\n");
    fprintf(stderr,"to the specified program. For example:\n");
    fprintf(stderr,"\t%s /etc/passwd /bin/wc -l\n", argv[0]);
    fprintf(stderr,"will count the lines in the file /etc/motd\n");
    
  }
  char *filename = argv[1];
  //
  // Create a pipe that we will use in the two children
  //
  int filedes[2];
  int ret = pipe(filedes);
  if ( ret < 0 ) {
    perror("pipe"); exit(1);
  }

  const int INPUT_FD = 0;
  const int OUTPUT_FD = 1;

  int catpid = Fork();
  if ( catpid == 0 ) {
    // I am the child.
    // Using dup2 to make the input of the pipe be my stdout

    int retd = dup2(filedes[OUTPUT_FD], 1); // stdout is file descriptor #1
    close(filedes[INPUT_FD]);  // close our duplicates & other end of pipe
    close(filedes[OUTPUT_FD]);
    if ( retd < 0 ) {
      perror("dup2"); exit(2);
    }
    char *catargs[4];
    catargs[0] = "/bin/cat";
    catargs[1] = filename;
    catargs[2] = NULL;
    int retr = execve("/bin/cat", catargs, environ);
    perror("execve"); exit(4);
  }

  int output = Fork();
  if (output == 0 ) {
    // I am the child.
    // Using dup2 to make the input of the pipe be my stdin

    int retd = dup2(filedes[INPUT_FD], 0); // stdin is file descriptor #0
    close(filedes[INPUT_FD]);  // close our duplicates & other end of pipe
    close(filedes[OUTPUT_FD]);
    if ( retd < 0 ) {
      perror("dup2"); exit(2);
    }
    int retr = execve(argv[2], &argv[2], environ);
    perror("execve"); exit(3);
  }

  close(filedes[INPUT_FD]);  // close our duplicates & other end of pipe
  close(filedes[OUTPUT_FD]);

  int status;
  waitpid(output, &status, 0);
  fprintf(stderr,"done\n");
}
