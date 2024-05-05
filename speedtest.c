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
	double det;
	for (i=0; i<N; i++){
		M = random_matrix(ncols, nrows);
		printf("\n");
		printM(M);
		printf("\n");
		list = computeEROs(M); 
		printf("\n");
		free_list(list);
		free_matrix(M);
	}
		
}
