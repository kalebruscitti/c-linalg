#include <stdio.h>
#include <stdlib.h>
#include "gausselim.h"

void main(){
	/* Defining vectors, printing */
	vector *x = new_vector(3);
	x->vals[0]=1.; x->vals[1]=2.5; x->vals[2]=0.;

	printf("The vector x = ");
	printv(x);
	printf("\n");

	/* Addition and dot product */

	vector *y = new_vector(3);
	y->vals[0]=0.; y->vals[1]=1.; y->vals[2]=1.;

	printf("y= ");printv(y);printf("\n");

	vector *z = new_vector(2);
	z->vals[0]=2.; z->vals[1]=3.;

	struct vector* w = v_add(x,y);
	printf("x+y = ");printv(w);
	printf("\n");
	free_vector(w);

	w = scalmul(z, 2.);
	printf("2");printv(z);printf(" = ");printv(w);
	printf("\n");
	
	double c = v_dot(x,y);
	printf("<x,y> = %.2f \n", c);

	/* Matrices and multiplication */
	matrix *A = new_matrix(2, 3);
	A->cols[0] = x;
	A->cols[1] = y;
	printf("Matrix A = \n");printM(A);printf("\n");

	vector *b = matvectmul(A, z);
	printf("Multiplying A by [2.,3.] gives ");printv(b);printf("\n\n");

	w->vals[0]=3.;
	w->vals[1]=-2.;
	matrix *B = new_matrix(2,2);
	B->cols[0]=w;
	B->cols[1]=z;
	matrix *C = matmul(A,B);
	printM(A);printf("*\n");printM(B);printf("=\n");printM(C);
	printf("\n");

	/* Gaussian elimination */
	free_matrix(A);
	A = new_matrix(3,3);
	A->cols[0] = x;
	A->cols[1] = new_vector(3);
	A->cols[2] = y;
	printM(A);
	printf("REF of A: \n");
	A = rowechelon(A, true); 	
	printM(A);
}

