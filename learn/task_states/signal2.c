#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int num)
{
    printf("I am in main task's sig_handler. Wont die..\n");
    return;
}

int main(void)
{
    signal(SIGINT, sig_handler);
    sleep(50);
    printf("Main thread sleep is over.\n");
    return 0;
}
