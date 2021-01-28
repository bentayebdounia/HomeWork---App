#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "equal.h"

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