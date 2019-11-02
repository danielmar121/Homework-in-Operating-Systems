all: v1 v2

v1: Threads1.o Funcs.o
	gcc Threads1.c Funcs.c -o v1 -lm -lpthread

Threads1.o: Threads1.c
	gcc -c Threads1.c

Funcs.o: Funcs.c
	gcc -c Funcs.c

v2: Threads2.o Funcs2.o
	gcc Threads2.c Funcs2.c -o v2 -lm -lpthread

Threads2.o: Threads2.c
	gcc -c Threads2.c

Funcs2.o: Funcs2.c
	gcc -c Funcs2.c

clear: 
	rm *.o v1 v2

run:
	./v1 demo.txt
	./v1 demo2.txt
	./v1 demo3.txt
	./v1 demo4.txt
	./v1 demo5.txt
	./v1 wrong1
	./v1 wrong2
	./v1 wrong3
	./v1 wrong4.txt
	./v1 wrong5.txt
	./v2 demo.txt
	./v2 demo2.txt
	./v2 demo3.txt
	./v2 demo4.txt
	./v2 demo5.txt
	./v2 wrong1
	./v2 wrong2
	./v2 wrong3
	./v2 wrong4.txt
	./v2 wrong5.txt
