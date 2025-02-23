# Minishell

This is a 42's project of simulation the Shell command-line terminal, taking `Bash` as a reference.

## I - Introduction

### 1 - Bash / Shell

- `Bash` (*Bourne-Again SHell*) is the shell, or command language interpreter, for the GNU operating system.
	- to check which shell we are on, use `echo $0`
	- to create child process, use `bash` or `zsh`

- a `shell` is simply a macro processor that executes commands.

- `POSIX`: A family of open system standards based on Unix. Bash is primarily concerned with the Shell and Utilities portion of the POSIX 1003.1 standard.

- `builtin`: A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system.

- `control operator`: A token that performs a control function. It is a newline or one of the following: `||`, `&&`, `|`, `(`, `)` or `&`, `;`, `;;`, `;&`, `;;&`, `|&` (not used in this project).

- `exit status` or `return status`: The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255.

- `filename`: A string of characters used to identify a file.

- `metacharacter`: A character that, when unquoted, separates words. A metacharacter is a `space`, `tab`, `newline`, or one of the following characters: `|`, `&`, `;`, `(`, `)`, `<`, or `>`.

- `signal`: A mechanism by which a process may be notified by the kernel of an event occurring in the system.

- `token`: A sequence of characters considered a single unit by the shell. It is either a word or an operator.

- `word`: A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters. 


### 2 - Understand the Project Requirements

The Minishell should:

- Display a **promt** when waiting for a new command.

- Have a working **history**.

- Search and launch the right executable (based on the **PATH** variable or using a relative or an absolute path).

- Not use more than **one global variable**.

- Not interpret unclosed quotes or special characters as `\` or `;`.

- Handle `'` (single quote) which should prevent the shell from interpreting the *metacharacters* in the quoted sequence.

```shell
>$ echo 'now we are in $PWD'
now we are in $PWD
>$ echo '"$USER"'
"$USER"
```

- Handle `"` (double quote) which should prevent the shell from interpreting the *metacharacters* in the quoted sequence except for `$`.

```shell
>$ echo "now we are in $PWD"
now we are in /home/user/minishell
>$ echo now we are in $PWD
now we are in /home/user/minishell
>$ echo "'$USER'"
'tat-nguy'
```

- Implement **redirections**:
	- `<` should redirect input. It redirects `stdin` to read input from a file.

	- `>` should redirect output. It redirects `stdout` to a file, overwrites the file if existing or creates a new file if not.
	```shell
	>$ echo Hello 42 > output.txt | cat output.txt
	Hello 42
	```
	
	- `>>` should redirect output in append mode.
	```shell
	>$ echo Hello 42 >> output.txt | cat output.txt
	abc
	Hello 42
	```

	- `<<` should be given a `delimiter`, read the input until a line containing the `delimiter` is seen. However, it doen't update the history!
	```shell
	>$ cat << EOF
	> this is a multi-line input
	> in the input
	> EOF
	this is a multi-line input
	in the input
	EOF
	```

- Implement **pipes** `|`. *The output of each command in the pipeline is connected to the input of the next command via a pipe.*

- Handle **environment variables** `$VARIABLE` which should expand to their values.
```shell
>$ echo $HOME
/home/user
>$ MY_VAR="Hello 42!" | echo $MY_VAR
Hello 42!
```

- Handle `$?` which should expand to the exit status (return value) of the previous command:
	- `0` → Success ✅
	- `1-255` → Error ❌
```shell
>$ ls nonexistent_folder
ls: cannot access 'nonexistent_folder': No such file or directory
>$ echo $?
2
>$ ls my_folder
file.txt
>$ echo $?
0
```

- Handle `Ctrl-C`, `Ctrl-D`, `Ctrl-\`:
	- `Ctrl-C` sends the `SIGINT` **Interrupt signal** to the process.
		- It terminates the running program immediately (but not the Shell).
		- In interactive mode, it display the prompt on a new line.
	- `Ctrl-D` sends the `EOF` **End of File signal** to the shell.
		- Inside a program waiting for input → Signals the end of input (useful for `cat`, `read`, `heredoc`).
		- At an empty prompt, in interactive mode → Closes the shell (logs out).
	- `Ctrl-\` send the `SIGQUIT` **Quit signal** to the process.
		- If a process is running, it terminates the process and print "^\Quit (core dumped)".
		- In intractive mode, it does nothing.
```shell
>$ sleep 42
>$ ^\Quit (core dumped)
```

- The Builtins:
	- `echo` with option `-n` (remove the \n at the end).
	- `cd` with only a relative or absolute path.
		- *absolute path* starts from the **root** `/` directory.
		- *relative path* relatives to the current directory `./` or noting to go into and `..` or `../` to go out of.
	- `pwd` with no options.
	- `export` with no options.
		- It's used to add environment variables that are inherited by child processes.
		- When run alone without arguments, it prints exported variables.
	```shell
	>$ export MY_VAR=42
	>$ bash
	>$ echo $MY_VAR
	>$ 42
	>$ exit
	>$ unset MY_VAR
	>$ echo $MY_VAR
	
	>$
	```

	- `unset` with no options. It removes variable from the shell environment. If that variable isn't exsist, it does nothing (no error).

	- `env` with no options or arguments. It displays the environment variables in current shell session. It shows only **exported variables**, it means that variables set without `export` are not shown.
	```shell
	>$ MY_VAR=42
	>$ env | grep MY_VAR
	>$ 
	>$ export MY_VAR
	>$ env | grep MY_VAR
	>$ MY_VAR=42
	>$ unset MY_VAR
	```

	- `exit` with no options. It closes the current shell session (or process) and returns an exit status (default is `0`)
	```shell
	>$ bash
	>$ exit
	>$ echo $?
	0
	``` 

- Bonus part:
	- `&&` *double ampersand*: the shell will interpret `&&` as a **logical AND**, meaning that the second command is executed only if the first one **succeeds** (return a `0` exit status)
	
	```bash
	>$ echo first && echo second
	>$ first
	>$ second
	>$ cd nodir && echo first
	>$ bash: cd: nodir: No such file or directory
	```

	- `||` *double vertical bar*: it represents a **logical OR**, meaning that the second command is executed only when the first command **fails** (return a non-zero exit status)
	
	```bash
	>$ echo first || echo second
	>$ first
	>$ cd nodir || echo first
	>$ bash: cd: nodir: No such file or directory
	>$ first
	```




---
## II - Functions

### 1 - **The `readline`**
- `readline`: need to `free()` after using

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


---
### 2 - File I/O

- `access`:

`access()` checks whether the calling process can access the file `pathname`.

```c
int	access(const char *pathname, int mode);
```

The `mode` specifies the accessibility checks to be performed, and is either the value `F_OK` (test for the *existence* of the file), or a mask consisting of the bitwise `OR (|)` of one or more of `R_OK`, `W_OK` and `X_OK` (which test whether file exists and grants *read*, *write* and *execute* permissions).

- `write`, `open`, `read`, `close`

- `stat`, `lstat`, `fstat`:

```c
#include <sys/stat.h>
int stat(const char *restrict pathname, struct stat *restrict statbuf);
int lstat(const char *restrict pathname, struct stat *restrict statbuf);
int fstat(int fd, struct stat *statbuf);
```

These functions return information about a file in the structure pointed by `statbuf`.


- `unlink`: (for `rm`)

```c
#include <unistd.h>
int	unlink(const char *filename);
```

The `unlink()` function deletes the file name `filename`. It returns `0` on success and `-1` on error.



- The `dup` & `dup2`: redirecting stardard output (for `>>`, `>`)

```c
int	dup(int	oldfd);
int	dup2(int oldfd, int newfd);
```

The `dup()` system call creates a copy of the file descriptor `oldfd`, using the lowest-numbered unused file descriptor for the new descriptor.
The `dup2()` system call performs the same task as `dup()`, but it uses the file descriptor number specified in `newfd`. If it was previously open (like STDOUT_FILENO), it will be silently closed before being reused.



---
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

- `execve`: (for execute ./Minishell)

```c
int	execve(const char *pathname, char *const argv[], char *const envp[]);
```

The `execve()` executes the new program referred to by `pathname` (by replacing the current process), while allowing us to specify new `argv[]` and new `envp[]`.

`argv[]` is an array of strings of command-line arguments (`argv[0]` should contain the filename executing). `envp[]` is an array of strings, where each entry is an environment variable in the format `KEY=VALUE`.

The argument vector and environment can be accessed by the new program's main function, as:

```c
int	main(int argc, char *argv[], char *envp[]);
```

Example:
```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
    int i = 0;

    // Loop through environment variables
    while (envp[i] != NULL)
    {
        if (strncmp(envp[i], "PATH=", 5) == 0) // Check if it's "PATH"
        {
            printf("PATH: %s\n", envp[i] + 5); // Print value without "PATH="
            break;
        }
        i++;
    }

    return 0;
}
```
```shell
PATH: /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
```

- `pipe`:

```c
int	pipe(int pipefd[2]);
```

The `pipe()` creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array `pipefd[2]` is used to return two file descriptors referring to the ends of the pipe:

`pipefd[0]`: refers to the read end of the pipe (data comes out here).
`pipefd[1]`: refers to the write end of the pipe (data goes in here). 


- `getenv`: get an environment variable (for `env`)

```c
char	*getenv(const char *name);
```

The `getenv()` function searches in the environment list to find the environment variable name, and returns a pointer to the corresponding value string.

> *in C, the environment refers to a collection of* **environment variables** *that store configuration settings for processes. These variables provide system-wid information, such as paths, user details, language settings...*. 

---
### 4 - Terminal

- `isatty`:

```c
int	isatty(int fd);
```

The `isatty()` tests whether `fd` is an open file descriptor referring to a terminal. It returns `1` if fd is an open file descriptor referring to a terminal, otherwise, `0` is returned with `errno`.


- `ttyname`:

```c
char **ttyname(int fd);
```

The `ttyname()` returns a pointer to the NULL-terminated pathname of the terminal device that is open on the file descriptor `fd`, or `NULL` on error.

- `ttyslot`:

```c
int	ttyslot(void);
```

The `ttyslot()` returns the index of the current user's entry in some file.


- `ioctl`:

```c
#include <sys/ioctl.h>
int	ioctl(int fd, unsigned long request, ...);
```

The `ioctl()` system call manipulates file descriptors, devices, and terminals at a lower level. `fd`: file descriptor (ex: terminal, device,...), `request`: the operation to perform (defined in `<sys/ioctl.h>`), `...`: additional arguments based on the request.


- `tcsetattr`, `tcgetattr`: set and get terminal attributes

```c
#include <termios.h>
#include <unistd.h>
int	tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
int	tcgetattr(int fd, struct termios *termios_p);
```

The `tcsetattr()` function shall set the parameters associated with the terminal referred to by the open file descriptor `fd` from the termios structure referenced by `termios_p` with the `optional_action` (`TCSANOW`, `TCSADRAIN` or `TCSAFLUSH`).

The `tcgetattr()` function shall get the parameters associated with with the terminal reffered to by `fd` and store them in the termios structure referenced by `termios_p`.

- The terminal capabilities: `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

```c
#include <termcap.h>
int	tgetent(char *bp, const char *name);
int	tgetflag(char *id);
int	tgetnum(char *id);
char	*tgetstr(char *id, char **area);
char	*tgoto(const char *cap, int col, int row);
int	tputs(const char *str, int affcnt, int (*putc)(int));
```

These functions are part of the `termcap` library, used for handling *terminal capabilities* (cursor movement, colors,...). Find capabilities with `id` in `**man** termcap`.

`tgetent()`: Initializes termcap and loads terminal capabilities.
`tgetflag()`: Checks if a terminal supports a boolean capability.
`tgetnum()`: Retrieves numeric capabilities (e.g., terminal size).
`tgetstr()`: Gets string capabilities (e.g., clear screen, cursor movement).
`tgoto()`: Formats a cursor movement command.
`tputs()`: Prints a termcap escape sequence safely.


---
### 5 - Directory

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

- `opendir`, `readdir`, `closedir`:

```c
#include <sys/types.h>
#include <dirent.h>
DIR	*opendir(const char *name);
struct dirent	*readdir(DIR *dirp);
int	closedir(DIR *dirp);
```

The `opendir()` function opens a directory stream corresponding to the directory `name`, and return a pointer to the directory stream. The stream is positioned at the first entry in the directory.

The `readdir()` function reads a directory, returns a pointer to a `dirent` structure representing the next directory entry in the directory stream pointed to by `dirp`. It returns `NULL` on reaching the end of the directory stream or if an error occured.

The `closedir()` fuction closes the directory stream associated with `dirp`. A successful call to `closedir()` also closes the underlying file descriptor associated with `dirp`. The directory stream descriptor `dirp` is not available after this call.

---
### 6 - The errors

- `strerror()`:

```c
#include <string.h>
char	*strerror(int errnum);
```

The strerror() function returns a pointer to a string that describes the error code passed in the argument `errnum`.


- `perror`:

```c
#include <stdio.h>
void	perror(const char *s);
```

The `perror()` function produces a message on standard error describing the last error encountered during a call to a system or library function.



## III - Planning

### 1 - Parsing & Input Handling `<tat-hoang>`

#### Input & Parsing Module:

- Tokenizer/Lexer: Converts the raw input into tokens (words, operators, etc.).
- Parser: Builds a data structure (like a command tree or a list of command structs) representing the commands, arguments, redirections, and pipelines.
	- Grammar Design: Divides the command line into components where each operator has a defined precedence.
	Grammar with [Extended Backus-Naur Form (EBNF)](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form)
	
	```go
	// [...] means None or once
	// {...} means Zero or more times

	<COMMAND_LINE>    	::= <EXPRESSION>
	<EXPRESSION>      	::= <LOGICAL_EXPR>
	<LOGICAL_EXPR>    	::= <PIPE_EXPR> { ("&&" | "||") <PIPE_EXPR> } 
	<PIPE_EXPR>       	::= <SIMPLE_EXPR> { "|" <SIMPLE_EXPR> }
	<SIMPLE_EXPR>     	::= <COMMAND> 
						| "(" <EXPRESSION> ")"
	<COMMAND>         	::= <CMD_WORDS> [ <REDIR_LIST> ]
	<CMD_WORDS>       	::= <WORD> { <WORD> }
						| <ASSIGNMENT_WORD> { <WORD> }
	<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }
	<REDIRECTION>     	::= ">"  <FILENAME>
						| "<"  <FILENAME>
						| ">>" <FILENAME>
						| "<<" <HERE_END>
	<ASSIGNMENT_WORD>	::= <WORD> "=" <WORD>
	<FILENAME>			::= <WORD>
	<HERE_END>			::= <WORD>

	```

	- Recursive Descent Parser: 
		- Write a function for each non-terminal.
		- Combine the parsed pieces into an AST (binary tree) where internal nodes represent operators and leaves represent simple commands.
		- Use recursion to naturally capture the structure dictated by operator precedence and associativity.


#### Signal Handling & Error Management Module:

- Setup appropriate signal handlers.
- Ensure proper error messaging and cleanup (avoid memory leaks, etc.).

### 2 - Execution & Build-in Commands `<theo>`

#### Execution Module:

- Command Executor: Determines whether a command is a built-in or an external command, then either executes it directly or uses fork/execve for external programs.
- Pipes & Redirections: Set up inter-process communication and handle file descriptor redirections.

#### Built-in Commands Module:

- Implement the logic for built-ins (e.g., handling directory changes for cd, managing environment variables for export/unset, etc.).


## IV - Testing




---
### References
- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
