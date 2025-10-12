#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

bool flag[2] = {false, false};
int turn = 0;  // indicates whose turn

void* process0(void* arg) {
    for (int i = 0; i < 3; i++) {
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1);  // waiting

        // Critical Section
        printf("Process 0 entering Critical Section (iteration %d)\n", i + 1);
        sleep(1);
        printf("Process 0 leaving Critical Section\n");

        flag[0] = false; // exit CS

        // Remainder Section
        sleep(1);
    }
    return NULL;
}

void* process1(void* arg) {
    for (int i = 0; i < 3; i++) {
        flag[1] = true;
        turn = 0;
        while (flag[0] && turn == 0);  // waiting

        // Critical Section
        printf("Process 1 entering Critical Section (iteration %d)\n", i + 1);
        sleep(1);
        printf("Process 1 leaving Critical Section\n");

        flag[1] = false; // exit CS

        // Remainder Section
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;
    pthread_create(&t0, NULL, process0, NULL);
    pthread_create(&t1, NULL, process1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("\nBoth processes have completed.\n");
    return 0;
}
