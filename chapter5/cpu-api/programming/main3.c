#include <unistd.h>
#include <stdio.h>

int main(void) {
    int pipefd[2];
    char buf;
    
    if (pipe(pipefd) < 0) {
        perror("error using pipe");
        return 1;
    }

    int rc = fork();

    if (rc < 0) {
        perror("error using fork");
        return 1;
    } else if (rc == 0) {
        close(pipefd[0]);
        printf("Hello ");
        write(pipefd[1], "x", 1);
        close(pipefd[1]);
    } else {
        close(pipefd[1]);
        read(pipefd[0], &buf, 1);
        printf("World\n");
        close(pipefd[0]);
    }
    return 0;
}