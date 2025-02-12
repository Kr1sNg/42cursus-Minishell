#include <stdio.h>
#include <string.h>

// int main(int argc, char *argv[], char *envp[])
// {
//     int i = 0;

//     // Loop through environment variables
//     while (envp[i] != NULL)
//     {
//         if (strncmp(envp[i], "PATH=", 5) == 0) // Check if it's "PATH"
//         {
//             printf("PATH: %s\n", envp[i] + 5); // Print value without "PATH="
//             break;
//         }
//         i++;
//     }

//     return 0;
// }


/* This program runs /bin/ls using execve(), passing a new argument list and using the same environment:
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    char *new_argv[] = {"/bin/ls", "-l", NULL}; // Command: ls -l
    char *new_envp[] = {NULL}; // Use the same environment

    printf("Executing /bin/ls -l ...\n");

    if (execve("/bin/ls", new_argv, envp) == -1)
    {
        perror("execve failed");
        return 1;
    }

    return 0; // This line will not be reached if execve succeeds.
}

/*
Explanation:
The program prints "Executing /bin/ls -l ...".
execve() is called, replacing the current process with /bin/ls -l.
If execve() succeeds, the current program is completely replaced with /bin/ls.
If execve() fails, it prints "execve failed" and returns an error.
*/