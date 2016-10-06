#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>


#define PROG_SIZE 100
#define ARG_SIZE 100
#define STR_SIZE 100
#define N 100

struct processes
{
  char* time_str[N];
  int time[N];
  int count;
  char* prog_name[N];
  char* args[N];
  char str[N][100];
};

struct process
{
  int time;
  char* prog_name;
  char* args;
};

void usage(char *prog_name)
{
    fprintf(stderr, "Incorrect arguements\n");
    fprintf(stderr, "Usage: %s\n", prog_name);
}

int parsing(struct processes* ptr)
{
  int i;
  for (i = 0; i < ptr->count; i++)
   {
    ptr->time_str[i] = malloc(sizeof(char)*10);
    if (ptr->time_str[i]==NULL)
    {
      fprintf(stderr, "Can't allocate memory\n");
      fprintf(stderr, "%s\n", strerror(errno));
      return -1;
    }

    ptr->time_str[i] = strtok(ptr->str[i], " ,");
    if (ptr->time_str[i]==NULL)
    {
      fprintf(stderr, "Can't parse string %s in %d str\n", ptr->str[i], i);
      return -1;
    }

    ptr->prog_name[i] = malloc(sizeof(char)*20);
    if (ptr->prog_name[i] == NULL)
    {
      fprintf(stderr, "Can't allocate memory\n");
      fprintf(stderr, "%s\n", strerror(errno));
      return -1;
    }

    ptr->prog_name[i] = strtok(NULL, " ,");
    if (ptr->prog_name[i]==NULL)
    {
      fprintf(stderr, "Can't parse string %s in %d str\n", ptr->str[i], i);
      return -1;
    }

    ptr->args[i] = malloc(sizeof(char)*20);
    if (ptr->time_str[i]==NULL)
    {
      fprintf(stderr, "Can't allocate memory\n");
      fprintf(stderr, "%s\n", strerror(errno));
      return -1;
    }

    ptr->args[i] = strtok(NULL, " ,");
    if (ptr->args[i]==NULL)
    {
      fprintf(stderr, "Can't parse string %s in %d str\n", ptr->str[i], i);
      return -1;
    }
  }
  return 1;
}

struct processes* get_processes(char* file_name)
{
  FILE* f;
  f = fopen(file_name, "r");

  if (f==NULL)
  {
    fprintf(stderr,"Can't open file %s\n", file_name);
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  struct processes* ptr = NULL;
  ptr = malloc(sizeof(struct processes));

  if (ptr == NULL)
   {
    fprintf(stderr, "Can't allocate memory\n");
    fprintf(stderr, "%s\n", strerror(errno));
    fclose(f);
    return NULL;
  }

  ptr->count=0;

  while (fgets(ptr->str[ptr->count], STR_SIZE, f) != NULL)
  {
    if (ferror(f))
    {
      fprintf(stderr, "Error in reading file %s\n", file_name);
      fclose(f);
      return NULL;
    }
    ptr->count++;
  }
  fclose(f);
  int flag = -1;
  flag = parsing(ptr);
  if (flag == -1)
  {
    return NULL;
  }
  return ptr;
}

int get_sleep_time(struct processes* ptr)
{
  int i;
  for (i=0; i<ptr->count; i++)
  {
    char* wrongsym = NULL;
    ptr->time[i] = strtol(ptr->time_str[i], &wrongsym, 10);

    if ( strcmp(wrongsym, "\0") != 0)
    {
      fprintf(stderr, "Can't convert %s to int\n", ptr->time_str[i]);
      return -1;
    }
  }
  return 1;
}

int compare(const void * x1, const void * x2)   // функция сравнения элементов массива
{
  return ((struct process*)x1)->time - ((struct process*)x2)->time;              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int main(int argc, char** argv)
{
  if (argc !=2 )
  {
    usage(argv[0]);
    return -1;
  }

  struct processes* ptr = get_processes(argv[1]);
  if (ptr==NULL)
  {
    return -1;
  }

  int i;

  int flag = get_sleep_time(ptr);
  if (flag==-1)
  {
    return -1;
  }

  struct process list[ptr->count];

  for (i = 0; i < ptr->count; i++)
  {
      list[i].time = ptr->time[i];
      list[i].prog_name = ptr->prog_name[i];
      list[i].args = ptr->args[i];
      //free(ptr->args[i]);
  }

  qsort(list, 3, sizeof(struct process), compare);

  for (i = 0; i < ptr->count; i++)
  {
    list[i].args[strlen(list[i].args)-1]=0;
    printf("%d %s ------%s-------\n",list[i].time, list[i].prog_name, list[i].args);
  }
  printf("\n\n");

  for (i = ptr->count-1; i >=1; i--)
  {
    list[i].time-=list[i-1].time;
  }

  /*for (i = 0; i < ptr->count; i++)
  {
    printf("%d %s %s\n",list[i].time, list[i].prog_name, list[i].args);
  }*/
  printf("\n\n");


  i = 0;
  int status;
  while (i<ptr->count)
  {
    int pid = fork();
    if (pid == 0)
    {
      sleep(list[i].time);
      printf("I start process %s\n",list[i].prog_name);
      execlp(list[i].prog_name, list[i].prog_name, list[i].args, 0);
    }
    else
    {
      if (pid == waitpid(pid, &status, WNOHANG))
      {
        printf( "child(%s) exit code: %d\n", list[i].prog_name, WEXITSTATUS(status));
      }
      else
      {
        printf("waaaaaaaaait\n" );
        i++;
      }
    }
  }

  return 0;
}
