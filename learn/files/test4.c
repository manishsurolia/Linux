#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 100

int main(void)
{
    int fd;
    char buf[BUF_SIZE];

    fd = open("./somefile.txt", O_RDWR|O_CREAT); 
    if (fd == -1) {
        printf("file open failed.\n");
    }

    if (fork() == 0) {
        //child process.
        strcpy(buf, "ONE ");
        if (write(fd, buf, strlen(buf)) != strlen(buf)) {
            printf("Write failed.\n");
        }
    } else {
        //parent process.
        wait(NULL); // wait until child process is done.
        strcpy(buf, "TWO");
        if (write(fd, buf, strlen(buf)) != strlen(buf)) {
            printf("Write failed.\n");
        } 
    }

	return 0;
}
