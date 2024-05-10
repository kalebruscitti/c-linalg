#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structs
typedef struct vector{
    unsigned int dim;
    double *vals;
} vector;

typedef struct matrix{
	unsigned int ncols;
	unsigned int nrows;
	vector* *cols;
} matrix;

// Matrix and Vector constructors & destructors
vector *new_vector(unsigned int dim);

void free_vector(vector *v);

vector *veccopy(vector *v);

matrix *new_matrix(unsigned int ncols, unsigned int nrows);

void free_matrix(matrix *M);

matrix *matcpy(matrix *M);

// Basic operations

vector *v_add(vector *x, vector *y);

double v_dot(vector *x, vector *y);

vector *scalmul(vector *v, double c);

void printv(vector *v);

int vecEqual(vector *v, vector *w);

int matEqual(matrix *A, matrix *B);

vector *getrow(matrix *M, int k);

void printM(matrix *M);

matrix *matmul(matrix *A, matrix *B);

vector *matvecmul(matrix *A, vector *v);

// Row Operations
typedef struct mat_ERO{
    /* one elementary row operation */
    int type; //1=swap, 2=scale, 3=add
    int rows[2];
    double scalar;
} mat_ERO;

typedef struct node{
    // Linked list of row operations
    struct mat_ERO op;
    struct node *next;
    int index;
} node;

node *new_list();

mat_ERO *new_ERO();

node *append(mat_ERO op, node *list);

void free_list(node *list);

void printOP(mat_ERO op); // for debugging


// Gaussian Elimination

matrix *swaprow(matrix *M, unsigned int i, unsigned int j);

matrix *scalerow(matrix *M, unsigned int i, double c);

matrix *addrows(matrix *M, unsigned int i, double c, unsigned int j);

matrix *applyERO(matrix *M, mat_ERO op);

matrix *rowReduce(matrix *A, node *head);

node *computeEROs(matrix *M);

matrix *inverse(matrix *M);

matrix *minor(matrix *M, int n, int m);

double slow_determinant(matrix *M);

double determinant(matrix *M);

// Utilities

vector *random_vector(unsigned int dim);

matrix *random_matrix(unsigned int ncols, unsigned int nrows);

