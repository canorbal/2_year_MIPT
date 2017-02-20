#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


double function(double x)
{
    return sin(x);
}


struct Task
{
    double from;
    double to;
    int n;
    pthread_t t;
    double s;
};

void * my_thread( void * arg)
{
    struct Task *t = (struct Task *)arg;
    double delta = (t->to - t->from)/t->n;
    double s = 0, x = t->from;
    int i;

    for(i=0; i<t->n; i++)
    {
        s += (function(x) + function(x+delta))/2 * delta;
        x += delta;
    }

    t->s = s;
    printf( "Partial integrating: [%f,%f] = %f\n", t->from, t->to, t->s);
    while(1);
    return 0;
}


int main(int argc, char **argv)
{
    pthread_t t;
    void *retval;
    int i;
    double from, to, delta;
    struct Task *tasks;

    sscanf(argv[1], "%lf", &from);
    sscanf(argv[2], "%lf", &to);

    int numCPU = 2*sysconf(_SC_NPROCESSORS_ONLN);
    numCPU = 13;
    delta = (to-from)/numCPU;
    printf( "Number of processors: %d\n", numCPU);
    printf( "Integrating on interval from %f to %f\n", from, to);
    tasks = malloc(sizeof(struct Task)*numCPU);

    for(i=0;i<numCPU;i++)
    {
        tasks[i].from = from + delta*i;
        tasks[i].to = tasks[i].from + delta;
        tasks[i].n = 100;
        pthread_create(&tasks[i].t, 0, my_thread, (void *)(tasks+i));
    }

    double integral = 0;
    for(i=0;i<numCPU;i++)
    {
        pthread_join(tasks[i].t, &retval);
        integral += tasks[i].s;
    }

    printf( "Integral: %f\n", integral);

    return 0;
}
