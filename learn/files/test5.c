#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

int main(void)
{
    int fd1, fd2;
    char buf[BUF_SIZE];

    fd1 = open("./somefile.txt", O_RDWR|O_CREAT); 

    if (fd1 == -1) {
        printf("file open failed.\n");
    }

    strcpy(buf, "ONE ");
    if (write(fd1, buf, strlen(buf)) != strlen(buf)) {
        printf("Write failed.\n");
    } 

    fd2 = dup(fd1);

    strcpy(buf, "TWO ");
    if (write(fd2, buf, strlen(buf)) != strlen(buf)) {
        printf("Write failed.\n");
    } 
	return 0;
}
