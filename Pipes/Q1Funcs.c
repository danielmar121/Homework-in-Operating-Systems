/*
 * Q1.c
 *
 *  Created on: 7 May 2019
 *      Author: danielmar121
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "Q1Funcs.h"

//open the kid program
void openKidProgram(int kidNum, int pipeIDRead, int pipeToclose1, int pipeIDWrite, int pipeToclose2){
	int kid;
	char* myFile[3];
	char num[INT_SIZE];
	//putting the name of the child's program in the strings array
	myFile[0] = strdup("pipeChild");
	myFile[2] = NULL;
	//open a new child
	kid = fork();
	if(kid == 0){
		close(pipeToclose1);
		close(pipeToclose2);
		snprintf(num, INT_SIZE, "%d", kidNum);
		//the number of the child for the pipeChild code to know which check of the 3 to do
		myFile[1] = strdup(num);
		//changing the pipe to the STDs to easy reading and writing in the child's program
		dup2(pipeIDRead, STDOUT_FILENO);
		dup2(pipeIDWrite, STDIN_FILENO);
		kid = execv(myFile[0],myFile);
		printf("ERROR OPEN KID NUM %d", kidNum);
	}
}

void sendMatToChild(int mat[9][9], int pipeWrite1, int pipeWrite2, int pipeWrite3){
	int i, j;
	char* inBuff;
	inBuff = malloc(sizeof(char));
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			//turn the integer to char
			sprintf(inBuff, "%d", mat[i][j]);
			//write one number of the sudoku to the children
			write(pipeWrite1, inBuff, CHAR_SIZE);
			write(pipeWrite2, inBuff, CHAR_SIZE);
			write(pipeWrite3, inBuff, CHAR_SIZE);
			free(inBuff);
			inBuff = malloc(sizeof(char));
		}
	}
	free(inBuff);
}

int readAnsFromChild(int pipeRead) {
	int i, legal = 0;
	char* inBuff;
	inBuff = malloc(sizeof(char));
	for (i = 0; i < CHILDS; i++) {
		//reading the answer from one of the children
		read(pipeRead, inBuff, CHAR_SIZE);
		//changing the number to integer and checking the answer, 1 is true
		if (atoi(inBuff) == 1) {
			legal++;
		}
		free(inBuff);
		inBuff = malloc(sizeof(char));
	}
	free(inBuff);
	return legal;
}

void closeChilds(int pipeWrite1, int pipeWrite2, int pipeWrite3){
	//send "-" for a signal to the child that there is no more matrixes
		write(pipeWrite1, "-", CHAR_SIZE);
		write(pipeWrite2, "-", CHAR_SIZE);
		write(pipeWrite3, "-", CHAR_SIZE);
}

void readFileToMat(FILE* fptr,int mat[9][9]){
	int i, j;
	//check if the file open properly
	if (fptr == NULL) {
		printf("Error! wrong file name\n");
		exit(0);
	}
	//writing the integer into the matrix
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			fscanf(fptr, "%d", &mat[i][j]);
		}
	}
}
