#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd = open("nonexistent.txt", O_RDONLY);
    if (fd == -1) {
        perror("perror output");  // Prints directly
        printf("strerror output: %s\n", strerror(errno));  // Uses formatted output
    }
    return 0;
}
