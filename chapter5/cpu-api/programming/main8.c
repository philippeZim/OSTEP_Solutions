#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 256

int main(void) {
    int pipefd[2];
    char buffer[BUFSIZE];

    if(pipe(pipefd) < 0) {
        perror("error doing pipe");
        return 1;
    }

    int rc = fork();

    if (rc < 0) {
        perror("error doing fork");
        return 1;
    } 
    if (rc == 0) {
        char *data1 = "message from child 1";
        close(pipefd[0]);
        write(pipefd[1], data1, strlen(data1) + 1);
        close(pipefd[1]);
        exit(0);
    }

    int rc2 = fork();

    if (rc2 < 0) {
        perror("error doing fork");
        return 1;
    }

    if (rc2 == 0) {
        close(pipefd[1]);
        read(pipefd[0], &buffer, BUFSIZE);
        close(pipefd[0]);
        printf("Child 2 recieved: %s\n", buffer);
        exit(0);
    }
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);
    return 0;
}