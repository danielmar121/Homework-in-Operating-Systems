/*
 * Q1Funcs.h
 *
 *  Created on: 12 May 2019
 *      Author: daniel
 */

#ifndef Q1FUNCS_H_
#define Q1FUNCS_H_

#define SIZE 9
#define INT_SIZE 2
#define CHAR_SIZE 1
#define CHILDS 3

void openKidProgram(int kidNum, int pipeIDRead, int pipeToclose1, int pipeIDWrite,
		int pipeToclose2);
void sendMatToChild(int mat[9][9], int pipeWrite1, int pipeWrite2, int pipeWrite3);
int readAnsFromChild(int pipeRead);
void closeChilds(int pipeWrite1, int pipeWrite2, int pipeWrite3);
void readFileToMat(FILE* fptr,int mat[9][9]);

#endif /* Q1FUNCS_H_ */
