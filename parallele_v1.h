#ifndef PARALLELE_H_
#define PARALLELE_H_

void creation_threads( int** matrix1 , int** A1 , int** B1 , int n1 , int p1);
void * fonctionMult ( void *th );
void * fonctionMult__ ( void *th );

#endif