#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t readTry, rmutex, wmutex, resource;
int read_count = 0, write_count = 0;
int data = 0; // Shared variable

void* reader(void* arg) {
    int id = *((int*)arg);
    while (true) {
        sem_wait(&readTry);
        sem_wait(&rmutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&resource);
        sem_post(&rmutex);
        sem_post(&readTry);

        cout << "Reader " << id << " is reading data = " << data << endl;
        sleep(1);

        sem_wait(&rmutex);
        read_count--;
        if (read_count == 0)
            sem_post(&resource);
        sem_post(&rmutex);

        sleep(2);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (true) {
        sem_wait(&wmutex);
        write_count++;
        if (write_count == 1)
            sem_wait(&readTry);
        sem_post(&wmutex);

        sem_wait(&resource);
        data++;
        cout << "Writer " << id << " is writing data = " << data << endl;
        sleep(2);
        sem_post(&resource);

        sem_wait(&wmutex);
        write_count--;
        if (write_count == 0)
            sem_post(&readTry);
        sem_post(&wmutex);

        sleep(3);
    }
    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    sem_init(&readTry, 0, 1);
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&resource, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&readTry);
    sem_destroy(&rmutex);
    sem_destroy(&wmutex);
    sem_destroy(&resource);

    return 0;
}
