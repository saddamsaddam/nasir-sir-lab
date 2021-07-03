#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define N 5
#define LEFT i>0?(i-1)%N:N-1
#define RITE (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2


int state[N];
int philosopher_num[N];

sem_t mutex;
sem_t sem_phil[N];

void * philosopher(void *);
void takechops(int);
void putchops(int);
void test(int);

main(int argc,char **argv)
{
int k;
pthread_t tid[N];
printf("Dining Phiosophern");
for(k=0;k<N;k++)
{
philosopher_num[k]=k;
}
sem_init(&mutex,0,1);
for(k=0;k<N;k++) sem_init(&sem_phil[k],0,0);
for(k=0;k<N;k++) pthread_create(&tid[k],NULL,philosopher,&philosopher_num[k]);
for(k=0;k<N;k++) pthread_join(tid[k],NULL);
}

void * philosopher(void *param)
{
int i=*((int *)param);
int tt=1;
int et=2;
while(1)
{
sleep(tt);
takechops(i);
sleep(et);
putchops(i);
}
}

void takechops(int i)
{
sem_wait(&mutex);
state[i]=HUNGRY;
printf("Philosopher %d is hungryn",i);
test(i);
sem_post(&mutex);
sem_wait(&sem_phil[i]);
}

void putchops(int i)
{
sem_wait(&mutex);
state[i]=THINKING;
printf("Philosopher %d is thinkingn",i);
test(LEFT);
test(RITE);
sem_post(&mutex);
}

void test(int i)
{
if(state[i]==HUNGRY&&state[LEFT]!=EATING&&state[RITE]!=EATING){
state[i]=2;
printf("Philosopher %d is eatingn",i);
sem_post(&sem_phil[i]);
}
}
Share this:
