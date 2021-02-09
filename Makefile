all: hw1
hw1: remplirMtrix.o sequentielle.o functions.o printMatrix.o parallele_v1.o parallele_v2.o parallele_v3.o HW1.o
	gcc  HW1.o functions.o printMatrix.o remplirMtrix.o sequentielle.o parallele_v1.o parallele_v2.o parallele_v3.o -lpthread -lm -o hw1


remplirMtrix.o: remplirMtrix.c remplirMtrix.h
	gcc -c remplirMtrix.h remplirMtrix.c

sequentielle.o: sequentielle.c sequentielle.h
	gcc -c sequentielle.h sequentielle.c

functions.o: functions.c functions.h
	gcc -c functions.h functions.c

printMatrix.o: printMatrix.c printMatrix.h
	gcc -c printMatrix.h printMatrix.c
parallele_v1.o: parallele_v1.c parallele_v1.h
	gcc -c parallele_v1.h parallele_v1.c
parallele_v2.o: parallele_v2.c parallele_v2.h
	gcc -c parallele_v2.h parallele_v2.c
parallele_v3.o: parallele_v3.c parallele_v3.h
	gcc -c parallele_v3.h parallele_v3.c

HW1.o:   remplirMtrix.h  sequentielle.h  functions.h  printMatrix.h parallele_v1.h parallele_v2.h HW1.c
	gcc -c remplirMtrix.h remplirMtrix.c parallele_v1.h parallele_v1.c parallele_v2.h parallele_v2.c parallele_v3.h parallele_v3.c sequentielle.h sequentielle.c functions.h functions.c printMatrix.h printMatrix.c HW1.c

clean:
	rm -fr hw1 *.o
