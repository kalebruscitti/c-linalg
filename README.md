# C-LinAlg Library
A practice implementation of linear algebra tools in C

## Usage:
**Defining vectors**
Example: The code
```
	/* Defining vectors, printing */
	vector *x = new_vector(3);
	x->vals[0]=1.; x->vals[1]=2.5; x->vals[2]=0.;

	printf("The vector x = ");
	printv(x);
	printf("\n");
```
outputs
```
The vector x = [1.00,2.50,0.00]
```

**Vector addition, scalar multiples, and dot product**
Example: the code
```
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
```
outputs
```
y= [0.00,1.00,1.00]
x+y = [1.00,3.50,1.00]
2[2.00,3.00] = [4.00,6.00]
<x,y> = 2.50 
```

** Matrices, matrix-vector multiplication and matrix multiplication **
Example, defining a matrix: the code
```	
matrix *A = new_matrix(2, 3);
A->cols[0] = x;
A->cols[1] = y;
printf("Matrix A = \n");printM(A);printf("\n");
```
outputs
```
Matrix A = 
[1.00,0.00]
[2.50,1.00]
[0.00,1.00]
```
Example, matrix multiplication: the code
```
vector *b = matvectmul(A, z);
printf("Multiplying A by [2.,3.] gives ");printv(b);printf("\n\n");

w->vals[0]=3.;
w->vals[1]=-2.;
matrix *B = new_matrix(2,2);
B->cols[0]=w;
B->cols[1]=z;
matrix *C = matmul(A,B);
printM(A);printf("*\n");printM(B);printf("=\n");printM(C);
```
outputs
```
Multiplying A by [2.,3.] gives [2.00,8.00,3.00]

[1.00,0.00]
[2.50,1.00]
[0.00,1.00]
*
[3.00,2.00]
[-2.00,3.00]
=
[3.00,2.00]
[5.50,8.00]
[-2.00,3.00]
```
