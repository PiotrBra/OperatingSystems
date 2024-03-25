#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dir path>\n", argv[0]);
        return 1;
    }

    int local = 0;
    printf("Program Name: %s\n", argv[0]);

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "There's an error with creating child's process \n");
        return 1;
    } else if (pid == 0) {

        printf("child's process\n");
        printf("child's pid = %d, parent's pid = %d\n", getpid(), getppid());

        global++;
        local++;
        printf("child's local = %d, child's global = %d\n", local, global);

        execl("/bin/ls", "ls", argv[1], NULL);
        perror("Błąd wykonania programu ls");
        exit(1);
    } else {

        printf("parent's process\n");
        printf("parent's pid = %d, child's pid = %d\n", getpid(), pid);

        int status;
        wait(&status);
        printf("Child exit code: %d\n", WEXITSTATUS(status));

        printf("Parent's local = %d, parent's global = %d\n", local, global);

        return 0;
    }
}
