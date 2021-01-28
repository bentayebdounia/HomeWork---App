#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printMatrix.h"

/* l'affichage de la matrice C avec les deux méthode de calcule ( Parallele et secontielle) */

	void printMatrix(int** matrix , int n ){
	int i, j;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}