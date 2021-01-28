/*  BENTAYEB Dounia */
/*   BOUZAR Louiza  */

#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "remplirMtrix.h"
#include "sequentielle.h"
#include "equal.h"
#include "printMatrix.h"


	int   **A	, **B 	, 	**C 	, **D  ,  n  , p  ; 

	
	
			
 
		/*la méthode de calcule de multiplication en paralléle*/

	void * fonctionMult ( void *th ) {

		long tid ;
		tid = (long) th ;

		int i, j , k , blockSize , reste , idebut , ifin ;	
    
		
	        blockSize = n/p ;    //calcule de block 
		reste = n % p ;
		idebut = tid * blockSize ;   //debut de block
		ifin = idebut + blockSize - 1 + reste ;   //la fin de block
		
		for (  i = idebut ;  i <= ifin ; i++ ) {     
			
			for ( j=0 ; j < n ; j++ ) {

				C[i][j]=0 ;

				for ( k=0 ; k < n ; k++ ) {
					C[i][j]= C[i][j] + A[i][k] * B[k][j] ;
					//printf ( " thread %lu : %d \n" , tid, C[i][j]); 	

				}	
			
			}
		}

		pthread_exit(NULL);

	}

       

/* une fonction qui tester est ce que le calcule de la matrice c en parallele c'est le meme en sequentielle  */

	

  int main()
 {
  	int i , j  , rc  ,k  ; 
	long tid ;
	double debut , fin ;
		
	char choix [1] ; 

	
	printf("Matrix size = \n");     // la taille de matrice 
	scanf( "%d", &n );

	printf( "le nombre de threads = \n" );    // le nombre du threads 
	scanf( "%d", &p );

	printf ( " choisi la méthode de calcule s or p " );
        scanf( "%s" , choix );

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
	
	generateRandomMatrix(A, n, 0, 99);  //méthode pour remplir A aléatoirement
	//printMatrix(A);

	printf(" ..... matrix B \n ");

	generateRandomMatrix(B, n, 0, 99);
	//printMatrix(B);

			
	
/*calcule multiplication en parallele */
	
	if ( (!strcmp (choix , "P")) || (!strcmp (choix , "p")) ) { 
	printf("\n \t calcule de matrice C en parallele \n" );
	pthread_t threads[p];

	debut = clock();

	for(tid = 0 ; tid < p ; tid++ ) { 


	      rc = pthread_create ( &threads[tid] , NULL , fonctionMult , (void *)tid ); 	// creation de thread 
	      
	      if (rc){ 
                    	printf("Erreur de creation de thread; code erreur = %d\n" , rc); 
	            	exit(-1); 
              } 
	 } 
	 
	 
	 for( tid = 0 ; tid < p ; tid++ ) { 
	      (void)pthread_join( threads[tid] , NULL);    //la joiture du thread
         }

	fin =  clock(); 
 	printMatrix(C , n ) ;

	printf("temps parallele=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC);  //le calcule de temps parallele 
	seqMult ( D , A , B , n );
	fonctionEqual( D , C , n );
 }
      
/*calcule multiplication en séquentielle */

	else  {
			printf("\n \t calcule de matrice C en séquentielle \n" );
	
			seqMult ( D , A , B , n );
      
}

		
        
        return 0;
 }

