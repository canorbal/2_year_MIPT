#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#define MAX_STRING_SIZE 124
#define MAX_NUMBER_PROG 128
#define MAX_PROG_NAME_SIZE 64
#define MAX_ARG_SIZE 64
#define	MAX_ARG_NUMB 16


struct program
{
	int time;
	int count_of_args;
	char* prog_name;
	char** args;
	pid_t pid;
};

void usage()
{
	printf(
	"\n\n############################################################\n"
	"\tEXECUTOR.\n"
	"EXECUTOR begin programs according to your plan of execution.\n\n"
	"############################################################\n"
	"Description.\n"
	"\texecuter [FILE\n"
	"FILE is a text file which contains info about programs to execute: \n\n"
	"#############################################################\n"
	"FORMAT:\n"
	"\t [SHIFT [PROG_NAME [ARG(1) ... [ARG(N)\n"
	"[SHIFT should be in seconds.\n\n"
	);
}



int sort_programs(const char* path)
{
	pid_t sort_pid;
	int sort_stat;
	int file = 0;
	int exec_stat, wait_stat;

	sort_pid = fork();

	switch (sort_pid) {
		case -1:
			printf("Something went wrong with fork()\nReason: %s\n", strerror(errno));
        	return -1;

		case 0:
			exec_stat = execlp("sort", "sort", "-n", path, "-o", "tmp_sorted_programs.txt", NULL);
			if (exec_stat == -1) {
				fprintf(stderr, "Something went wrong with execlp()\nReason: %s\n", strerror(errno));
				return -1;
			}
			break;

		default:
			wait_stat = waitpid(sort_pid, &sort_stat, 0);
			if (wait_stat == -1) {
				fprintf(stderr, "Something went wrong with waitpid()\nReason: %s\n", strerror(errno));
				return -1;
			}
			break;
		}

	if (sort_stat != 0){
		printf("sort ended with code %d\n", sort_stat);
		return -1;
	}
	// If WIFEXITED returns TRUE it means that child terminated successfully
	if (WIFEXITED(sort_stat))
		return  0;
	else
		return -1;
}

void free_memory(struct program* programs)
{
	if (programs == NULL){
		return;
	}
	int i;
	for(i=0; i<MAX_NUMBER_PROG; ++i){
		if (programs[i].prog_name != NULL){
			free(programs[i].prog_name);
			programs[i].prog_name = NULL;
		}

		int j;
		for(j=0; j<MAX_ARG_NUMB; ++j){
			if (programs[i].args[j] != NULL){
				free(programs[i].args[j]);
				programs[i].args[j] = NULL;
			}
		}
		free(programs[i].args);
		programs[i].args = NULL;
	}
	free(programs);
	programs = NULL;
}

struct program* allocate_memory()
{
	struct program* programs = calloc(MAX_NUMBER_PROG, sizeof(struct program));
	if (programs == NULL){
		fprintf(stderr, "Can't allocate memory for array of programs\nReason: %s", strerror(errno));
		return NULL;
	}

	int i;
	for(i = 0; i< MAX_NUMBER_PROG; ++i){
		programs[i].prog_name = calloc(MAX_PROG_NAME_SIZE, sizeof(char));
		if (programs[i].prog_name == NULL){
			fprintf(stderr, "Can't allocate memory for prog_name array\nReason: %s", strerror(errno));
			goto allocate_out;
		}
		programs[i].args = calloc(MAX_ARG_NUMB, sizeof(char*));
		if (programs[i].args == NULL){
			fprintf(stderr, "Can't allocate memory for args array\nReason: %s", strerror(errno));
			goto allocate_out;
		}
		int j;
		for(j=0; j<MAX_ARG_NUMB; ++j){
			programs[i].args[j] = calloc(MAX_ARG_SIZE, sizeof(char));
			if (programs[i].args[j] == NULL){
				fprintf(stderr, "Can't allocate memory for args[%d] array\nReason: %s", j, strerror(errno));
				goto allocate_out;
			}
		}
	}
	return programs;

	allocate_out:
		free_memory(programs);
		return NULL;
}

struct program* read_programs()
{
	// open tmp_sorted_programs.txt
	FILE* file = fopen("tmp_sorted_programs.txt", "r");
	if (file == NULL) {
        fprintf(stderr, "Can't open file \"tmp_sorted_programs.txt\"\n");
		return NULL;
	}

	struct program* programs = allocate_memory();
	if (programs == NULL){
		return NULL;
	}

	// read tmp_sorted_programs.txt
	char string[MAX_STRING_SIZE];
	char rec_string[MAX_STRING_SIZE];
	char* sep = " \n";
	int i = 0;

	while (fgets(string, MAX_STRING_SIZE-1, file) != NULL){

		strcpy(rec_string, string);
		char* endptr = NULL;
		char* buff;

		buff = strtok(string, sep);

		if (buff == NULL) {
        	fprintf(stderr, "Something went wrong with time in line: %s\n", rec_string);
			usage();
        	goto read_programs_out;
    	}

		programs[i].time = strtol(buff, &endptr, 10);
		if (strcmp(endptr, "\0") != 0) {
			fprintf(stderr, "Incorrect time argument in program in line %s\n", rec_string);
			usage();
			goto read_programs_out;
		}

		buff = strtok(NULL, sep);

		int j=0;
		while (buff != NULL) {
			strcpy(programs[i].args[j], buff);
			++j;
			buff = strtok(NULL, sep);
		}
		programs[i].args[j] = NULL;
		programs[i].count_of_args = j;

		++i;
	}

	fclose(file);
	return programs;

	read_programs_out:
		fclose(file);
		free_memory(programs);
		return NULL;
}

int run_programs(struct program* programs)
{
	int i,j;
	int time_shift=0;
	int prev_time = 0;

	int ret = 0;
	int numb_of_proc = 0;


	for(i=0; i<MAX_NUMBER_PROG; ++i){

		if(programs[i].args[0] != NULL)
			time_shift = programs[i].time - prev_time;

		if (time_shift > 0) {
            sleep(time_shift);
            prev_time += time_shift;
		}

		if ( (programs[i].args[0] != NULL) && ((strcmp(programs[i].args[0],"\0") !=0 ) ))  {
			int fork_ret = fork();
		    switch(fork_ret) {
				case -1:
					fprintf(stderr, "Error in fork()\n");
					return -1;

		        case 0:
		            if (execvp(programs[i].args[0], programs[i].args) == -1) {
		                fprintf(stderr, "execvp() error with %s: %s\n", programs[i].args[0], strerror(errno));
						return -1;
		            }
					break;

		        default:
					programs[i].pid = fork_ret;
					++numb_of_proc;
		    }
		}
	}

	while (numb_of_proc > 0) {
		int status_ret;
		int waitpid_ret = waitpid(-1, &status_ret, 0);

		for(j=0; j<i; ++j){
			if (waitpid_ret == programs[j].pid){
			printf("process %s ended with code %d\n",programs[j].args[0], status_ret);
			programs[j].pid = -1;
			numb_of_proc--;
			}
		}
	}

	return 0;
}


int main(int argc, char** argv)
{
	if (argc != 2){
		usage();
		exit(EXIT_FAILURE);
	}

	int sort_stat =  sort_programs(argv[1]);
	if (sort_stat == -1) {
		printf("Error in sorting.\n");
		exit(EXIT_FAILURE);
	}


	struct program* programs = read_programs();
	if (programs == NULL){
		goto error_exit;
	}

	int run = run_programs(programs);
	if(run == -1){
		goto error_exit;
	}

	free_memory(programs);
	return EXIT_SUCCESS;

	error_exit:
		free_memory(programs);
		exit(EXIT_FAILURE);
}
