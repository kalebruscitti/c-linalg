#include "lib/linalg.h"

/* Test Parameters */
#define NTRIALS 10;
#define NTESTS 6;

void main(){
	int N_passes = NTESTS;

	/* T1: Memory Operations */
	vector *x = new_vector(3);
	x->vals[0]=1.; x->vals[1]=2.5; x->vals[2]=0.;
	vector *y = veccopy(x);
	// Test that y isn't just a pointer to the same addr as x
	x->vals[1] = 3.; 
	if (y->vals[1] != 2.5){
		printf("Test 1.1: 'veccopy' failed. \n");
		N_passes -= 1;
	} 
	
	x->vals[0] = 1.; x->vals[1]= 0.; x->vals[2]=-1.;
	y->vals[0] = 0.; y->vals[1] = 2.5; y->vals[2]=1.;
	matrix *A= new_matrix(2,3);
	A->cols[0] = x; A->cols[1] = y;

	matrix *B = matcpy(A);
	// Test B isn't just a pointer to addr of A
	A->cols[1] = y;
	if (vecEqual(B->cols[0], x)!=1){
		printf("Test 1.2: 'matcpy' failed. \n");
		N_passes -= 1;
	}
	free_matrix(B);

	/* T2: Basic Operations */
	vector *x_cpy = veccopy(x);
	if (vecEqual(x, x_cpy) != 1){
		printf("Test 2.1 'vecEqual' failed. \n");
		N_passes -= 1;
	}

	vector *z = v_add(x, y);
	vector *z_cor = new_vector(3);
	z_cor->vals[0] = 1.; z_cor->vals[1] = 2.5; z_cor->vals[2] = 0.;
	if (vecEqual(z, z_cor) != 1){
		printf("Test 2.2 'v_add' failed. \n");
		N_passes -= 1;
	}
	z = scalmul(x, 0.5);
	z_cor->vals[0] = 0.5; z_cor->vals[1]=0.; z_cor->vals[2]=-0.5; 
	if (vecEqual(z, z_cor) != 1){
		printf("Test 2.3 'scal_mul' failed. \n");
		N_passes -= 1;
	}

	vector *x2 = new_vector(2);
	x2->vals[0]=3; x2->vals[1]=0;
	vector *y2 = new_vector(2);
	y2->vals[0]=5; y2->vals[1]=-2;
	B = new_matrix(2,2);
	B->cols[0] = x2; B->cols[1] = y2;

	vector *x_cor = new_vector(3);
	vector *y_cor = new_vector(3);
	x_cor->vals[0]=3.; x_cor->vals[1]=0.; x_cor->vals[2]=-3.;
	y_cor->vals[0]=5.; y_cor->vals[1]=-5.; y_cor->vals[2]=-7.;
	matrix *C_cor = new_matrix(2,3);
	C_cor->cols[0]=x_cor; C_cor->cols[1]=y_cor;

	matrix *C = matmul(A,B);
	if (matEqual(C, C_cor) != 1){
		printf("Test 2.4 'matmul' failed. \n");
		N_passes -= 1;
	}

	/* Results */
	if (N_passes == NTESTS){
		printf("All tests passed!\n");
	} else {
		printf("%d/%d tests passed. \n", N_passes,NTESTS);
	}
}
