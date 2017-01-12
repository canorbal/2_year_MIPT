#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>


void usage()
{
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
            "\tCOPY PROGRAM ON SIGNAL.\n"
            "It allows you to copy files using signals\n"
            "SYNOPSIS\n"
            "\tsignalcp [FILE_FROM] [FILE_TO] \n\n"
            "DESCRIPTION\n"
            "\tFILE_FROM - is a file which should be copied to FILE_TO\n\n" 
            "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
             );
}

pid_t pid;
int output_char = 0;
int counter = 128;

// SIGCHLD
void childexit(int sign) 
{
    exit(EXIT_SUCCESS);
}

// SIGALRM
void parentexit(int sign) 
{ 
	exit(EXIT_FAILURE);
}

// Nothing
void nothing(int sign) {
}


// SIGUSR2
void zero_handler(int sign) 
{ 	
	counter /= 2;	
	kill(pid, SIGUSR1);
}


// SIGUSR1
void one_handler(int sign) 
{
	output_char += counter;
	counter /= 2;	
	kill(pid, SIGUSR1);
}

int copy(char** argv)
{
	pid_t parent_pid = getpid();     
	sigset_t set;

	// при SIGCHLD - выходим
	struct sigaction child_exit_action;
	memset(&child_exit_action, 0, sizeof(child_exit_action));
	child_exit_action.sa_handler = childexit; 
	sigfillset(&child_exit_action.sa_mask); 
	sigaction(SIGCHLD, &child_exit_action, NULL); 

	// SIGUSR1 - one_handler()
	struct sigaction one_signal;
	memset(&one_signal, 0, sizeof(one_signal));
	one_signal.sa_handler = one_handler;
	sigfillset(&one_signal.sa_mask);
	sigaction(SIGUSR1, &one_signal, NULL);

	// SIGUSR2 - zero_handler()
	struct sigaction zero_signal;
	memset(&zero_signal, 0, sizeof(zero_signal));
	zero_signal.sa_handler = zero_handler;
	sigfillset(&zero_signal.sa_mask);    
	sigaction(SIGUSR2, &zero_signal, NULL);
								       
	//  блокировки
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, NULL );
	sigemptyset(&set);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Can't open file %s\n", argv[1]);
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

	pid = fork();
    if (pid == 0) 
    {
		sigemptyset(&set); // очищаем набор сигналов

		// SIGUSR1 - nothing()
		struct sigaction nothing_action;                    
		memset(&nothing_action, 0, sizeof(nothing_action));
		nothing_action.sa_handler = nothing;
		sigfillset(&nothing_action.sa_mask);    
		sigaction(SIGUSR1, &nothing_action, NULL);
		
        // SIGALRM - parentexit()

		struct sigaction alarm_action;
		memset(&alarm_action, 0, sizeof(alarm_action));
		alarm_action.sa_handler = parentexit;
		sigfillset(&alarm_action.sa_mask);
		sigaction(SIGALRM, &alarm_action, NULL);

        int i;
	    char c;	
		while (read(fd, &c, 1) > 0)
        {
			// SIGALRM Будет получен если родитель не успеет ответить за секунду
			alarm(1);
			// Побитовые операции		
			for ( i = 128; i >= 1; i /= 2)
            {	
				if ( i & c )  
				 // 1 
					kill(parent_pid, SIGUSR1);
				else 
				// 0 
					kill(parent_pid, SIGUSR2);
					// Ждём подтверждения от родителя
					// приостанавливает процесс до получения сигнала
					sigsuspend(&set); 
			} 
		}
		exit(EXIT_SUCCESS);
	}
	// Получаем пока ребёнок не умрёт
    int out = open(argv[2], O_CREAT | O_WRONLY | O_EXCL, 0666);
    if (out == -1)
    {
        fprintf(stderr, "Can't copy in file %s\n", argv[2]);
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }

	do 
    {	
		if(counter == 0)
        {       // считали весь байт
			write(out, &output_char, 1);          
			counter=128;
			output_char = 0;
		}
		sigsuspend(&set); // Ждём сигнал от ребёнка
	} while (1);
    return 0;
}


int main(int argc, char ** argv)
{
	if (argc != 3) 
    {
		usage();
		exit(EXIT_FAILURE);
	}
    int cp = copy(argv);
	if (cp == -1)
    {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

