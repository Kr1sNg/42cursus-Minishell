# Bash Reference Manual

## 1 Introduction

### 1.1 What is Bash?

Bash is the shell, or command language interpreter, for the GNU operating system. The name is an acronym for the ‘Bourne-Again SHell’, a pun on Stephen Bourne, the author of the direct ancestor of the current Unix shell sh, which appeared in the Seventh Edition Bell Labs Research version of Unix.

Bash is largely compatible with sh and incorporates useful features from the Korn shell ksh and the C shell csh. It is intended to be a conformant implementation of the IEEE POSIX Shell and Tools portion of the IEEE POSIX specification (IEEE Standard 1003.1). It offers functional improvements over sh for both interactive and programming use.

While the GNU operating system provides other shells, including a version of csh, Bash is the default shell. Like other GNU software, Bash is quite portable. It currently runs on nearly every version of Unix and a few other operating systems - independently-supported ports exist for MS-DOS, OS/2, and Windows platforms.

### 1.2 What is a shell?

At its base, a shell is simply a macro processor that executes commands. The term macro processor means functionality where text and symbols are expanded to create larger expressions.

A Unix shell is both a command interpreter and a programming language. As a command interpreter, the shell provides the user interface to the rich set of GNU utilities. The programming language features allow these utilities to be combined. Files containing commands can be created, and become commands themselves. These new commands have the same status as system commands in directories such as /bin, allowing users or groups to establish custom environments to automate their common tasks.

Shells may be used interactively or non-interactively. In interactive mode, they accept input typed from the keyboard. When executing non-interactively, shells execute commands read from a file.

A shell allows execution of GNU commands, both synchronously and asynchronously. The shell waits for synchronous commands to complete before accepting more input; asynchronous commands continue to execute in parallel with the shell while it reads and executes additional commands. The redirection constructs permit fine-grained control of the input and output of those commands. Moreover, the shell allows control over the contents of commands’ environments.

Shells also provide a small set of built-in commands (builtins) implementing functionality impossible or inconvenient to obtain via separate utilities. For example, cd, break, continue, and exec cannot be implemented outside of the shell because they directly manipulate the shell itself. The history, getopts, kill, or pwd builtins, among others, could be implemented in separate utilities, but they are more convenient to use as builtin commands. All of the shell builtins are described in subsequent sections.

While executing commands is essential, most of the power (and complexity) of shells is due to their embedded programming languages. Like any high-level language, the shell provides variables, flow control constructs, quoting, and functions.

Shells offer features geared specifically for interactive use rather than to augment the programming language. These interactive features include job control, command line editing, command history and aliases. Each of these features is described in this manual.


## 2 Definitions

These definitions are used throughout the remainder of this manual.

POSIX

    A family of open system standards based on Unix. Bash is primarily concerned with the Shell and Utilities portion of the POSIX 1003.1 standard.
blank

    A space or tab character.
builtin

    A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system.
control operator

    A token that performs a control function. It is a newline or one of the following: ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.
exit status

    The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255.
field

    A unit of text that is the result of one of the shell expansions. After expansion, when executing a command, the resulting fields are used as the command name and arguments.
filename

    A string of characters used to identify a file.
job

    A set of processes comprising a pipeline, and any processes descended from it, that are all in the same process group.
job control

    A mechanism by which users can selectively stop (suspend) and restart (resume) execution of processes.
metacharacter

    A character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
name

    A word consisting solely of letters, numbers, and underscores, and beginning with a letter or underscore. Names are used as shell variable and function names. Also referred to as an identifier.
operator

    A control operator or a redirection operator. See Redirections, for a list of redirection operators. Operators contain at least one unquoted metacharacter.
process group

    A collection of related processes each having the same process group ID.
process group ID

    A unique identifier that represents a process group during its lifetime.
reserved word

    A word that has a special meaning to the shell. Most reserved words introduce shell flow control constructs, such as for and while.
return status

    A synonym for exit status.
signal

    A mechanism by which a process may be notified by the kernel of an event occurring in the system.
special builtin

    A shell builtin command that has been classified as special by the POSIX standard.
token

    A sequence of characters considered a single unit by the shell. It is either a word or an operator.
word

    A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters. 


## 3 Basic Shell Features

### 3.1 Shell Syntax

When the shell reads input, it proceeds through a sequence of operations. If the input indicates the beginning of a comment, the shell ignores the comment symbol (‘#’), and the rest of that line.

Otherwise, roughly speaking, the shell reads its input and divides the input into words and operators, employing the quoting rules to select which meanings to assign various words and characters.

The shell then parses these tokens into commands and other constructs, removes the special meaning of certain words or characters, expands others, redirects input and output as needed, executes the specified command, waits for the command’s exit status, and makes that exit status available for further inspection or processing. 

#### 3.1.1 Shell Operation

The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

- Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
- Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
- Parses the tokens into simple and compound commands (see Shell Commands).
- Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
- Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
- Executes the command (see Executing Commands).
- Optionally waits for the command to complete and collects its exit status (see Exit Status).

#### 3.1.2 Quoting

Quoting is used to remove the special meaning of certain characters or words to the shell. Quoting can be used to disable special treatment for special characters, to prevent reserved words from being recognized as such, and to prevent parameter expansion.

Each of the shell metacharacters (see Definitions) has special meaning to the shell and must be quoted if it is to represent itself. When the command history expansion facilities are being used (see History Expansion), the history expansion character, usually ‘!’, must be quoted to prevent history expansion. See Bash History Facilities, for more details concerning history expansion.

There are three quoting mechanisms: the escape character, single quotes, and double quotes. 

##### 3.1.2.1 Escape Character

A non-quoted backslash ‘\’ is the Bash escape character. It preserves the literal value of the next character that follows, with the exception of newline. If a \newline pair appears, and the backslash itself is not quoted, the \newline is treated as a line continuation (that is, it is removed from the input stream and effectively ignored).

Key Takeaway: Use \ to escape special characters or split commands across lines, ensuring it is the last character before a newline for line continuation.

##### 3.1.2.2 Single Quotes

Enclosing characters in single quotes (‘'’) preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.

##### 3.1.2.3 Double Quotes

Enclosing characters in double quotes (‘"’) preserves the literal value of all characters within the quotes, with the exception of ‘$’, ‘`’, ‘\’, and, when history expansion is enabled, ‘!’. When the shell is in POSIX mode (see Bash POSIX Mode), the ‘!’ has no special meaning within double quotes, even when history expansion is enabled. The characters ‘$’ and ‘\`’ retain their special meaning within double quotes (see Shell Expansions). The backslash retains its special meaning only when followed by one of the following characters: ‘$’, ‘\`’, ‘"’, ‘\’, or newline. Within double quotes, backslashes that are followed by one of these characters are removed. Backslashes preceding characters without a special meaning are left unmodified. A double quote may be quoted within double quotes by preceding it with a backslash. If enabled, history expansion will be performed unless an ‘!’ appearing in double quotes is escaped using a backslash. The backslash preceding the ‘!’ is not removed.

The special parameters ‘*’ and ‘@’ have special meaning when in double quotes (see Shell Parameter Expansion). 


#### 3.1.3 Comments

In a non-interactive shell, or an interactive shell in which the interactive_comments option to the shopt builtin is enabled (see The Shopt Builtin), a word beginning with ‘#’ causes that word and all remaining characters on that line to be ignored. An interactive shell without the interactive_comments option enabled does not allow comments. The interactive_comments option is on by default in interactive shells. See Interactive Shells, for a description of what makes a shell interactive. 

### 3.2 Shell Commands

#### 3.2.2 Simple Commands

A simple command is the kind of command encountered most often. It’s just a sequence of words separated by blanks, terminated by one of the shell’s control operators (see Definitions). The first word generally specifies a command to be executed, with the rest of the words being that command’s arguments.

The return status (see Exit Status) of a simple command is its exit status as provided by the POSIX 1003.1 waitpid function, or 128+n if the command was terminated by signal n. 

