all: hw1
hw1: remplirMtrix.o sequentielle.o equal.o printMatrix.o HW1.o
	gcc HW1.o equal.o printMatrix.o remplirMtrix.o sequentielle.o -lpthread -o hw1


remplirMtrix.o: remplirMtrix.c remplirMtrix.h
	gcc -c remplirMtrix.h remplirMtrix.c

sequentielle.o: sequentielle.c sequentielle.h
	gcc -c sequentielle.h sequentielle.c

equal.o: equal.c equal.h
	gcc -c equal.h equal.c

printMatrix.o: printMatrix.c printMatrix.h
	gcc -c printMatrix.h printMatrix.c

HW1.o:   remplirMtrix.h  sequentielle.h  equal.h  printMatrix.h HW1.c
	gcc -c remplirMtrix.h remplirMtrix.c sequentielle.h sequentielle.c equal.h equal.c printMatrix.h printMatrix.c HW1.c

clean:
	rm -fr hw1 *.o
