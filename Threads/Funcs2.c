/*
 * Funcs.c
 *
 *  Created on: 14 May 2019
 *      Author: daniel
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Funcs2.h"

void readFileToMat(FILE* fptr) {
	int i, j;
	//check if the file open properly
	if (fptr == NULL) {
		printf("Error! wrong file name\n");
		exit(0);
	}
	//writing the integer into the matrix
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			fscanf(fptr, "%d", &comm.mat[i][j]);
		}
	}
}

void* threadHandler() {
	int job;
	int jobToCheck;
	//while there is more jobs to do
	while (comm.jobNum < 27) {
		//lock the struct and take a new job
		pthread_mutex_lock(&structLock);
		job = comm.jobNum;
		jobToCheck = job % 9;
		comm.jobNum++;
		pthread_mutex_unlock(&structLock);
		//choose the right job to do by the job number
		if (job < 9) {
			rowCheck(jobToCheck);
		} else if (job < 18) {
			colCheck(jobToCheck);
		} else {
			subMatCheck(jobToCheck);
		}
		//for ending the checking by the father
		if (legal == 0) {
			pthread_cond_signal(&myConVar);
		}
	}
	pthread_mutex_lock(&doneLock);
	done++;
	//for ending the checking by the father
	if (done == N) {
		pthread_cond_signal(&myConVar);
	}
	pthread_mutex_unlock(&doneLock);
	return NULL;
}

void rowCheck(int numOfRow) {
	int i, j;
	int counter = 0;

	//rows
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (comm.mat[numOfRow][j] == i + 1) {
				counter++;
				if (counter > i + 1) {
					legal = 0;
					return;
				}
			}
		}
		if (counter != i + 1) {
			legal = 0;
			return;
		}
	}
}

void colCheck(int numOfCol) {
	int i, j;
	int counter = 0;

	//columns
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (comm.mat[j][numOfCol] == i + 1) {
				counter++;
				if (counter > i + 1) {
					legal = 0;
					return;
				}
			}
		}
		if (counter != i + 1) {
			legal = 0;
			return;
		}
	}
}

void subMatCheck(int matNum) {
	int i, j, k;
	int counter = 0, row = 0, col = 0;
	//get the indexes f the right sub matrix
	getRowAndCol(&row, &col, matNum);

	//matrix
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE / 3; j++) {
			for (k = 0; k < SIZE / 3; k++) {
				if (comm.mat[row + j][col + k] == i + 1) {
					counter++;
					if (counter > i + 1) {
						legal = 0;
						return;
					}
				}
			}
		}
		if (counter != i + 1) {
			legal = 0;
			return;
		}
	}
}

void getRowAndCol(int* theRow, int* theCol, int matNum) {
	int row, col;
	switch (matNum) {
	case 0:
		row = 0;
		col = 0;
		break;
	case 1:
		row = 0;
		col = 3;
		break;
	case 2:
		row = 0;
		col = 6;
		break;
	case 3:
		row = 3;
		col = 0;
		break;
	case 4:
		row = 3;
		col = 3;
		break;
	case 5:
		row = 3;
		col = 6;
		break;
	case 6:
		row = 6;
		col = 0;
		break;
	case 7:
		row = 6;
		col = 3;
		break;

	case 8:
		row = 6;
		col = 6;
		break;
	default:
		break;
	}
	*theRow = row;
	*theCol = col;
}

void openLocks() {
	if (pthread_mutex_init(&structLock, NULL) != 0) {
		printf("ERROR - lock open");
		exit(1);
	}
	if (pthread_mutex_init(&doneLock, NULL) != 0) {
		printf("ERROR - lock open");
		exit(2);
	}
	if (pthread_mutex_init(&condMutex, NULL) != 0) {
		printf("ERROR - lock open");
		exit(2);
	}
	pthread_cond_init(&myConVar, NULL);
}

void destroyLocks() {
	pthread_mutex_destroy(&structLock);
	pthread_mutex_destroy(&doneLock);
	pthread_mutex_destroy(&condMutex);
	pthread_cond_destroy(&myConVar);
}

