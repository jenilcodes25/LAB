#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

// Function executed by each thread
void* task(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d is running...\n", thread_id);
    for (int i = 0; i < 3; i++) {
        printf("Thread %d working: step %d\n", thread_id, i + 1);
        sleep(1);
    }
    printf("Thread %d finished execution.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[3];                // Thread identifiers
    pthread_attr_t attr;             // Attribute object
    struct sched_param param;        // For priority

    pthread_attr_init(&attr);        // Initialize thread attributes
    pthread_attr_setschedpolicy(&attr, SCHED_RR); // Round Robin scheduling

    int priority[] = {30, 20, 10};   // Different priorities
    int thread_ids[] = {1, 2, 3};

    // Create threads with different priorities
    for (int i = 0; i < 3; i++) {
        param.sched_priority = priority[i];
        pthread_attr_setschedparam(&attr, &param);
        pthread_create(&tid[i], &attr, task, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("\nAll threads have completed execution.\n");
    return 0;
}
