#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "Funcs.h"

int main(int argc, char **argv) {
	FILE *fptr;
	int i, j, legal = 0;

	//Question 1
	//Initialize the answer array to false
	for (i = 0; i < NUM_OF_THREADS; i++) {
		comm.answer[i] = 0;
	}
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
	//open and join all the 27 threads
	openThreads();
	//sum all the answer array. if the sum is 27 the matrix is legal
	for (i = 0; i < NUM_OF_THREADS; ++i) {
		legal += comm.answer[i];
	}

	//check if the matrix legal or not
	if (legal == NUM_OF_THREADS) {
		printf("solution is legal\n");
	} else {
		printf("solution is not legal\n");
	}

	return EXIT_SUCCESS;
}
