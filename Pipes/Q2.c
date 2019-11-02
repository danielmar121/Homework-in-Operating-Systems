/*
 ============================================================================
 Name        : testExec.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "Q2Funcs.h"

int main(int argc, char **argv) {
	FILE *fptr;
	int i, j, fileNum = 0;
	struct Shared *ptr; //for Q2

//Question 2: mmap question
	ptr = mmap(NULL, sizeof(struct Shared), PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	//initialize the status
	for (i = 0; i < 3; i++) {
		ptr->status[i] = MAT_NOT_READY;
	}
	if (fork() == 0) {
		//child number 1
		childCheck(ptr->solution, ptr->status, 0, rowCheck);
	} else if (fork() == 0) {
		//child number 2
		childCheck(ptr->solution, ptr->status, 1, colCheck);
	} else if (fork() == 0) {
		//child number 3
		childCheck(ptr->solution, ptr->status, 2, matCheck);
	} else {
		//father code
		if (argc > 1) {
			for (fileNum = 1; fileNum < argc; fileNum++) {
				fptr = fopen(argv[fileNum], "r");
				readFileToMat(fptr, ptr->solution);
				if (checkIfLegal(ptr->status)) {
					printf("%s is legal\n", argv[fileNum]);
				} else {
					printf("%s is not legal\n", argv[fileNum]);
				}
				fclose(fptr);
			}
		} else {
			for (i = 0; i < SIZE; i++) {
				for (j = 0; j < SIZE; j++) {
					scanf("%d", &ptr->solution[i][j]);
				}
			}
			if (checkIfLegal(ptr->status)) {
				printf("the matrix is legal\n");
			} else {
				printf("the matrix is not legal\n");
			}
		}
		//telling the kids that is no more matrix to check
		for (i = 0; i < CHILDS; i++) {
			ptr->status[i] = NO_MORE_MAT;
		}

	}
	return EXIT_SUCCESS;
}
