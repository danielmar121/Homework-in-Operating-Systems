/*
 * Funcs.c
 *
 *  Created on: 14 May 2019
 *      Author: daniel
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Funcs.h"

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

void* rowCheck(void* theardNum) {
	int i, j;
	int counter = 0;
	int *numOfRow = (int*)theardNum;
	int placeInAnswerArr = *numOfRow;

	//check the rows of the sudoku matrix
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (comm.mat[*numOfRow][j] == i + 1) {
				counter++;
				if (counter > i + 1) {
					comm.answer[placeInAnswerArr] = 0;
					return NULL;
				}
			}
		}
		if (counter != i + 1) {
			comm.answer[placeInAnswerArr] = 0;
			return NULL;
		}
	}
	comm.answer[placeInAnswerArr] = 1;
	return NULL;
}

void* colCheck(void* theardNum) {
	int i, j;
	int counter = 0;
	int *numOfCol = (int*)theardNum;
	int placeInAnswerArr = *numOfCol + 9;

	//check the column of the sudoku matrix
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (comm.mat[j][*numOfCol] == i + 1) {
				counter++;
				if (counter > i + 1) {
					comm.answer[placeInAnswerArr] = 0;
					return NULL;
				}
			}
		}
		if (counter != i + 1) {
			comm.answer[placeInAnswerArr] = 0;
			return NULL;
		}
	}
	comm.answer[placeInAnswerArr] = 1;
	return NULL;
}

void* subMatCheck(void* theardNum) {
	int i, j, k;
	int counter = 0, row = 0, col = 0;
	int *matNum = (int*)theardNum;
	int placeInAnswerArr = *matNum + 18;

	//get the indexes of the right sub matrix
	getRowAndCol(&row, &col, *matNum);
	//matrix
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE / 3; j++) {
			for (k = 0; k < SIZE / 3; k++) {
				if (comm.mat[row + j][col + k] == i + 1) {
					counter++;
					if (counter > i + 1) {
						comm.answer[placeInAnswerArr] = 0;
						return NULL;
					}
				}
			}
		}
		if (counter != i + 1) {
			comm.answer[placeInAnswerArr] = 0;
			return NULL;
		}
	}
	comm.answer[placeInAnswerArr] = 1;
	return NULL;
}

void getRowAndCol(int *theRow, int *theCol, int matNum){
	int row, col;
	//choosing the starting point of the sub matrix by matrix number
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

void openThreads(){
	pthread_t tid[27];
	int parameters[] = {0,1,2,3,4,5,6,7,8};
	int i;
	//open all the 27 threads
	for (i = 0; i < SIZE; i++) {
		//open all the rows check threads
		pthread_create(&tid[i], 0, rowCheck, (void*) &parameters[i]);
		//open all the column check threads
		pthread_create(&tid[i+9], 0, colCheck, (void*) &parameters[i]);
		//open all the sub matrix check threads
		pthread_create(&tid[i+18], 0, subMatCheck, (void*) &parameters[i]);
	}
	//do join to all all the 27 threads
	for (i = 0; i < SIZE; i++) {
		//join all the rows check threads
		pthread_join(tid[i], NULL);
		//join all the column check threads
		pthread_join(tid[i+9], NULL);
		//join all the sub matrix check threads
		pthread_join(tid[i+18], NULL);
	}
}


