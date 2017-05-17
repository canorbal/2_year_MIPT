#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define B_SIZE 1000

void usage(char *prog_name)
{
    fprintf(stderr, "Incorrect arguements: wrong number of arguements\n");
    fprintf(stderr, "Usage: \n");
    fprintf(stderr, "./cp.o filename_from filename_to\n");
}

int open_input(char* input_name)
{
    int f = -1;
    f = open(input_name, O_RDONLY);
    if (f == -1)
    {
        fprintf(stderr, "Can't open file %s\n", input_name);
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }
    return f;
}

int open_output(char* output_name)
{
    int out = -1;
    out = open(output_name, O_CREAT | O_WRONLY | O_EXCL, 0666);
    if (out == -1)
    {
        fprintf(stderr, "Can't open file %s\n", output_name);
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }
    return out;
}

int copy(char* input_file, char* output_file)
{
    int ret = 1;
    int input = -1;
    int output = -1;

    input = open_input(input_file);
    if (input == -1)
    {
        ret = -1;
        goto out;
    }

    output = open_output(output_file);
    if (output == -1)
    {
        ret = -1;
        goto out;
    }

    char buf[B_SIZE];
    int bytes = 1;

    while (bytes>0)
    {
        bytes = read(input, buf, bytes);
        if (bytes == -1)
        {
            fprintf(stderr, "Can't read file %s\n", input_file);
            fprintf(stderr, "%s\n", strerror(errno));
            ret = -1;
            goto out;
        }   
        int flag = -1;
        buf[bytes] = 0;
        flag = write(output, buf,	bytes);

        if (flag == -1)
        {
            fprintf(stderr, "Can't write to file %s\n", output_file);
            fprintf(stderr, "%s\n", strerror(errno));
            ret = -1;
            goto out;
        }
    }

    out:
        if (input>=0)
        {
            close(input);
        }
        if (output>=0)
        {
            close(output);
        }
        return ret;
}


int main(int argc, char** argv)
{
    if (argc!=3)
    {
        usage(argv[0]);
        return -1;
    }

    int cp = copy(argv[1], argv[2]);

    if (cp == -1)
    {
        return -1;
    }

    return 0;
}
