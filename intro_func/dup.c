#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("open failed");
        return 1;
    }

    int new_fd = dup(file);  // Duplicate the file descriptor
    if (new_fd == -1) {
        perror("dup failed");
        return 1;
    }

    write(new_fd, "Hello, file!\n", 13);  // Writes to output.txt
    write(file, "Hello again!\n", 13);  // Also writes to output.txt

    close(file);
    close(new_fd);
    return 0;
}

