#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define N 5

sem_t chopstick[N];
pthread_mutex_t mutex; // To pick both chopsticks atomically

void* philosopher(void* num) {
    int id = *((int*)num);
    while (true) {
        // Thinking
        cout << "Philosopher " << id << " is thinking.\n";
        sleep(1);

        // Try to pick up chopsticks
        pthread_mutex_lock(&mutex); // Enter critical section
        if (sem_trywait(&chopstick[id]) == 0 && sem_trywait(&chopstick[(id + 1) % N]) == 0) {
            pthread_mutex_unlock(&mutex); // Exit critical section
            cout << "Philosopher " << id << " picked up chopsticks and is eating.\n";
            sleep(2); // Eating
            sem_post(&chopstick[id]);
            sem_post(&chopstick[(id + 1) % N]);
            cout << "Philosopher " << id << " finished eating and put down chopsticks.\n";
        } else {
            // Could not pick both, release any acquired
            if (sem_trywait(&chopstick[id]) == 0) sem_post(&chopstick[id]);
            if (sem_trywait(&chopstick[(id + 1) % N]) == 0) sem_post(&chopstick[(id + 1) % N]);
            pthread_mutex_unlock(&mutex); // Exit critical section
        }

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t phil[N];
    int ids[N];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);

    return 0;
}
