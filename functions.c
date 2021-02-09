#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "functions.h"

/* fonction qui compare entre le calcule en séquentielle et en parallele de la matric C */
void fonctionEqual(int **N , int **R , int n ){

		int i , j  ;
		bool a = true ;
  		 for ( i= 0  ; i<n ; i++) { 

			for ( j = 0 ; j<n ; j++ ) {
				
				if ( N[i][j] != R[i][j] ) {
						a=false;
						break;
							}
				
			}
}
		if ( a == true ) printf ( "is equal \n" );
		else printf ( "is not equal \n" );
		
}

  /*  fonction qui teste que le nombre de threads est de la puissance de deux   */

bool IsPowerOfTwo ( int n ){

	 int intV;
     float floatV;

     floatV = sqrt((double) n );
     intV = floatV ;

        if ( intV == floatV ) return true ;
        else  return false ;

 }

     /*   fonction qui teste que le nombre de threads est pair */
 bool pair ( int p ){
	 
	  if ( p % 2 == 0 ) return true ;
	  else return false ;

 }
