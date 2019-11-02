#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "childFuncs.h"

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

//function to read the matrix from the pipe of the father
int readMat(int mat[9][9]) {
	int i, j;
	char* inBuff;
	inBuff = malloc(sizeof(char));
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			//reading chars from the father
			read(STDOUT_FILENO, inBuff, CHAR_SIZE);
			//"-" send from the father to know when there is no more matrixes
			if (strcmp(inBuff, "-") == 0) {
				free(inBuff);
				return 0;
			}else{
				//atoi changing char to an integer
				mat[i][j] = atoi(inBuff);
				free(inBuff);
				inBuff = malloc(sizeof(char));
			}
		}
	}
	free(inBuff);
	return 1;
}
