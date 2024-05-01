#include"miscutils.h"
#include<time.h>

void main(){
	srand(time(NULL));
	int N = 3;
	int ncols = 4;
	int nrows = 4;
	int i;
	matrix *M;
	node *list;	
	for (i=0; i<N; i++){
		M = random_matrix(ncols, nrows);
		printf("\n");
		printM(M);
		printf("\n");
		list = computeEROs(M);
		printf("Row Reduced:\n");	
		M = rowReduce(M, list);
		printM(M);
	}
		
}
