HDRS = matrix.h linsolver.h
LIBS = linsolver.o
CC = g++

linsolver.o:
	CC -c linsolver.cpp -o linsolver.o

matrix_test: linsolver.o
	CC $(HDRS) linsolver.o mat_test.cpp -o matrix_test