#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of precesses>\n", argv[0]);
        return 1;
    }

    int num_processes = atoi(argv[1]);
    if (num_processes <= 0) {
        fprintf(stderr, "Number of parameters has to be bigger than 0\n");
        return 1;
    }

    printf("Parent's process: PID = %d\n", getpid());

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "There's an error with creating child's process\n");
            return 1;
        } else if (pid == 0) {
            printf("Child's process: PID = %d, PID parent's = %d\n", getpid(), getppid());
            exit(0);
        }
    }
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    printf("Argument argv[1]: %s\n", argv[1]);

    return 0;
}
