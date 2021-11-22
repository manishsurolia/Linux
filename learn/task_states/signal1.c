#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int num)
{
    printf("I am main task's sig_handler. Wont die..\n");
    return;
}

int main(void)
{
    signal(SIGINT, sig_handler);
    getchar();
    printf("Main task is over.\n");
    return 0;
}
