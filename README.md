# Exceptional Control Flow Examples

Examples for CSCI 2400. We're going to go over a subset of the code examples from the text in recitation to highlight specific features of aspects of the process and exceptioanl control flow system calls.

You should be able to build all the examples using `make` -- this will build a number of executable files corresponding to the various C files. For example, `forkprob0.c` will have an exectabel `forkprob0.exe`. The file `csapp.c` contains helper routines used by the other files and there will be no `csapp.exe` executable.

### Fork

* `forkprob0.exe` - Simple fork example showing Fork() and the fact that the child processes run independently, the output may be reordered and the parent doesn't wait. Run repeatedly to see this effect.
* `forkprob1.exe` - Runs fork in a loop - how many processes are created?
* `forkprob2.exe` - ignore this one for now
* `forkprob3.exe` - parent and child state are duplicated
* `forkprob7.exe` - Like `fork.exe`, child process modifies counter, parent waits for child to complete, global counter values are different for parent & child.

### Wait

* `waitprob0.exe` - parent explicitly waits for child, output is ordered by waiting
* `waitpid1.exe` - Child processes returns value to parent using `exit()`, parent waits for children in any order. Run repeatedly to see this effect.
* `waitpid2.exe` - Like `waitpid1.exe` but wait for processes in specific order due to waiting for specific PID. Repeated execution shows output remains the same.

### execve
* `shellex.exe` - this is a primitive shell demonstrates `exec()` and `wait()`. This is essentially the `tsh.c` shell that you are given for shell lab.

### kill - sending signals
* `kill.exe` - Parent killing child

### signal - catching signals
* `sigint.exe` - Example showing SIGINT being cause when you git Control-C. You can use Control-Z to suspend the program and then use `kill` to kill it.
* `signal1.exe` - Shows that signals are not queued. Repeated executions of this should result in case where not all children are reaped.
* `signal2.exe` - Fixes `signal1.exe` by waiting in a loop for all dead children

### sigprocmask
* `signalprob0.exe` - Uses `sigprocmask` to strong order execution output. Only one possible output ("213"). Occurs because of `waitpid()` for child and blocking /unblocking of signals
* `procmask1.exe` -- demonstrates race condition of addjob/deletejob
* `procmask2.exe` -- shows fix by blocking signals

## Using GDB to debug your shell lab with VScode

If you plan on using VScode to debug your shell lab, we need to do a little configuration. Normally, GDB "catches" the same sig\
nals your shell is supposed to catch. This stops execution and returns control to GDB when those signals occur. This means you \
can't just set a breakpoint in your signal handlers and expect to have the debugger notice that.

To get around this, we will use a [`.gdbinit`](.gdbinit) file which is contained in this Git repo. By default, `gdb` will not read a local `.gdbinit` file because of security concerns. We can override that by adding an option to the `.gdbinit` file in your home directory to enable loading any gdbinit file.

To do this, cut and paste the following line into a Terminal window

```
echo "set auto-load safe-path /" >> ~/.gdbinit
```

Following this, the local `.gdbinit` should be loaded. If you want to change the local `.gdbinit` you can learn more about the signal configurations [at this GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/Signals.html).
