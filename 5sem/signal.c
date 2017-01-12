#include <signal.h>
#include <stdio.h>
#include <string.h>

int counter = 0;

void add(int signum)
{
    printf("enter add\n");
    int eax = counter;
    sleep(5);
    eax++;
    counter = eax;
    printf("leave add\n");
}

void sub(int signum)
{
    printf("enter sub\n");
    int eax = counter;
    eax--;
    counter = eax;
    printf("leave sub\n");
}

void print_cnt(int signum)
{
    printf("counter=%d\n", counter);
}

int main()
{
    sigset_t mask, old_mask;
    sigfillset(&mask);
    sigprocmask( SIG_BLOCK, &mask, &old_mask);

    FILE *f = fopen("process.pid", "wt");
    fprintf(f, "%d", getpid());
    fclose(f);

    struct sigaction sa, sa_old;
    memset(&sa, 0, sizeof(sa));
    sigfillset(&sa.sa_mask);
    sa.sa_handler = add;
    sigaction(SIGUSR1, &sa, &sa_old);

    sa.sa_handler = sub;
    sigaction(SIGUSR2, &sa, 0);
    signal(SIGHUP, print_cnt);

    while(1) 
    {
        printf( "suspending...\n");
        sigsuspend( &old_mask);
        printf( "received signal, slipping 5 sec\n");
        sleep(5);
    }
    return 0;
}

