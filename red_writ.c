#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex,wrt;
int readcnt=0;
void * reader(void * data)
{sem_wait(&mutex);
readcnt++;
if(readcnt==1)
sem_wait(&wrt);
sem_post(&mutex);
printf("\n Reading");
sem_wait(&mutex);
readcnt--;
if(readcnt==0)
sem_post(&wrt);
sem_post(&mutex);
}void * writer(void * data)
{
sem_wait(&wrt);
printf("\nwriting");
sem_post(&wrt);
}

int main()
{
sem_init(&wrt,0,1);
sem_init(&mutex,0,1);

pthread_t read[5] ,write[5];
int i=0;
for(i=0; i<5; i++)
{
pthread_create(&write[i],NULL,writer,NULL);
pthread_create(&read[i],NULL,reader,NULL);
}

for(i=0; i<5; i++)
pthread_join(write[i],NULL);
for(i=0; i<5; i++)
pthread_join(read[i],NULL);

sem_destroy(&mutex);
sem_destroy(&wrt);
return 0;
}
