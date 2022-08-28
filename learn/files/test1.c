#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

int main(void)
{
    int fd;
    char buf[BUF_SIZE];

    fd = open("./somefile.txt", O_RDWR|O_CREAT); 

    if (fd == -1) {
        printf("file open failed.\n");
    }

    strcpy(buf, "ONE ");
    if (write(fd, buf, strlen(buf)) != strlen(buf)) {
        printf("Write failed.\n");
    } 

    strcpy(buf, "TWO ");
    if (write(fd, buf, strlen(buf)) != strlen(buf)) {
        printf("Write failed.\n");
    } 
	return 0;
}
