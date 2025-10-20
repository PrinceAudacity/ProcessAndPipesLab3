#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <search-term>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipe1[2]; // cat → grep
    int pipe2[2]; // grep → sort

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child: grep
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            // Grandchild: sort
            dup2(pipe2[0], STDIN_FILENO);
            close(pipe2[1]);
            close(pipe1[0]);
            close(pipe1[1]);
            execlp("sort", "sort", NULL);
            perror("execlp sort failed");
            exit(EXIT_FAILURE);
        } else {
            // grep
            dup2(pipe1[0], STDIN_FILENO);
            dup2(pipe2[1], STDOUT_FILENO);
            close(pipe1[1]);
            close(pipe2[0]);
            execlp("grep", "grep", argv[1], NULL);
            perror("execlp grep failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent: cat
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("cat", "cat", "scores", NULL);
        perror("execlp cat failed");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    wait(NULL);
    return 0;
}
