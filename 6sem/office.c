#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define QUEUE_LEN 67000
#define NC_MAX 16
#define ND_MAX 16
#define TD_MAX 1000
#define NS_MAX 1000
#define TS_MAX 1000
#define L_MAX 10000

pthread_mutex_t queue_guard = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t doc_ready = PTHREAD_COND_INITIALIZER;
pthread_cond_t space_available = PTHREAD_COND_INITIALIZER;

int NC, ND, TD, NS, TS, L, qsize = 0;
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


int get() {
	pthread_mutex_lock(&queue_guard);
	while (qsize == 0) {
		pthread_cond_wait(&doc_ready, &queue_guard);
	}
	int ret = queue[0];
	qsize--;
	memmove(queue, queue+1, sizeof(int)*qsize);
	
	pthread_cond_broadcast(&space_available);
	pthread_mutex_unlock(&queue_guard);
	return ret;
}

void put(int num)  {
	pthread_mutex_lock(&queue_guard);
	while (qsize == L) {
		pthread_cond_wait(&space_available, &queue_guard);
	}

	queue[qsize] = num ;
	qsize++;
	pthread_cond_broadcast(&doc_ready);
	pthread_mutex_unlock(&queue_guard);
}

void * from_clerk(int arg) {
	int n = (arg+1)*16*16;
	int need_to_pr = ND;
	while (need_to_pr != 0) {
		n++;
		sleep(TD);
		printf("Document %#.4x ready\n", n);
		put(n);
		need_to_pr--;
	}
}

void * for_skan() {
	int n;
	while (1) {
		n = get();
		sleep(TS);
		printf("Document %#.4x scanned\n", n); 
	}
}
/*
int check_values (int nc, int nd, int td, int ns, int ts, int l) {
	
	if (nc > NC_MAX) {
		fprintf(stderr, "Too big value of 1st parameter\n");
		return 1;
	}
	if (nd > ND_MAX) {
		fprintf(stderr, "Too big value of 2nd parameter\n");
		return 1;
	}
	if (td > TD_MAX) {
		fprintf(stderr, "Too big value of 3rd parameter\n");
		return 1;
	}
	if (ns > NS_MAX) {
		fprintf(stderr, "Too big value of 4th parameter\n");
		return 1;
	}
	if (ts > TS_MAX) {
		fprintf(stderr, "Too big value of 5th parameter\n");
		return 1;
	}
	if (l > L_MAX) {
		fprintf(stderr, "Too big value of 6th parameter\n");
		return 1;
	}
	return 0;
}*/


int main(int argc, char ** argv) {
	if (argc != 7) {
        usage();
		exit(EXIT_FAILURE);
	}
	
    char* endptr;
	NC = strtol(argv[1], &endptr, 10);
    if (strcmp(endptr, "\0") != 0){
        fprintf(stderr, "Error in NC\n");
        usage();
        exit(EXIT_FAILURE);
    }
	ND = strtol(argv[2], &endptr, 10);
    if (strcmp(endptr, "\0") != 0){
        usage();
        exit(EXIT_FAILURE);
    }
	TD = strtol(argv[3], &endptr, 10);
    if (strcmp(endptr, "\0") != 0){
        usage();
        exit(EXIT_FAILURE);
    }
	NS = strtol(argv[4], &endptr, 10);
     if (strcmp(endptr, "\0") != 0){
        usage();
        exit(EXIT_FAILURE);
    }
	TS = strtol(argv[5], &endptr, 10);
     if (strcmp(endptr, "\0") != 0){
        usage();
        exit(EXIT_FAILURE);
    }
	L = strtol(argv[6], &endptr, 10);
	 if (strcmp(endptr, "\0") != 0){
        usage();
        exit(EXIT_FAILURE);
    }

    if (NC < 0 || ND < 0 || TD < 0 || NS < 0 || TS < 0 || L < 0) {
	    fprintf(stderr, "Negative number get as parameter\n");
        usage();
        exit(EXIT_FAILURE);
		return 1;
	}	
	
	pthread_t clerk[NC_MAX] = {0};
	pthread_t skanner[NS_MAX] = {0};
	
	int i, n;
	for (i = 0; i < NC; i++) {
		if (pthread_create( &clerk[i], 0, from_clerk, i)  != 0) {
			fprintf(stderr, "Error with starting new thread for clerk. %s\n", strerror(errno));
			return 1;
		}
	}
	for (i = 0; i < NS; i++) {
		if (pthread_create( &skanner[i], 0, for_skan, 0) != 0) {
			fprintf(stderr, "Error with starting new thread for skanner. %s\n", strerror(errno));
			return 1;
		}
	}
	for (i = 0; i < NC; i++) {
		if (pthread_join( clerk[i], 0) != 0) {
			fprintf(stderr, "Error with waiting for thread. %s\n", strerror(errno));
			return 1;
		}
	}
	return 0;
}


