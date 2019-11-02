/*
 * Q2Funcs.h
 *
 *  Created on: 12 May 2019
 *      Author: daniel
 */

#ifndef Q2FUNCS_H_
#define Q2FUNCS_H_

#define SIZE 9
#define CHILDS 3


struct Shared{
	int solution[9][9];
	int status[3];
};

enum State {MAT_NOT_READY = 0, TRUE = 1, FALSE = 2, MAT_READY = 3,NO_MORE_MAT = 4};

int rowCheck(int mat[9][9]);
int colCheck(int mat[9][9]);
int matCheck(int mat[9][9]);
void childCheck(int mat[9][9], int status[3], int childNum, int (*checker)(int mat[9][9]));
int checkIfLegal(int status[3]);
void readFileToMat(FILE* fptr,int mat[9][9]);


#endif /* Q2FUNCS_H_ */
