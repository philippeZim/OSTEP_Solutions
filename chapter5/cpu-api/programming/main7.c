#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // In the child process
        printf("This will be printed before closing stdout.\n");

        // Close STDOUT
        close(STDOUT_FILENO);

        // Try to print after closing stdout
        printf("This will not be printed after closing stdout.\n");

        // Exit child process
        exit(0);
    } else {
        // In the parent process
        wait(NULL);  // Wait for the child to finish
        printf("Child process finished.\n");
    }

    return 0;
}


/*
The first printf() call will successfully print its message.
After close(STDOUT_FILENO) is called, the file descriptor for standard output is closed. 
Therefore, when the second printf() is executed, there is no valid output stream associated with it, 
and the output will not appear anywhere (i.e., it will be discarded).
No error message will be shown for the failed printf() after the file descriptor is closed 
because printf() internally buffers the output, but without a valid file descriptor, the output simply goes nowhere.
*/