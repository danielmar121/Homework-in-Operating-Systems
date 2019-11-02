#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Funcs2.h"

int main(int argc, char **argv) {
	FILE *fptr;
	int i, j;
	pthread_t tid[N];

	//Question 2
	openLocks();
	legal = 1;
	done = 0;

	//check if they are files to ready
	if (argc > 1) {
		fptr = fopen(argv[1], "r");
		//read the matrix from the file
		readFileToMat(fptr);
		fclose(fptr);
	} else {
		//getting the matrix from the user
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				scanf("%d", &comm.mat[i][j]);
			}
		}
	}
	//open all the threads
	for (i = 0; i < N; i++) {
		pthread_create(&tid[i], 0, threadHandler, NULL);
	}

	pthread_mutex_lock(&condMutex);
	pthread_cond_wait(&myConVar, &condMutex);
	pthread_mutex_unlock(&condMutex);

	//	check if the matrix legal or not
	if (legal == 1) {
		printf("solution is legal\n");
	} else {
		pthread_mutex_lock(&structLock);
		comm.jobNum = 27;
		pthread_mutex_unlock(&structLock);
		printf("solution is not legal\n");
	}

	for (i = 0; i < N; i++) {
		pthread_join(tid[i], NULL);
	}
	destroyLocks();
	return EXIT_SUCCESS;
}
