#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_STRING_SIZE 256
#define MAX_PROG_NAME_SIZE 16
#define MAX_ARGS_SIZE 64
#define MAX_ARGS_NUM 16

struct program
{
	char* name;
	char** args;
};

int spawn_proc (int in, int out, struct program *cmd)
{
	pid_t pid;

	if ((pid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2 (in, 0);
			close (in);
		}

		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}

		return execvp (cmd->name, cmd->args);
	}
	return pid;
}


int launch_prog(struct program* first, struct program* second)
{
	if (second != NULL){
		int in, fd[2];

		in = 0; // first process take input from stdin

		pipe(fd);
		spawn_proc(in, fd[1], first);
		close(fd[1]);

		int fd_2[2];
		pipe(fd_2);
						
		spawn_proc(fd[0], fd_2[1], second);
	
		close(fd_2[1]);	
		char s[300];	
		int tmp = 0;
		int size = 0;
	
		while ((tmp = read(fd_2[0], s, 300)) > 0){
		size+=tmp;
		printf("%s", s);
		}
	
		printf("readed bytes %d\n", size);
	}

	if (second == NULL){
		int fd[2];
		pipe(fd);
		spawn_proc(0, fd[1], first);

		close(fd[1]);

		char s[300];	
		int tmp = 0;
		int size = 0;

		while ((tmp = read(fd[0], s, 300)) > 0){
			size+=tmp;
			printf("%s", s);
		}
		
		printf("readed bytes %d\n", size);
	}

}


struct program* free_memory(struct program* prog)
{
	if (prog == NULL){
		return NULL;
	}

	if (prog->name != NULL){
		free(prog->name);
		prog->name = NULL;
	}


	if (prog->args != NULL){
		int i;
		for(i=0; i<MAX_ARGS_NUM; ++i){
			if (prog->args[i] != NULL){
				free(prog->args[i]);
				prog->args[i] = NULL;
			}
		}
	}

	free(prog->args);
	prog->args = NULL;

	return NULL;
}



struct program* allocate_memory()
{
	struct program* prog = NULL;
	prog = malloc(sizeof(struct program));
	if (prog == NULL){
		fprintf(stderr,"Can't allocate memory for struct program\n");
		goto allocate_out;	
	}

	prog->name = NULL;
	prog->name = malloc(MAX_PROG_NAME_SIZE*sizeof(char));
	if (prog->name == NULL){
		fprintf(stderr, "Can't allocate memory for prog_name\n");
		goto allocate_out;
	}

	prog->args = NULL;
	prog->args = malloc(MAX_ARGS_NUM*sizeof(char*));
	if (prog->args == NULL){
		fprintf(stderr, "Can't allocate memory for prog_args\n");
		goto allocate_out;
	}

	int i;
	for(i=0; i<MAX_ARGS_NUM; ++i){

		prog->args[i] = NULL;
		prog->args[i] = malloc(MAX_ARGS_SIZE*sizeof(char));
		if (prog->args[i] == NULL){

			fprintf(stderr, "Can't allocate memory for args[%d]\n", i);
			goto allocate_out;
			}
	}
	
	return prog;
					
	allocate_out:
		free_memory(prog);
		return NULL;
}	

struct program* parse(char* prog_line)
{
	char* sep = " \n\0\t";
	struct program* prog = allocate_memory();
	if (prog == NULL){
		return NULL;
	}
		
	char* buff = NULL;
	
	buff = strtok(prog_line, sep);
	
	prog->name = buff;
	
	//printf("prog_name = %s\n", prog->name);

	int j=0;
	while (buff != NULL) {
		strcpy(prog->args[j], buff);
		//printf("prog->args[%d] = %s\n", j, prog->args[j]);
		++j;
		buff = strtok(NULL, sep);
		//printf("buff = %s\n", buff);
	}
	prog->args[j] = NULL;
	
	return prog;	
}


int start_session()
{
	printf("***********SHELL*************\n");
	printf("**write down shell commands**\n");
	
	char* line = NULL;
	line = malloc(MAX_STRING_SIZE * sizeof(char));

	
	fflush(stdin); // clear stream
	fgets(line, MAX_STRING_SIZE, stdin);
	if(line == NULL){
		fprintf(stderr, "Wrong input");
		// usage();
	}

	printf("%s\n", line);	
	
		

	if (line == NULL){
		return -1;
	}
		
	char* sep = "\n|";
	
	char* first = strtok(line, sep);
	char* second = strtok(NULL, sep);
	
	printf("now first = %s\n", first);
	printf("now second = %s\n", second);
	
	struct program* first_prog = NULL;

	if (first == NULL){
		return -1;
	}
	first_prog = parse(first);


	//printf("first_prog --%s--%s--%s--%s--\n", first_prog->args[0], first_prog->args[1], first_prog->args[2], first_prog->args[3]);
	struct program* second_prog = NULL;
	if (second != NULL){
		second_prog = parse(second);
	}

	//printf("second_prog --%s--%s--%s--%s--\n", second_prog->args[0], second_prog->args[1], second_prog->args[2], second_prog->args[3]);
	
	launch_prog(first_prog, second_prog);
}


int main(int argc, char** argv)
{	
	while(1){
		start_session();
	}
	return 0;
}
