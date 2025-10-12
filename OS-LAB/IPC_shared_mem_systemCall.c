#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 1024  // Size of shared memory

int main() {
    key_t key = 1234;  // Shared memory key
    int shmid;
    char *str;

    // ===== Create shared memory segment =====
    shmid = shmget(key, SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        // ===== Parent Process (Sender) =====
        str = (char*) shmat(shmid, NULL, 0);  // Attach
        if (str == (char*) -1) {
            perror("shmat failed");
            exit(1);
        }

        char message[] = "Hello Child! Message via Shared Memory.";
        strcpy(str, message); // Write to shared memory
        printf("Parent PID: %d wrote message: %s\n", getpid(), message);

        wait(NULL); // Wait for child to finish
        shmdt(str); // Detach
        shmctl(shmid, IPC_RMID, NULL); // Remove shared memory
    } else {
        // ===== Child Process (Receiver) =====
        sleep(1); // Ensure parent writes first
        str = (char*) shmat(shmid, NULL, 0);  // Attach
        if (str == (char*) -1) {
            perror("shmat failed");
            exit(1);
        }

        printf("Child PID: %d read message: %s\n", getpid(), str);
        shmdt(str); // Detach
        exit(0);
    }

    return 0;
}
