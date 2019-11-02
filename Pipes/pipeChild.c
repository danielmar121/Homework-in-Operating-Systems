#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "childFuncs.h"

int main(int argc, char **argv) {
	int mat[9][9];
	int true;
	//while there is more matrix to read
	while (readMat(mat)){
		if (strcmp(argv[1], "1") == 0) {
			true = rowCheck(mat);
		}
		if (strcmp(argv[1], "2") == 0) {
			true = colCheck(mat);
		}
		if (strcmp(argv[1], "3") == 0) {
			true = matCheck(mat);
		}
		//writing to father if the answer is legal or not
		if (true == 1) {
			write(STDIN_FILENO, "1", CHAR_SIZE);
		} else {
			write(STDIN_FILENO, "0", CHAR_SIZE);
		}
	}
//	Close the pipes
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	return EXIT_SUCCESS;
}
