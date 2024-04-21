#include <stdio.h>
#include <stdlib.h>

struct vector{
	unsigned int dim;
	double *vals;
};

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

void main(){
	struct vector* x = new_vector(2);
	x->vals[0] = 1.;
	x->vals[1] = 2.;
	struct vector* y = new_vector(2);
	y->vals[0] = 3.;
	y->vals[1] = 2.;
	struct vector* z = v_add(x,y);
	printv(z);
}
