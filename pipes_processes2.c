#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int pipe1[2];  // parent → child
    int pipe2[2];  // child → parent
    pid_t pid;
    char input[100], buffer[200];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        // ---------- Parent ----------
        close(pipe1[0]);
        close(pipe2[1]);

        printf("Input : ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        write(pipe1[1], input, strlen(input) + 1);

        read(pipe2[0], buffer, sizeof(buffer));
        strcat(buffer, "gobison.org");
        printf("Output : %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    } else {
        // ---------- Child ----------
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], buffer, sizeof(buffer));
        printf("Other string is: howard.edu\n");

        strcat(buffer, "howard.edu");
        printf("Output : %s\n", buffer);

        printf("Input : ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        strcat(buffer, input);

        write(pipe2[1], buffer, strlen(buffer) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}
