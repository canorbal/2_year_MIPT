#include <limits.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define QUEUE_LEN 65536

pthread_mutex_t queue_guard = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t doc_ready = PTHREAD_COND_INITIALIZER;
pthread_cond_t free_space = PTHREAD_COND_INITIALIZER;

int NC, ND, TD, NS, TS, L, queue_size = 0;
int queue[QUEUE_LEN];

void usage()
{
    printf(
        "\n\n##############################################################\n"
        "\tOFFICE.\n"
        "OFFICE is a model of clerks and scanners work in office.\n\n"
        "##############################################################\n"
        "\tDescription.\n"
        "office NC ND TD NS TS L\n"
        "NC is number of clerks\n"
        "ND is number of documents\n"
        "TD is time for one document\n"
        "NS is number of scanners\n"
        "TS is time for one document to scan\n"
        "All time should be in seconds. All numbers should be positive\n"
        "#############################################################\n");
}


int take_doc()
{
    pthread_mutex_lock(&queue_guard);
    while (queue_size == 0)
    {
        pthread_cond_wait(&doc_ready, &queue_guard);
    }
    int ret = queue[0];
    queue_size--;
    memmove(queue, queue+1, sizeof(int)*queue_size);

    pthread_cond_broadcast(&free_space);
    pthread_mutex_unlock(&queue_guard);
    return ret;
}

void put_doc(int num)
{
    pthread_mutex_lock(&queue_guard);
    while (queue_size == L)
    {
        pthread_cond_wait(&free_space, &queue_guard);
    }

    queue[queue_size] = num;
    queue_size++;
    pthread_cond_broadcast(&doc_ready);
    pthread_mutex_unlock(&queue_guard);
}

void * take_document_from_clerk(int arg)
{
    int doc = (arg+1)*256;
    int documents_for_print = ND;
    while (documents_for_print != 0)
    {
        doc++;
        sleep(TD);
        printf("Document %#.4x ready\n", doc);
        put_doc(doc);
        documents_for_print--;
    }
}

void * for_scan()
{
    int doc;
    while (1)
    {
        doc = take_doc();
        sleep(TS);
        printf("Document %#.4x scanned\n", doc);
    }
}

int check_args(int argc, char** argv, int* NC, int* ND, int* TD, int* NS, int* TS, int* L)
{
    if (argc != 7)
    {
        usage();
        return -1;
    }

    char* endptr;
    *NC = strtol(argv[1], &endptr, 10);
    if (strcmp(endptr, "\0") != 0)
    {
        fprintf(stderr, "Error in NC\n");
        usage();
        return -1;
    }
    *ND = strtol(argv[2], &endptr, 10);
    if (strcmp(endptr, "\0") != 0)
    {
        fprintf(stderr, "Error in ND\n");
        usage();
        return -1;
    }

    *TD = strtol(argv[3], &endptr, 10);
    if (strcmp(endptr, "\0") != 0)
    {
        fprintf(stderr, "Error in TD\n");
        usage();
        return -1;
    }
    *NS = strtol(argv[4], &endptr, 10);
    if (strcmp(endptr, "\0") != 0)
    {
        fprintf(stderr, "Error in NS\n");
        usage();
        return -1;
    }
    *TS = strtol(argv[5], &endptr, 10);
    if (strcmp(endptr, "\0") != 0)
    {
        fprintf(stderr, "Error in TS\n");
        usage();
        return -1;
    }
    *L = strtol(argv[6], &endptr, 10);
    if (strcmp(endptr, "\0") != 0)
    {
        fprintf(stderr, "Error in L\n");
        usage();
        return -1;
    }

    if (*NC < 0 || *ND < 0 || *TD < 0 || *NS < 0 || *TS < 0 || *L < 0)
    {
        fprintf(stderr, "Negative number get as parameter\n");
        usage();
        return -1;
    }

    if (*L > QUEUE_LEN)
    {
        fprintf(stderr, " Too big size of queue. Max size = 65536\n");
        return -1;
    }
    return 0;
}

int main(int argc, char ** argv) {

    int right_input = check_args(argc, argv, &NC, &ND, &TD, &NS, &TS, &L);
    if (right_input == -1)
    {
        exit(EXIT_FAILURE);
    }

    pthread_t* clerks;
    clerks = malloc(NC * sizeof(pthread_t));
    if (clerks == NULL)
    {
        fprintf(stderr, "Can't allocate memory\n");
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    int i;
    for (i=0; i<NC; i++)
    {
        clerks[i] = 0;
    }

    pthread_t* scanners;
    scanners = malloc(NS * sizeof(pthread_t));
    if (scanners == NULL)
    {
        fprintf(stderr, "Can't allocare memory\n");
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (i=0; i<NS; i++)
    {
        scanners[i] = 0;
    }


    for (i = 0; i < NC; i++)
    {
        if (pthread_create( &clerks[i], 0, take_document_from_clerk, i)  != 0)
        {
            fprintf(stderr, "Error with starting new thread for clerk. %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < NS; i++)
    {
        if (pthread_create( &scanners[i], 0, for_scan, 0) != 0)
        {
            fprintf(stderr, "Error with starting new thread for skanner. %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < NC; i++)
    {
        if (pthread_join( clerks[i], 0) != 0)
        {
            fprintf(stderr, "Error with waiting for thread. %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    free(clerks);
    free(scanners);
    exit(EXIT_SUCCESS);
}
