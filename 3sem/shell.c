#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_STRING_SIZE 256
#define MAX_PROG_NAME_SIZE 16
#define MAX_ARGS_SIZE 8
#define MAX_ARGS_NUM 16

struct program
{
	char* name;
	char** args;
};


void launch_prog(char* first, char* second)
{
	int fd[2], result;
	ssize_t size;

	if (pipe(fd) < 0) {
     	printf("Can't open pipen");
     	exit(-1);
   	}
	
	result = fork();

	if(result < 0) {
      		printf("Can't fork childn");
      		exit(-1);
	}

	if (result > 0) {
	/* Parent process */
	}

      	close(fd[0]);

      	size = write(fd[1], "Hello, world!", 14);

      	if(size != 14){
        	printf("Can't write all string to pipen");
        	exit(-1);
      	}

     	close(fd[1]);
      	printf("Parent exitn");
	
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
	prog->args = malloc(sizeof(char*));
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
		
	struct program* first;	
	first = allocate_memory();
	if (first == NULL){
		return -1;
	}
	
	char* sep = "\n |";
	
	printf("%s\n", line);
	first->name = strtok(line, sep);
	if (first->name == NULL){
		fprintf(stderr, "Can't parse line %s", line);
		return -1;
	}

	printf("first->name = %s\n", first->name);
	
	char* buff;

	buff = strtok(NULL, sep);

	int j=0;
	while (buff != NULL) {
		strcpy(first->args[j], buff);
		++j;
		buff = strtok(NULL, sep);
	}
	first->args[j] = NULL;
	
	
}


int main(int argc, char** argv)
{	
	start_session();
		
	return 0;
}
