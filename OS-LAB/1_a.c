#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[100];

    // ===== 1. Create pipe for parent-child communication =====
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid_t pid = fork(); // Create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        // ===== Parent Process =====
        close(pipefd[0]); // Close read end
        char msg[] = "Hello from Parent!";
        write(pipefd[1], msg, strlen(msg)+1);
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
        printf("Parent sent message: %s\n", msg);

        // ===== Zombie Process Demonstration =====
        pid_t zombie_pid = fork();
        if (zombie_pid == 0) {
            printf("Zombie Child PID: %d (will terminate immediately)\n", getpid());
            exit(0); // Child terminates
        }
        sleep(3); // Parent sleeps so child becomes zombie
        printf("Parent checking zombie: wait() to clean up\n");
        waitpid(zombie_pid, NULL, 0); // Reap zombie

        close(pipefd[1]); // Close write end
        wait(NULL); // Wait for main child to finish

        // ===== Orphan Process Demonstration =====
        pid_t orphan_pid = fork();
        if (orphan_pid == 0) {
            sleep(2); // Wait for parent to terminate
            printf("Orphan Child PID: %d, New Parent PID: %d\n", getpid(), getppid());
            exit(0);
        }
        printf("Parent PID: %d will terminate, leaving orphan child\n", getpid());
        exit(0); // Parent terminates, orphan child remains
    } else {
        // ===== Child Process =====
        close(pipefd[1]); // Close write end
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child received message: %s\n", buffer);
        close(pipefd[0]);

        // ===== Daemon Process Demonstration =====
        pid_t daemon_pid = fork();
        if (daemon_pid > 0) exit(0); // Parent exits
        if (daemon_pid == 0) {
            setsid(); // Start new session for daemon
            printf("Daemon PID: %d, PPID: %d (detached from terminal)\n", getpid(), getppid());
            sleep(5); // Daemon continues running
            printf("Daemon finished work.\n");
        }
    }

    return 0;
}
