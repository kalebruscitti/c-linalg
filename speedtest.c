#include"miscutils.h"
#include<time.h>

void main(){
	srand(time(NULL));
	int N = 1;
	int ncols = 3;
	int nrows = 3;
	int i;
	matrix *M;
	node *list;	
	for (i=0; i<N; i++){
		M = random_matrix(ncols, nrows);
		printf("\n");
		printM(M);
		printf("\n");
		list = computeEROs(M);
		double det  = determinant(M);
		printf("det M = %f\n", det);
	}
		
}
