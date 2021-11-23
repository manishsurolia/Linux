#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>

void *func(void *args)
{
    printf("Creating child inside a thread.\n");
    if (fork() == 0) {
        printf("child has pid : %d, ppid : %d\n", getpid(), getppid());
    } else {
        wait(NULL);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1;
    printf("Main task pid : %d\n", getpid());
    pthread_create(&t1, NULL, func, "T1");
    pthread_join(t1, NULL);
    return 0;
}
