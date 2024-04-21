#C-LinAlg Library
A practice implementation of linear algebra tools in C

## Usage:
**Defining vectors**
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
