#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "parallele_v1.h"

int** matrix ; int** A ; int** B ; int n , p , rc  ;



void creation_threads( int** matrix1 , int** A1 , int** B1 , int n1 , int p1){

long tid ;
double debut , fin ;

matrix = matrix1;
A = A1;
B = B1;
n = n1;
p = p1;
 
    pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t)*p);   // allouer un espace pour stocker N threads

	

	for(tid = 0 ; tid < p ; tid++ ) { 


	      rc = pthread_create ( &threads[tid] , NULL , fonctionMult , (void *)tid ); 	// creation de thread 
	      
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

	/*	architecture ligne */

	void * fonctionMult ( void *th ) {

		long tid ;
		tid = (long) th ;

		int i, j , k , blockSize , reste , idebut , ifin ;	
    
		
	    blockSize = n/p ;   		 	       //calcule de block 
		reste = n % p ;        				  // calcule de reste de block
		idebut = tid * blockSize ;           // calcule de debut de block
		ifin = idebut + blockSize - 1 + reste ;      // calcule de la fin de block
		
		/*	calcule de multiplication de deux matrices	*/
		for (  i = idebut ;  i <= ifin ; i++ ) {     
			
			for ( j=0 ; j < n ; j++ ) {

				matrix[i][j]=0 ;

				for ( k=0 ; k < n ; k++ ) {
					matrix[i][j]= matrix[i][j] + A[i][k] * B[k][j] ;
					
				}	
			
			}
		}

		pthread_exit(NULL);

	}

   										 /* architecture colomn */
	/* je l'ai pas fait appele parce qu'elle fonction comme l'architecture ligne sauf elle fonction avec les colomns  */
	void * fonctionMult__ ( void *th ) {

		long tid ;
		tid = (long) th ;

		int i, j , k , blockSize , reste , idebut , ifin ;	
    
		
	    blockSize = n/p ;   		 	       //calcule de block 
		reste = n % p ;        				  // calcule de reste de block
		idebut = tid * blockSize ;           // calcule de debut de block
		ifin = idebut + blockSize - 1 + reste ;      // calcule de la fin de block
		
		/*	calcule de multiplication de deux matrices	*/
		for (  i = 0 ;  i < n ; i++ ) {     
			
			for ( j=idebut ; j <= ifin ; j++ ) {

				matrix[i][j]=0 ;

				for ( k=0 ; k < n ; k++ ) {
					matrix[i][j]= matrix[i][j] + A[i][k] * B[k][j] ;
					
				}	
			
			}
		}

		pthread_exit(NULL);

	}
