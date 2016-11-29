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
#define MAX_PROG_NUM 20

struct program
{
	char* name;
	char** args;
};

int spawn_proc (int in, int out, struct program *cmd)
{
	pid_t pid;
	int ret = 0;

	pid = fork();
	
	if (pid == -1){
		fprintf(stderr, "Can't fork\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;	 
	}
	if (pid  == 0)
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

		int exec_stat = execvp (cmd->name, cmd->args);
		if ( exec_stat == -1) {
			fprintf(stderr, "Can't execute %s\n", cmd->name);
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	int wait_stat;
	int ret_stat;
	
	wait_stat = waitpid(pid, &ret_stat, WNOHANG);
	if (wait_stat == -1){
		fprintf(stderr, "Error in waitpid with process %s\n", cmd->name);
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	return 0;
}



int launch_prog(struct program** array_of_prog, int count)
{
		int in, fd[2];

		in = 0; // first process take input from stdin
		int ret = 0;
			
		int i;
		for (i=0; i<count; i++){
			
			ret = pipe(fd);
			if (ret == -1){
				fprintf(stderr, "Can't make pipe\n");
				fprintf(stderr, "%s\n", strerror(errno));
				return -1;
			}

			ret = spawn_proc(in, fd[1], array_of_prog[i]);
			if (ret == -1){
				goto out;
			}

			close(fd[1]);
			in = fd[0];
		}	
	
		char s[1];
		int tmp = 0;
		int size = 0;

		tmp = read(fd[0], s, sizeof(char));
		while (tmp  > 0){
			size+=tmp;
			printf("%c", s[0]);
			tmp = read(fd[0], s, sizeof(char));
			if (tmp == -1){
				fprintf(stderr,"Error in reading from pipe\n");
				fprintf(stderr, "%s\n", strerror(errno));
				goto out;
			}
		}
		
		close(fd[0]);
		printf("readed %d bytes\n", size);
	
		return 0;
		out:
			close(fd[0]);
			close(fd[1]);	
			return -1;

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
	char* sep = " \n\t";
	struct program* prog = allocate_memory();
	if (prog == NULL){
		return NULL;
	}

	char* buff = NULL;	

	buff = strtok(prog_line, sep);;
	strcpy(prog->name, buff);
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


	size_t size = 0;
	int len;
	len = getline(&line, &size, stdin);

	if (len == -1){
		fprintf(stderr, "Error in reading commands\n");
		return -1;
	}
	
	line[len] = '\0';

	printf("%s\n", line);

	char* sep = "|";

	struct program* array[MAX_PROG_NUM];
	char  str_array[MAX_PROG_NUM][MAX_ARGS_SIZE];
	
	int count = 0;

	char* buf = strtok(line, sep);
	

	while (buf != NULL){
		strcpy(str_array[count], buf);
		count++;
		buf = strtok(NULL, sep);
	}
	
	int i;
	for(i=0; i<count; i++){
		array[i] = parse(str_array[i]);	
	}

/*
	buf = strtok(NULL, sep);
	printf("buf = %s\n", buf);

*/
	/*for(i=0; i<count; i++){
		printf("cmd[%d] = %s\n", i, array[i]->name);
	}
	printf("count = %d\n", count);
	*/

	launch_prog(array, count);
	for(i=0; i<count; i++){
		free_memory(array[i]);
	}

}	


int main(int argc, char** argv)
{
	while(1){
		start_session();
	}
	return 0;
}
