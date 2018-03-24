# Mój plik makefile - wpisz 'make all' aby skompilować cały program
# (właściwie wystarczy wpisać 'make' - all jest domyślny jako pierwszy cel)
CPP = g++  

all: main.o SparseVector.o
	$(CPP) SparseVector.o main.o -std=c++11 -o aplikacja

SparseVector.o: SparseVector.cpp  SparseVector.h
	$(CPP) SparseVector.cpp -std=c++11 -c -o SparseVector.o

main.o: main.cpp SparseVector.h
	$(CPP) main.cpp -std=c++11 -c -o main.o

clean:
	rm -f *.o aplikacja
