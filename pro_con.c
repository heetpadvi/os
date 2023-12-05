#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20 // Maximum number of items to produce/consume

sem_t empty;
sem_t full;
sem_t mutex;
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;

void *producer(void *arg) {
    while (produced_count < MAX_ITEMS) {
        int item = rand() % 100 + 1; // Generate a random item
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        produced_count++;

        sem_post(&mutex);
        sem_post(&full);

        usleep(rand() % 2000000); // Sleep for a random time
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (consumed_count < MAX_ITEMS) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        consumed_count++;

        sem_post(&mutex);
        sem_post(&empty);

        usleep(rand() % 2000000); // Sleep for a random time
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
