#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "parallele_v3.h"

int** matrix ; int** A ; int** B ; int n , p , rc  ;



void creation_threads3( int** matrix1 , int** A1 , int** B1 , int n1 , int p1){

long tid ;
double debut , fin ;

matrix = matrix1;
A = A1;
B = B1;
n = n1;
p = p1;

    pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t)*p);		// allouer un espace pour stocker N threads

	for(tid = 0 ; tid < p ; tid++ ) { 

	      rc = pthread_create ( &threads[tid] , NULL , fonctionMult3 , (void *)tid ); 	// creation de thread 
	      
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


	void * fonctionMult3 ( void *th ) {
		long tid ;
		tid = (long) th  ;

		int i, j , k , blockSizeL , blockSizeC , resteL , resteC , idebut , ifin , jdebut , jfin ;	
    
		blockSizeL =   n / 2  ;           // calcule de ligne de block
	    blockSizeC =   n / ( p/2 ) ;     // calcule de colomn de  block 
		
		resteL = n % 2 ;                     // calcule de reste des ligne de block 
        resteC = n %  ( p / 2 ) ;			// calcule de reste des colomn de block 
        
		
		/*   le calcul le debut de ligne de block et le debut de colomn de block  */
		if( ( tid / ( p / 2 ) ) < 1 ) {
				idebut = 0;    
                jdebut = tid * blockSizeC ;   
                
              
        }
		else {
				idebut = n / 2 ;
                jdebut =  ( tid - ( p / 2 ) ) * blockSizeC ; // calcule de debut de colomn de block 
                
                
            }
            ifin = idebut + blockSizeL - 1 + resteL ;		// calcule de fin de ligne  de block 
            jfin = jdebut + blockSizeC - 1 + resteC ;		// calcule de fin de colomn de block 
        
        
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
