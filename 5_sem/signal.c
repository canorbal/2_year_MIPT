#include <signal.h>
#include <string.h>
#include <stdio.h>

void handler(int signal)
{
  print("received signal %d", signal)
  int i = counter;
  counter = i;
}

void add(int signal)
{
  print("received signal %d", signal)
  int i = counter;
  i--;
  counter = i;
}

void print_cnt(int signal)
{
  fprintf( "counter=%d\n",counter);
}

int counter = 0;

int main()
{

  FILE* f = fopen("process.pid","wt");

  //printf("my pid = %d\n",getpid());
  fclose(f);

  struct sigaction sa, sa_old;
  memset(&sa, 0, sizeof(sa)); <-- заполняет одним и тем же байтом все адресное пространствоа
  sa.sa_handler = add;
  sigfillset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, 0);  // еще вариант sigaction(SIGUSR1, &sa, &sa_old); в sa_old записывается
                                              //                     обработчик, который стоят до этого

  sa.sa_handler  = sub;
  sigaction()


  signal(SIGUSR1, add);  // при получении сигнала SIGUSR1 будет вызвана функция handler
  signal(SIGUSR2, sub);
  signal(SIGHUP,  print_cnt)

  while (1)  //// <--  ПРАВИЛЬНЫЙ sleep()
    sleep(100);
  // функция sleep ненадежная, потому что может прекратиться при получении сигнала
  // аналогично функция read (может получить какой-нибудь сигнал)
  return 0;
}
