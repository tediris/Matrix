HDRS = matrix.h linsolver.h
LIBS = linsolver.o
CC = g++

linsolver.o:
	$(CC) -c linsolver.cc -o linsolver.o

matrix_test: linsolver.o
	$(CC) $(HDRS) linsolver.o mat_test.cc -o matrix_test

clean:
	rm -f *.o *.exe

default: matrix_test
