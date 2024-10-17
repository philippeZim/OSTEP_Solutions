#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fl = open("out.txt", O_WRONLY | O_CREAT);

    int rc = fork();

    if (rc < 0) {
        perror("error doing fork");
        return 1;
    } else if (rc == 0) {
        char *data1 = "Child process text";
        write(fl, data1, sizeof(char) * 18);

    } else {
        char *data1 = "Parent process text";
        write(fl, data1, sizeof(char) * 19);

        wait(NULL);
        close(fl);
    }

    return 0;
}