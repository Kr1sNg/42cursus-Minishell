# Minishell

## I - Introduction

## II - Functions:

### 1 - **The `readline`**
- `readline`:

`readline()` reads a line from the terminal and return it, using `prompt` as prompt (`NULL` prompt is accepted). The line return has the final newline removed, so only the text remains.

```c
char	*readline(const char *prompt);
```

- `rl_clear_history`:

`rl_clear_history()` clear the history list by deleting all of the entries, in the same manner as the History library’s `clear_history()` function. This differs from `clear_history()` because it frees private data Readline saves in the history list.

```c
void	rl_clear_history(void);
```

- `rl_on_new_line`:

`rl_on_new_line()` tells the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

```c
int	rl_on_new_line(void);
```

- *variable `rl_line_buffer`*:

This is the line gathered.

```c
char *rl_line_buffer;
```

- `rl_replace_line`:

`rl_replace_line()` replaces the contents of `rl_line_buffer` with `text`. The point and mark are preserved, if possible. If `clear_undo` is non-zero, the undo list associated with the current line is cleared.

```c
void	rl_replace_line(const char *text, int clear_undo);
```

- `rl_redisplay`:

`rl_redisplay()` changes what’s displayed on the screen to reflect the current contents of `rl_line_buffer`.

```c
void	rl_redisplay(void);
```

- `add_history`:

`add_history()` saves the `line` passed as parameter at the end of the history list, so it can be retrieved later in the terminal (like pressing *the up arrow* in bash).

```c
void	add_history (const char *line);
```



### 2 - files

- `access`:

`access()` checks whether the calling process can access the file `pathname`.

```c
int	access(const char *pathname, int mode);
```

The `mode` specifies the accessibility checks to be performed, and is either the value `F_OK` (test for the *existence* of the file), or a mask consisting of the bitwise `OR (|)` of one or more of `R_OK`, `W_OK` and `X_OK` (which test whether file exists and grants *read*, *write* and *execute* permissions).

- `write`, `open`, `read`, `close`

### 3 - Processes

- `fork`:

`fork()` creates a new process (child) by duplicating the calling process (parent).

```c
pid_t	fork(void);
```

On success, the PID of the child process is returned in the parent, and `0` is returned in the child. On failure, `-1` is returned in the parent, no child process is created.

- The `wait`:

	- `wait()`, `waitpid()` wait for process to change state. `wait()` suspends execution of the calling thread until oe of its children terminates. `waitpid()` suspends execution of the calling thread until in a child specified by `pid` has changed states, which are: *the child terminated*, *the child was stopped by a signal*, *the child was resumed by a signal*. 
	```c
	pid_t	wait(int *wstatus);
	pid_t	waitpid(pid_t pid, int *wstatus, int options);
	```

	- `wait3()`, `wait4()` are similar to `waitpid()` but additionally return resource usage information about the child in the structure pointed to by `rusage`. While `wait3()` waits of any child, `wait4()` waits a specified child or children.
	```c
	pid_t	wait3(int *wstatus, int options, struct rusage *rusage);
	pid_t	wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
	```

- The `signal`:

	- `signal()` specifies how a signal should be handled when a particualr signal is received. It sets the disposition of the signal `signum` to the function `handler`.
	
	```c
	#include <signal.h>
	typedef void (*sighandler_t)(int);
	sighandler_t signal(int signum, sighandler_t handler);
	```

	The `signal()` function returns a pointer to the previous signal handler function for the specified signal.


	- `signaction()` allows the calling process to change its action for the signal `signum` to the action described by `act`. `act` is assigned in struct `sigaction` as a handler function. A NULL `act` argument can be used to query the current action without changing it. `oldact` can set as `NULL`.

	```c
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	```

	Example:
	```c
	struct sigaction    sa;

    sa.sa_sigaction = handler_server;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    ft_printf("Bonus Server's PID is: %i\n", getpid());
    sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	```

	- `sigemptyset()`: The primary use of `sigemptyset()` to create an empty set of signals, which can then be manipulated using other signal-related functions. `set` is a pointer to a set of signal which has the type `sigset_t`.

	```c
    int sigemptyset(sigset_t *set);
	```


	- `sigaddset()`: add a specified signal `signum` to a specified signal `set`. It can be useful when we want to customize how the program responds to different signals.

	```c
	int	sigaddset(sigset_t *set, int signum);
	```

	- `kill()`: is used to send a signal to a process or a group of processes specified by the process ID `pid`. `sig` is the signal that we want to send.
	
	```c
    int kill(pid_t pid, int sig);
    ```

- `exit`:

`exit()` is used to terminate the calling process. It takes only one parameter `status` which is the exit code. `0` or `EXIT_SUCCESS` and `1` or `EXIT_FAILURE`.

```
void	exit(int status);
```

### 4 - Directory:

- `getcwd`: (for `pwd`)

```c
char	*getcwd(char *buf, size_t size);
```

The `getcwd` returns a null-terminated string containning the absolute pathname that is the current working directory of the calling process. It copies the pathname to the array pointed to by `buf`, which is of length `size`.

Example:
```c
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    printf("pwd: %s\n", pwd);
    return (0);
}
```
```bash
$ pwd: /home/tat-nguy/42perso/42curcus
```

- `chdir`: (for `cd`)

```c
int	chdir(const char *path);
```

The `chdir()` changes the current working directory of the calling process to the directory specified in `path`.

Example:
```c
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    printf("pwd before chdir: %s\n", pwd);
    chdir("/home/tat-nguy/42rendu");
    pwd = getcwd(NULL, 0);
    printf("pwd after chdir: %s\n", pwd);
    return (0);
}
```
```shell
$ pwd before chdir: /home/tat-nguy/42perso/42curcus/42cursus-Minishell/tathoang
$ pwd after chdir: /home/tat-nguy/42rendu
```




## III - Psuedocode:

## IV - Testing:
