C_FLAGS = -Wall -g 

all : test_abr test_abr2

abr.o : abr.c abr.h
	gcc ${C_FLAGS} -c abr.c

test_abr.o : test_abr.c abr.h
	gcc ${C_FLAGS} -c test_abr.c

test_abr : test_abr.o abr.o
	gcc ${C_FLAGS} -o test_abr test_abr.o abr.o

test_abr2.o : test_abr2.c abr.h
	gcc ${C_FLAGS} -c test_abr2.c

test_abr2 : test_abr2.o abr.o
	gcc ${C_FLAGS} -o test_abr2 test_abr2.o abr.o

clean :
	rm -f *.o test_abr test_abr2
