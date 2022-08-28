#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    int fd = open("./myfile", O_RDWR, S_IRUSR|S_IWUSR);
    struct stat sb;

    if (fstat(fd, &sb) == -1) {
        perror ("Could not get the file size.\n");
    }

    printf("Check the virtual memory map(/proc/%d/maps) and press enter.\n",
            getpid());
    getchar();
    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE,
            MAP_SHARED, fd, 0);
    printf("Check the virtual memory map(/proc/%d/maps) again. You will see an"
            " extra entry of 1 page for the mmap'ed file.\n", getpid());
    getchar();

    munmap(file_in_memory, sb.st_size);
    close(fd);
}
