/* using to simulate ls | wc - l */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> //for wait()
#include <sys/wait.h> // for wait()

int main(int argc, char *argv[], char *envp[])
{
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    if (fork() == 0) {
        // First Child: Executes "/bin/ls"
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[0]);  // Close unused read end
        close(pipefd[1]);  // Close duplicate write end

        char *cmd = "/bin/ls";  // Full path required
        char *args[] = {"ls", NULL};

        execve(cmd, args, envp);
        perror("execve ls failed");
        exit(1);
    }

    if (fork() == 0) {
        // Second Child: Executes "/usr/bin/wc -l"
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe
        close(pipefd[1]);  // Close unused write end
        close(pipefd[0]);  // Close duplicate read end

        char *cmd = "/usr/bin/wc";  // Full path required
        char *args[] = {"wc", "-l", NULL};

        execve(cmd, args, envp);
        perror("execve wc failed");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);
    return 0;
}
