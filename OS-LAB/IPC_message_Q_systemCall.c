#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 100

// Message structure
struct message {
    long mtype;        // Message type
    char mtext[SIZE];  // Message text
};

int main() {
    key_t key = 5678; // Message queue key
    int msqid;

    // ===== Create message queue =====
    msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        // ===== Parent Process (Sender) =====
        struct message msg;
        msg.mtype = 1; // Message type 1
        strcpy(msg.mtext, "Hello Child! Message via Message Queue.");

        msgsnd(msqid, &msg, sizeof(msg.mtext), 0); // Send message
        printf("Parent PID: %d sent message: %s\n", getpid(), msg.mtext);

        wait(NULL); // Wait for child
        msgctl(msqid, IPC_RMID, NULL); // Remove queue
    } else {
        // ===== Child Process (Receiver) =====
        struct message msg;
        msgrcv(msqid, &msg, sizeof(msg.mtext), 1, 0); // Receive message type 1
        printf("Child PID: %d received message: %s\n", getpid(), msg.mtext);
        exit(0);
    }

    return 0;
}
