#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int x = 100;
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "error calling fork");
        exit(1);
    } else if (rc == 0) {
        printf("x=%d, PID=%d\n", x, getpid());
        x++;
        printf("x=%d, PID=%d\n", x, getpid());
    } else {
        wait(NULL);
        printf("x=%d, PID=%d\n", x, getpid());
        x++;
        printf("x=%d, PID=%d\n", x, getpid());
        
    }
    return 0;
}