
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "remplirMtrix.h"




/* méthode pour la rempléssage aléatoire d'une matrice  */
  void generateRandomMatrix (int **matrix, int dim, int lowerValue, int upperValue) {
	srand(time(0));
	int i, j;
	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			matrix[i][j] = (rand() % (upperValue - lowerValue + 1)) + lowerValue;
		}
	}

}
