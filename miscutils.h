#include<stdlib.h>
#include"gausselim.h"

vector *random_vector(unsigned int dim){
	struct vector *v = calloc(1, sizeof(*v));
	v->dim = dim;
	v->vals = calloc(dim, sizeof(double));
	int i;
	for (i=0; i<dim; i++){
		v->vals[i] = rand()%10;
	}
	return v;
}


matrix *random_matrix(unsigned int ncols, unsigned int nrows){
	/* random matrix with 1-digit integer entries */
	/* yes the randomness is not uniform. */
	matrix *M = calloc(1, sizeof(*M));
	M->ncols = ncols;
	M->nrows = nrows;
	M->cols = calloc(ncols, sizeof(struct vector));
	int i;
	vector* v;
	for (i=0; i<ncols; i++){
		v = random_vector(nrows);
		M->cols[i] = v;
		free_vector(v);
	}
	return M;
}


