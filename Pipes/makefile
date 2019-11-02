all: v1 v2 pipeChild

v1: Q1.o Q1Funcs.o
	gcc Q1.c Q1Funcs.c -o v1 -lm

Q1.o: Q1.c
	gcc -c Q1.c

Q1Funcs.o: Q1Funcs.c
	gcc -c Q1Funcs.c

v2: Q2.o Q2Funcs.o
	gcc Q2.c Q2Funcs.c -o v2 -lm

Q2.o: Q2.c
	gcc -c Q2.c

Q2Funcs.o: Q2Funcs.c
	gcc -c Q2Funcs.c

pipeChild: pipeChild.o childFuncs.o
	gcc pipeChild.c childFuncs.c -o pipeChild -lm

pipeChild.o: pipeChild.c
	gcc -c pipeChild.c

childFuncs.o: childFuncs.c
	gcc -c childFuncs.c

clear: 
	rm *.o v1 v2 pipeChild
