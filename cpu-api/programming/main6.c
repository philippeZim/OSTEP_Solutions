/*
Differences between wait() and waitpid():
wait(): Waits for any child process to terminate. It’s useful when you don’t care which child finishes first, and you just want to know when any child process exits.
waitpid(): More flexible and allows the parent to wait for a specific child process to terminate, as identified by its PID.
With waitpid(), you can also specify options like WNOHANG to avoid blocking, making it useful in more complex scenarios (e.g., handling multiple child processes or performing non-blocking checks).
*/