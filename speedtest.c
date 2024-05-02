#include"miscutils.h"
#include<time.h>

void main(){
	srand(time(NULL));
	int N = 10;
	int ncols = 8;
	int nrows = 8;
	int i;
	matrix *M;
	node *list;	
	for (i=0; i<N; i++){
		M = random_matrix(ncols, nrows);
		//printf("\n");
		//printM(M);
		//printf("\n");
		free_matrix(M);
	}
		
}
