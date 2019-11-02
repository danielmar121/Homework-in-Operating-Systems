/*
 * MatrixCheck.c
 *
 *  Created on: 7 May 2019
 *      Author: danielmar121
 */

#include <stdio.h>
#include <stdlib.h>
#include "Q2Funcs.h"

int rowCheck(int mat[9][9]) {
	int i, j, k;
	int counter = 0;
	//rows
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			for (k = 0; k < SIZE; k++) {
				if (mat[i][k] == j + 1) {
					counter++;
					if (counter > j + 1) {
						return -1;
					}
				}
			}
			if (counter != j + 1) {
				return -1;
			}
		}
		counter = 0;
	}
	return 1;
}

int colCheck(int mat[9][9]) {
	int i, j, k;
	int counter = 0;
	//columns
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			for (k = 0; k < SIZE; k++) {
				if (mat[k][i] == j + 1) {
					counter++;
					if (counter > j + 1) {
						return -2;
					}
				}
			}
			if (counter != j + 1) {
				return -2;
			}
		}
		counter = 0;
	}
	return 1;
}

int matCheck(int mat[9][9]) {
	int i, j, k, l, m;
	int counter = 0;
	//matrix
	for (i = 0; i < SIZE; i += 3) {
		for (j = 0; j < SIZE; j += 3) {
			for (k = 0; k < SIZE; k++) {
				for (l = 0; l < SIZE / 3; l++) {
					for (m = 0; m < SIZE / 3; m++) {
						if (mat[i + l][j + m] == k + 1) {
							counter++;
							if (counter > k + 1) {
								return 0;
							}
						}
					}
				}
				if (counter != k + 1) {
					return 0;
				}
			}
			counter = 0;
		}
	}
	return 1;
}

void childCheck(int mat[9][9], int status[3], int childNum,
		int (*checker)(int mat[9][9])) {
	while (status[childNum] != NO_MORE_MAT) {
		//Waiting while the father changing the matrix
		if (status[childNum] == MAT_READY) {
			//checking if the matrix is legal or not
			if (checker(mat) == 1) {
				status[childNum] = TRUE;
			} else {
				status[childNum] = FALSE;
			}
		}
	}
}

int checkIfLegal(int status[3]) {
	int i;
	//turn the status to ready for the kids to read the matrix
	for (i = 0; i < CHILDS; i++) {
		status[i] = MAT_READY;
	}
	//for waiting to the kids to done
	while (status[0] == MAT_READY || status[1] == MAT_READY
			|| status[2] == MAT_READY) {
	}
	//checking the kids answers
	return status[0] == TRUE && status[1] == TRUE && status[2] == TRUE;
}

void readFileToMat(FILE* fptr,int mat[9][9]){
	int i, j;
	//check if the file open properly
	if (fptr == NULL) {
		printf("Error! wrong file name");
		exit(0);
	}
	//writing the integer into the matrix
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			fscanf(fptr, "%d", &mat[i][j]);
		}
	}
}
