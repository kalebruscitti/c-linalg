#include <stdio.h>
#include <stdlib.h>

typedef struct vector{
	unsigned int dim;
	double *vals;
} vector;

// Constructor?
struct vector* new_vector(unsigned int dim){
	if (dim == 0){
		printf("Dimension of a vector cannot be zero!");
		return NULL;
	}
	struct vector *v = calloc(1, sizeof(*v));
	v->dim = dim;
	v->vals = calloc(dim, sizeof(double));
	int i;
	for (i = 0; i < dim; i++){
		v->vals[i] = 0;
	}
	return v;
}

// Free memory function
void free_vector(struct vector *v){
	free(v->vals);
	free(v);
}

void printv(struct vector *v){
	int i;
	printf("[");
	for (i = 0; i < v->dim-1; i++){
		printf("%f,", v->vals[i]);
	}
	// no comma after last entry
	printf("%f", v->vals[i]);
	printf("]");
}

struct vector* v_add(struct vector* x, struct vector* y){
	if (x->dim != y->dim){
		printf("Dimensions must be the same for vector addition!");
		return NULL;
	}
	struct vector* z = new_vector(x->dim);
	int i;
	for (i=0; i < x->dim; i++){
		z->vals[i] = x->vals[i]+y->vals[i];	
	}	
	return z;
}

double v_dot(vector* x, vector* y){
	if (x-> dim != y->dim){
		printf("Dimensions must be the same for vector addition!");
		return 0;	
	}
	int i;
	double sum = 0.;
	for (i=0; i < x->dim; i++){
		sum += x->vals[i]*y->vals[i];	
	}	
	return sum;
}

/*
	Matrices, implemented as arrays of their columns.
*/
typedef struct matrix{
	unsigned int ncols;
	unsigned int nrows;
	vector* *cols;
} matrix;

struct matrix* new_matrix(unsigned int ncols, unsigned int nrows){
	if (ncols == 0 || nrows == 0){
		printf("Dimensions of a matrix must be non-zero!");
		return NULL;
	}
	matrix* M = calloc(1, sizeof(*M));
	M->ncols = ncols;
	M->nrows = nrows;
	M->cols = calloc(ncols, sizeof(struct vector));
	int i;
	vector* zero_vec = new_vector(nrows);
	for (i = 0; i < ncols; i++){
		M->cols[i] = zero_vec;
	}
	return M;
}

void free_matrix(struct matrix* M){
	free(M->cols);
	free(M);
}

struct vector* getrow(matrix* M, int k){
	// return kth row of M
	vector* mk = new_vector(M->ncols);
	int i;
	for (i = 0; i < M->ncols; i++){
		mk->vals[i] = M->cols[i]->vals[k];
	}
	return mk;
}

void printM(matrix* M){
	int i;
	vector* mi;
	for (i = 0; i < M->nrows; i++){
		mi = getrow(M, i);
		printv(mi);
		printf("\n");
	}
}

struct matrix* matmul(matrix* A, matrix* B){
	if (A->ncols != B->nrows){
		printf("A's # of cols must equal B's # of rowss!");
		return NULL;
	}
	matrix* C = new_matrix(A->nrows, B->ncols);
	vector *ci, *aj, *bi;
	int i,j;
	for (i = 0; i < B->ncols; i++){
		ci = new_vector(A->nrows);
		bi = B->cols[i];
		for (j=0; j < A->nrows; j++){
			aj = getrow(A,j);
			ci->vals[j] = v_dot(aj,bi); 
		}
		C->cols[i] = ci;
	}
	return C;
}

void main(){
	struct vector* x = new_vector(2);
	x->vals[0] = 1.;
	x->vals[1] = 2.;
	struct vector* y = new_vector(2);
	y->vals[0] = 3.;
	y->vals[1] = 2.;
	struct vector* z = v_add(x,y);
	printv(z);
	printf("\n");
	double dot = v_dot(x,y);
	printf("%f ", dot);
	printf("\n");

	matrix* A = new_matrix(2, 2);
	A->cols[0] = x;
	A->cols[1] = y;
	matrix* B = new_matrix(2,2);
	B->cols[0] = y;
	B->cols[1] = z;
	matrix* C = matmul(A,B);
	printM(A);
	printM(B);
	printM(C);
}
