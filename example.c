#include <stdio.h>
#include <stdlib.h>
#include "matmul.h"

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
}

