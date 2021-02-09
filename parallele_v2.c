#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "parallele_v2.h"

int** matrix ; int** A ; int** B ; int n , p , rc  ;



void creation_threads2( int** matrix1 , int** A1 , int** B1 , int n1 , int p1){

long tid ;
double debut , fin ;

matrix = matrix1;
A = A1;
B = B1;
n = n1;
p = p1;

    pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t)*p);		// allouer un espace pour stocker N threads

	for(tid = 0 ; tid < p ; tid++ ) { 

	      rc = pthread_create ( &threads[tid] , NULL , fonctionMult2 , (void *)tid ); 	// creation de thread 
	      
	      if (rc){ 
                    	printf("Erreur de creation de thread; code erreur = %d\n" , rc); 
	            	exit(-1); 
              } 
	 } 
	 
	 /*  attender la terminaison de tous les threads  */
	 for( tid = 0 ; tid < p ; tid++ ) { 
	      (void)pthread_join( threads[tid] , NULL);    //la joiture du thread
         }

	
}


	void * fonctionMult2 ( void *th ) {

		long tid ;
		tid = (long) th ;

		int i, j , k , blockSize , reste , idebut , ifin , jdebut , jfin , sqrtP , s;	
    
		
	    blockSize = n/sqrt(p)  ;   	 // calcule de block 
		sqrtP = sqrt(p) ;				// le calcul de reste de block
		reste = n % sqrtP ;
		s = tid/sqrt(p) ;
		idebut = s * blockSize ;   // le calcul de debut de ligne de block
		ifin = idebut + blockSize - 1 + reste ;   // le calcul de fin de ligne de block

		/*   le calcul de debut de colomn de block  */
		if( tid < sqrtP )
				jdebut = tid * blockSize ;   	
		else 
				jdebut = ( tid % sqrtP ) * blockSize ;

		/*  le calcul de fin de colomn de block  */
		jfin = jdebut + blockSize - 1 + reste ;
		
		/*	calcule de multiplication de deux matrices	*/
		for (  i = idebut ;  i <= ifin ; i++ ) {     
			for ( j = jdebut ; j <= jfin ; j++ ) {

				matrix[i][j]=0 ;

				for ( k=0 ; k < n ; k++ ) {
					matrix[i][j]= matrix[i][j] + A[i][k] * B[k][j] ;
					 	

				}	
			
			}
		}

		pthread_exit(NULL);

	}
