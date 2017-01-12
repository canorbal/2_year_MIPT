#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define PREFIX "It's a "

void usage(char *prog_name)
{
    fprintf( stderr, "Incorrect arguments\n");
    fprintf( stderr, "Usage:\n\t%s FILE\n", prog_name);
}

int logic(char *file_name)
{
    int f = -1;
    char *buff = 0;
    int ret = 0;
    
    f = open(file_name, O_CREAT | O_RDWR | O_EXCL, 0666);

    if(f == -1)
    {
        fprintf( stderr, "Can't open file %s: %s\n", file_name, strerror(errno));
        ret = 1;
        goto out;
    }

    buff = malloc(strlen(PREFIX) + strlen(file_name) + 2);
    if(buff == 0)
    {
        fprintf( stderr, "Can't allocate memory\n");
        ret = 1;
        goto out;
    }

    sprintf(buff, "%s%s\n", PREFIX, file_name);

    if(write(f, buff, strlen(buff)) < 0)
    {
        fprintf( stderr, "Can't write to file %s: %s\n", file_name, strerror(errno));
        ret = 1;
        goto out;
    }

    out:
        if(f >= 0)
            close(f);

        if(buff != 0)
            free(buff);

        return ret;
}

int main(int argc, char **argv)
{
    if( argc != 2)
    {
        usage( argv[0]);
        return 1;
    }
    
    return logic(argv[1]);
}
