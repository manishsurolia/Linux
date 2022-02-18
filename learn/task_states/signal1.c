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
    printf("Calling getchar() is putting me in 'TASK_INTERRUPTABLE' state.\n");
    printf("When I am in 'TASK_INTERRUPTABLE' state, any 'ctrl-c' signal to \n"
           "me will put me back to the 'TASK_RUNNING' state and sig_handler \n"
           "function will be called and then again I will be moved to \n"
           "'TASK_INTERRUPTABLE' state. When an input required by 'getchar' \n"
           "is passed to me, I will be again moved to 'TASK_RUNNING' state \n"
           "and continue with the executeion of 'getchar' in main.\n");
    getchar();
    printf("Main task is over.\n");
    return 0;
}
