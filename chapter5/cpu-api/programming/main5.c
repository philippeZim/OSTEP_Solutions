/*
If you call wait() in the child process, 
it will return -1 because the child has no children of its own to wait for. 
The error code will be set to ECHILD, 
indicating that there are no child processes to wait for.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        sleep(2); // Simulate some work in the child process
        printf("Child process: Done.\n");
        exit(0); // Exit successfully
    } else {
        // Parent process
        printf("Parent process: Waiting for child to finish...\n");
        pid_t waited_pid = wait(&status);  // Parent waits for child to finish

        if (waited_pid > 0) {
            if (WIFEXITED(status)) {
                printf("Parent process: Child %d finished with status %d.\n", waited_pid, WEXITSTATUS(status));
            } else {
                printf("Parent process: Child did not exit successfully.\n");
            }
        } else {
            perror("wait failed");
        }
    }

    return 0;
}
