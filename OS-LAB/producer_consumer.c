#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores and mutex
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < MAX_ITEMS; i++) {
        int item = i + 1;
        sem_wait(&empty);             // Wait if buffer is full
        pthread_mutex_lock(&mutex);   // Enter critical section

        buffer[in] = item;
        printf("Producer %d produced item %d at position %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);              // Signal full slot

        sleep(1); // simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(&full);              // Wait if buffer is empty
        pthread_mutex_lock(&mutex);   // Enter critical section

        int item = buffer[out];
        printf("Consumer %d consumed item %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);             // Signal empty slot

        sleep(2); // simulate consumption time
    }
    return NULL;
}

int main() {
    int m, n;
    printf("Enter number of producers: ");
    scanf("%d", &m);
    printf("Enter number of consumers: ");
    scanf("%d", &n);

    pthread_t prod[m], cons[n];
    int pid[m], cid[n];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < m; i++) {
        pid[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &pid[i]);
    }
    for (int i = 0; i < n; i++) {
        cid[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cid[i]);
    }

    for (int i = 0; i < m; i++) pthread_join(prod[i], NULL);
    for (int i = 0; i < n; i++) pthread_join(cons[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("\nAll producers and consumers finished execution.\n");
    return 0;
}
