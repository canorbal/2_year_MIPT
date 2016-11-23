#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char **argv)
{
    int fd[2];
    pipe(fd);

    if( fork() == 0)
    {
        dup2(fd[1],1);

        close(fd[0]);
        close(fd[1]);

        execlp("ps", "ps", 0);
    }

    if( fork() == 0)
    {
        dup2(fd[0], 0);

        close(fd[0]);
        close(fd[1]);

        execlp("wc", "wc", 0);
    }

    close(fd[0]);
    close(fd[1]);

    wait();
    wait();

    printf( "done\n");

}
