#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    struct winsize w;
    
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl failed");
        return 1;
    }

    printf("Terminal size: %d rows x %d columns\n", w.ws_row, w.ws_col);
    return 0;
}
