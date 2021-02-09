/*  BENTAYEB Dounia */
/*   BOUZAR Louiza  */

#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "remplirMtrix.h"
#include "sequentielle.h"
#include "functions.h"
#include "printMatrix.h"
#include "parallele_v1.h"
#include "parallele_v2.h"
#include "parallele_v3.h"


	int   **A	, **B 	, 	**C 	, **D  ,  n  , p    ;
	double debut1 , debut2 , fin1 , fin2 ; 

	
  int main()  {

  	int i , j   ,k  ; 
	
	double debut , fin ;
		
	char choix [1], v[2] ; 

	
	printf("Matrix size = \n");    			 // la taille de matrice 
	scanf( "%d", &n );


	printf ( " choisi la méthode de calcule s or p " );
    scanf( "%s" , choix ); 									// entrer  le choix de calcul

		/* la creation des matrice  */

	A = (int **)malloc(n * sizeof(int *));

	for (i = 0; i < n; i++)
		A[i] = (int *)malloc(n * sizeof(int));

	B = (int **)malloc(n * sizeof(int *));

	for (i = 0; i < n; i++)
		B[i] = (int *)malloc(n * sizeof(int));

	C = (int **)malloc(n * sizeof(int *));

	for (i = 0; i < n; i++)
		C[i] = (int *)malloc(n * sizeof(int));

	D = (int **)malloc(n * sizeof(int *));

	for (i = 0; i < n; i++)
		D[i] = (int *)malloc(n * sizeof(int));
	
	printf(" ..... matrix A \n");
	
	generateRandomMatrix(A, n, 0, 99);  	//méthode pour remplir A aléatoirement
	//printMatrix(A);

	printf(" ..... matrix B \n ");

	generateRandomMatrix(B, n, 0, 99);			//méthode pour remplir B aléatoirement
	//printMatrix(B);

			
	
/*calcule multiplication en parallele */
	
	if ( (!strcmp (choix , "P")) || (!strcmp (choix , "p")) ) { 		//tester le choix du calcule 
		 
		printf( " vous voulez quelle version de calcul parallele : \n v1 , v2 ou v3 \n" );
		scanf ( "%s",v); 		// entrer le choix de version de calcul parallele 

		if ( (!strcmp (v , "V1")) || (!strcmp (v , "v1")) ){  				 //tester le choix de version de calcul en parellele
			printf( "entrer le nombre de threads  : \n" );   	 // le nombre du threads 
			scanf( "%d", &p );
			
			printf("\n \t calcule de matrice C en parallele \n" );
			debut2 = clock ();
			creation_threads(  C , A , B ,  n ,  p );
			fin2 = clock();

			debut1 = clock();
			seqMult ( D , A , B , n );
			fin1 = clock();

			printf("temps parallele = %f\n", (double)(fin2-debut2)/CLOCKS_PER_SEC);  //le calcule de temps parallele
			printf("temps sequentielle  = %f\n", (double)(fin1-debut1)/CLOCKS_PER_SEC);  //le calcule de temps séquentielle
			printf( "speedup = %f \n" , ((double)(fin1-debut1)/CLOCKS_PER_SEC) / ((double)(fin2-debut2)/CLOCKS_PER_SEC) );  	//calcule de speedup
			

			printMatrix(C , n ) ;
			fonctionEqual( D , C , n );
		}

		if ( (!strcmp (v , "V2")) || (!strcmp (v , "v2")) ){  //tester le choix de version de calcul en parellele

			printf( "Entrer le nombre de threads ( le nombre de threads faut etre de la puissance de deux ) : \n" );    // le nombre du threads 
			scanf( "%d", &p );

			while (IsPowerOfTwo ( p ) == false) {     //tester si le nombre des threads est de puissance de 2
				printf( "le nombre de threads faut etre de puissance de deux : \n" );    // le nombre du threads 
				scanf( "%d", &p );
			}

			printf("\n \t calcule de matrice C en parallele \n" );
			debut2 = clock ();
			creation_threads2(  C , A , B ,  n ,  p );  	 //méthode de création des threads et de calcul parallele de version 2
			fin2 = clock ();

			debut1 = clock();
			seqMult ( D , A , B , n );  					// méthode de calcule de multiplication en séquentielle 
			fin1 = clock();

			printf("temps parallele = %f\n", (double)(fin2-debut2)/CLOCKS_PER_SEC);  //le calcule de temps parallele
			printf("temps sequentielle  = %f\n", (double)(fin1-debut1)/CLOCKS_PER_SEC);  //le calcule de temps séquentielle
			printf( "speedup = %f \n" , ((double)(fin1-debut1)/CLOCKS_PER_SEC) / ((double)(fin2-debut2)/CLOCKS_PER_SEC) );	//le calcule de speedup
			
			printMatrix(C , n ) ;       				   //affichage de matrice résultat 
			fonctionEqual( D , C , n );  				  //tester est ce que la matrice resultat est la meme dans les deux façon de calcule 
		}

		if ( (!strcmp (v , "V3")) || (!strcmp (v , "v3")) ){   			//tester le choix de version de calcul en parellele

			printf( " Entrer le nombre de threads ( le nombre de threads faut etre pair)  : \n" );   	 	// le nombre du threads 
			scanf( "%d", &p );

			while (pair ( p ) == false) {
				printf( "le nombre de threads faut etre pair : \n" );   	 // le nombre du threads 
				scanf( "%d", &p );
			}

			printf("\n \t calcule de matrice C en parallele \n" );

			debut2 = clock();
			creation_threads3(  C , A , B ,  n ,  p );
			fin2 = clock ();

			debut1 = clock();
			seqMult ( D , A , B , n ); 			 // méthode de calcule de multiplication en séquentielle 
			fin1 = clock();

			printf("temps parallele = %f\n", (double)(fin2-debut2)/CLOCKS_PER_SEC);  //le calcule de temps parallele
			printf("temps sequentielle  = %f\n", (double)(fin1-debut1)/CLOCKS_PER_SEC);  //le calcule de temps séquentielle
			printf( "speedup = %f \n" , ((double)(fin1-debut1)/CLOCKS_PER_SEC) / ((double)(fin2-debut2)/CLOCKS_PER_SEC) );  	//le calcule de speedup
			
			printMatrix( C , n )  ;				//affichage de matrice résultat 
			fonctionEqual( D , C , n ); 	   //tester est ce que la matrice resultat est la meme dans les deux façon de calcule

		}

 }
      
/*calcule multiplication en séquentielle */

	else  {
			printf("\n \t calcule de matrice C en séquentielle \n" );
			printf( " Entrer le nombre de threads  : \n" );    // le nombre du threads 
			scanf( "%d", &p );

			debut1 = clock();
			seqMult ( D , A , B , n );			 // méthode de calcule de multiplication en séquentielle 
			
			fin1 = clock();
			debut2 = clock();
			
			creation_threads(  C , A , B ,  n ,  p );   //méthode de création des threads et de calcul parallele de version 1
			fin2 = clock();
			
			printf("temps sequentielle = %f\n", (double)(fin1-debut1)/CLOCKS_PER_SEC);  //le calcule de temps séquentielle
			printf("temps parallele = %f\n", (double)(fin2-debut2)/CLOCKS_PER_SEC);  //le calcule de temps parallele
			printf( "speedup = %f \n" , ((double)(fin1-debut1)/CLOCKS_PER_SEC) / ((double)(fin2-debut2)/CLOCKS_PER_SEC) ); 	//le calcule de speedup
			
			printMatrix( D , n )  ;				//affichage de matrice résultat 
			fonctionEqual( D , C , n ); 	   //tester est ce que la matrice resultat est la meme dans les deux façon de calcule
			
      
        }

		
        
        return 0;
 }

