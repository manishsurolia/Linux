#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t t1_sem, t2_sem;

void sig_handler(int num)
{
    printf("I am in main task sig_handler. Wont die..\n");
    return;
}

void sig_handler1(int num)
{
    printf("I am in task1 sig_handler. Wont die..\n");
    return;
}

void sig_handler2(int num)
{
    printf("I am in task2 sig_handler. Wont die..\n");
    return;
}

void *func1(void *args)
{
    signal(SIGINT, sig_handler1);
    while (1) {
        sem_wait(&t2_sem);
        printf("Task 1 running.\n");
        sleep(10);
        printf("Task 1 sleep is over.\n");
        sem_post(&t1_sem);
    }
    return NULL;
}

void *func2(void *args)
{
    signal(SIGINT, sig_handler2);
    while (1) {
        sem_wait(&t1_sem);
        printf("Task 2 running.\n");
        sleep(10);
        printf("Task 2 sleep is over.\n");
        sem_post(&t2_sem);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    sem_init(&t1_sem, 0, 0);
    sem_init(&t2_sem, 0, 1);
    signal(SIGINT, sig_handler);
    pthread_create(&t1, NULL, func1, "T1");
    sleep(1);
    pthread_create(&t2, NULL, func2, "T2");

    while (1) {
        sleep(50);
        printf("Main task's sleep is over. Again going for sleep\n");
    }

    return 0;
}
