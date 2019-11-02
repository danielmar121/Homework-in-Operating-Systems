#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "Q1Funcs.h"

#define PIPE_SIZE 2

int main(int argc, char **argv) {
	FILE *fptr;
	int mat[9][9];
	int i, j, fileNum = 0;
	int pipeWrite1[PIPE_SIZE], pipeWrite2[PIPE_SIZE], pipeWrite3[PIPE_SIZE],
			pipeRead[PIPE_SIZE]; //for Q1

	//Question 1: pipe question
	//open children and pipes
	pipe(pipeRead);
	pipe(pipeWrite1);
	openKidProgram(1, pipeWrite1[0], pipeWrite1[1], pipeRead[1], pipeRead[0]);
	pipe(pipeWrite2);
	openKidProgram(2, pipeWrite2[0], pipeWrite1[1], pipeRead[1], pipeRead[0]);
	pipe(pipeWrite3);
	openKidProgram(3, pipeWrite3[0], pipeWrite1[1], pipeRead[1], pipeRead[0]);
	close(pipeWrite1[0]);
	close(pipeWrite2[0]);
	close(pipeWrite3[0]);
	close(pipeRead[1]);

	if (argc > 1) {
		//if there are files to read, the father send them to the children
		for (fileNum = 1; fileNum < argc; fileNum++) {
			fptr = fopen(argv[fileNum], "r");
			readFileToMat(fptr, mat);
			sendMatToChild(mat, pipeWrite1[1], pipeWrite2[1], pipeWrite3[1]);
			if (readAnsFromChild(pipeRead[0]) == 3) {
				printf("%s is legal\n", argv[fileNum]);
			} else {
				printf("%s is not legal\n", argv[fileNum]);
			}
			fclose(fptr);
		}
		closeChilds(pipeWrite1[1], pipeWrite2[1], pipeWrite3[1]);
	} else {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				scanf("%d", &mat[i][j]);
			}
		}
		sendMatToChild(mat, pipeWrite1[1], pipeWrite2[1], pipeWrite3[1]);
		if (readAnsFromChild(pipeRead[0]) == 3) {
			printf("the matrix is legal\n");
		} else {
			printf("the matrix is not legal\n");
		}
	}
	close(pipeWrite1[1]);
	close(pipeWrite2[1]);
	close(pipeWrite3[1]);
	close(pipeRead[0]);

	return EXIT_SUCCESS;
}
