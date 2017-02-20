#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        printf("\n");
        printf("I'm a child\n");
        printf("My getpid() = %d\n", getpid());
        printf("My getppid = %d\n", getppid());
        printf("My int pid = %d\n", pid);
        printf("\n");
    }
    else
    {
        printf("\n");
        printf("I'm a parent\n" );
        printf("My getpid() = %d\n", getpid());
        printf("My int pid = %d\n", pid);
        printf("\n");
        sleep(10);
    }
    return 0;
}
