#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Demonstrating execl()
    pid = fork();
    if (pid == 0) {
        // Child process
        printf("Using execl()\n");
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); // Parent waits for child
    }

    // Demonstrating execle()
    pid = fork();
    if (pid == 0) {
        // Child process
        printf("Using execle()\n");
        char *env[] = { "HOME=/usr/home", "LOGNAME=home", NULL };
        execle("/bin/ls", "ls", "-l", (char *)NULL, env);
        perror("execle failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); // Parent waits for child
    }

    // Demonstrating execlp()
    pid = fork();
    if (pid == 0) {
        // Child process
        printf("Using execlp()\n");
        execlp("ls", "ls", "-l", (char *)NULL); // No need for full path
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); // Parent waits for child
    }

    // Demonstrating execv()
    pid = fork();
    if (pid == 0) {
        // Child process
        printf("Using execv()\n");
        char *args[] = { "ls", "-l", NULL };
        execv("/bin/ls", args);
        perror("execv failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); // Parent waits for child
    }

    // Demonstrating execvp()
    pid = fork();
    if (pid == 0) {
        // Child process
        printf("Using execvp()\n");
        char *args[] = { "ls", "-l", NULL };
        execvp("ls", args); // No need for full path
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); // Parent waits for child
    }

    // Demonstrating execvpe()
    pid = fork();
    if (pid == 0) {
        // Child process
        printf("Using execvpe()\n");
        char *args[] = { "ls", "-l", NULL };
        char *env[] = { "HOME=/usr/home", "LOGNAME=home", NULL };
        execvpe("ls", args, env);
        perror("execvpe failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); // Parent waits for child
    }

    return 0;
}


/*
Explanation:
execl(): Takes the path to the executable and a variable-length list of arguments, followed by NULL.
execle(): Same as execl(), but also allows passing a custom environment for the executed program.
execlp(): Similar to execl(), but searches for the executable in the directories listed in the PATH environment variable.
execv(): Takes the path to the executable and an array of arguments (rather than a variable-length list).
execvp(): Similar to execv(), but searches for the executable in PATH.
execvpe(): Similar to execvp(), but also allows passing a custom environment.
*/