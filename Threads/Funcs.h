/*
 * Funcs.h
 *
 *  Created on: 14 May 2019
 *      Author: daniel
 */

#ifndef FUNCS_H_
#define FUNCS_H_

#define SIZE 9
#define NUM_OF_THREADS 27

struct Communication {
	int mat[SIZE][SIZE];
	int answer[NUM_OF_THREADS];
};

struct Communication comm;

void readFileToMat(FILE* fptr);
void* rowCheck(void* threadNum);
void* colCheck(void* threadNum);
void* subMatCheck(void* threadNum);
void openThreads();
void getRowAndCol(int *theRow, int *theCol, int matNum);
#endif /* FUNCS_H_ */
