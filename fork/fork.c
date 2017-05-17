#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


int main( int argc, char** argv)
{
    int pid;
    int status;

    pid = fork();

    if(  pid == 0)
    {
        int ret;

        char** my_argv;

        my_argv = malloc( 3*sizeof(char *));
        my_argv[0] = "ls";
        my_argv[1] = "-al";
        my_argv[2] = 0;

        ret = execv( "/bin/ls", my_argv);
        fprintf( stderr, "error: %s\n", strerror(errno));
        return -1;
    }

    printf( "I'm parent: %d\n", getpid());


    while( (pid = waitpid(0, &status, WNOHANG)) == 0)
    {
        printf( "waiting...\n");
        sleep(1);
    }

    printf( "child(%d) exit code: %d\n", pid, WEXITSTATUS(status));

}
