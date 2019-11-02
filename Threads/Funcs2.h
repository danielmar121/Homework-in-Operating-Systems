/*
 * Funcs.h
 *
 *  Created on: 16 May 2019
 *      Author: daniel
 */

#ifndef FUNCS2_H_
#define FUNCS2_H_


#define SIZE 9
#define N 4

//#define NUM_OF_THREADS 27

struct Communication {
	int mat[SIZE][SIZE];
	int jobNum;
};

int legal;
int done;
struct Communication comm;
pthread_mutex_t structLock;
pthread_mutex_t doneLock;
pthread_mutex_t condMutex;
pthread_cond_t myConVar;

void readFileToMat(FILE* fptr);
void rowCheck(int numOfRow);
void colCheck(int numOfCol);
void subMatCheck(int matNum);
void* threadHandler();
void openLocks();
void getRowAndCol(int* theRow, int* theCol, int matNum);
void destroyLocks();

#endif /* FUNCS2_H_ */
