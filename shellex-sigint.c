/* $begin shellmain */
#include "csapp.h"
#define MAXARGS 128

//
// Sample shell program from the text.
//
// Thie example has a basic fork / exec / wait loop to evaluate individual commands.
// It can also "background" jobs meaning it does not wait for them. Those processes
// will be "zombie" proceses because no wait() is ever performed
//

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);


/*
 * The PID of the fg process -- needed in SIGINT handler
 */

static pid_t global_pid = 0;

void sigint_handler(int sig)
{
  fprintf(stderr, "Caught SIGINT in %s!\n", __FILE__);

  if (global_pid <= 0) {
    fprintf(stderr, "...but no child to kill...\n");
  } else {
    fprintf(stderr, "...send SIGINT to %d\n", global_pid);
    kill(global_pid, SIGINT);
  }
}

void sigchld_handler(int sig)
{
  fprintf(stderr,"Caught SIGCHLD\n");
}

int main()
{
    char cmdline[MAXLINE]; /* Command line */

    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");
    if (signal(SIGCHLD, sigchld_handler) == SIG_ERR)
        unix_error("signal error");

    while (1)
    {
        /* Read */
        printf("> ");
        Fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        /* Evaluate */
        eval(cmdline);
    }
}

/* eval - Evaluate a command line */
void eval(char *cmdline)
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
        return; /* Ignore empty lines */

    if (!builtin_command(argv))
    {
        if ((global_pid = Fork()) == 0)
        { /* Child runs user job */
            if (execve(argv[0], argv, environ) < 0)
            {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        /* Parent waits for foreground job to terminate */
        if (!bg)
        {
            int status;
	    fprintf(stderr,"Start waiting for child %d\n", global_pid);
            if (waitpid(global_pid, &status, 0) < 0)
                unix_error("waitfg: waitpid error");
	    fprintf(stderr,"Done waiting for child %d\n", global_pid);
	    global_pid = 0;
        }
        else {
	  printf("%d %s", global_pid, cmdline);
	  global_pid = 0;
	}
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit")) /* quit command */
        exit(0);
    if (!strcmp(argv[0], "&")) /* Ignore singleton & */
        return 1;
    return 0; /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
    char *delim; /* Points to first space delimiter */
    int argc;    /* Number of args */
    int bg;      /* Background job? */

    buf[strlen(buf) - 1] = ' ';   /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0) /* Ignore blank line */
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc - 1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}
/* $end parseline */
