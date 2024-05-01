#include"matmul.h"
#include"row_op.c"
#include<stdbool.h>
#include<stdio.h>

matrix *swaprow(matrix* M, unsigned int i, unsigned int j){
	vector* Mi = getrow(M, i);
	vector* Mj = getrow(M, j);
	int k;
	for (k=0; k < M->ncols; k++){
		M->cols[k]->vals[i] = Mj->vals[k];
		M->cols[k]->vals[j] = Mi->vals[k];
	}
	return M;
}

matrix *scalerow(matrix* M, unsigned int i, double c){
	vector* Mi = getrow(M,i);
	Mi = scalmul(Mi, c);
	int k;
	for (k=0; k < M->ncols; k++){
		M->cols[k]->vals[i] = Mi->vals[k];
	}	
	return M;
}

matrix *addrows(matrix* M, unsigned int i, double c, unsigned int j){
	vector* Mi = scalmul(getrow(M, i),c);
	vector* Mj = getrow(M, j);
	vector* Msum = v_add(Mi,Mj);
	int k;
	for (k=0; k < M->ncols; k++){
		M->cols[k]->vals[j] = Msum->vals[k];
	}
	return M;
}

matrix *applyERO(matrix* M, mat_ERO op){
	switch (op.type){
		case 0:
			printf("undefined ERO\n");
			break;
		case 1:
			M = swaprow(M, op.rows[0], op.rows[1]);
			break;
		case 2:
			M = scalerow(M, op.rows[0], op.scalar);
			break;
		case 3:
			M = addrows(M, op.rows[0], op.scalar, op.rows[1]);
			break;
	}
	return M;
}

void printOP(mat_ERO op){
	switch (op.type){
		case 0:
			printf("undefined ERO\n");
			break;
		case 1:
			printf("Swapping row %d and %d\n", op.rows[0], op.rows[1]);
			break;
		case 2:
			printf("Scaling row %d by %f\n", op.rows[0], op.scalar);
			break;
		case 3:
			printf("Adding %f times row %d to row %d\n", op.scalar, op.rows[0], op.rows[1]);
			break;
	}
}

matrix *rowReduce(matrix* M, node* head){
	mat_ERO op;
	while (head->next != NULL){
		op = head->op;
		M = applyERO(M, op);
		head = head->next;
	}
	/* do last node! */
	op = head->op;
	M = applyERO(M, op);
	return M;
}

matrix *matcpy(matrix *M){
	matrix *A = new_matrix(M->ncols, M->nrows);
	int i;
	int j;
	vector *Mi;
	vector *vi = new_vector(M->nrows);
	for (i=0; i<M->ncols; i++){
		Mi = M->cols[i];
		for (j=0; j<Mi->dim; j++){
			vi->vals[j]=Mi->vals[j];
			
		}
		A->cols[i] = veccopy(vi);
	}
	return A;
}

node *computeEROs(matrix *M){
	matrix *A = matcpy(M);
	node *EROlist = new_list();
	int i;
	int j;
	int k;
	int pivot = 0;
	double val;
	vector *Ai;
	mat_ERO op;
	for (i=0; i < A->ncols; i++){
		Ai = A->cols[i];
		/* find highest non-zero entry in column i 
		 * and swap it to the top row 	*/
		for (j=pivot; j < A->nrows; j++){
			if (Ai->vals[j] != 0){
				val = Ai->vals[j];
				if (val != 1){
					op.type = 2;
					op.rows[0]=j;
					op.scalar = (1/val);
					EROlist = append(op, EROlist);
					A = scalerow(A,j,(1/val));
				}
				if (j!= 0 && j!= pivot){
					op.type = 1;
					op.rows[0] = pivot;
					op.rows[1] = j;
					EROlist = append(op, EROlist);
					A = swaprow(A, pivot, j);
				}
				/* since we moved things, refresh Ai */
				Ai = A->cols[i]; 
				/* use this to eliminate all others */
				for (k=0; k < A->nrows; k++){
					if (k!=pivot){
						val = Ai->vals[k];
						op.type = 3;
						op.rows[0]= pivot;
						op.rows[1] = k;
						op.scalar = -1*val;
						EROlist = append(op, EROlist);
						A = addrows(A, pivot, -1*val, k);
					}
				}
				pivot++;
				break;
			}

		}	
	}
	return EROlist;
}

matrix *inverse(matrix *M){
	if (M->nrows != M->ncols){
		printf("Non-square matrices are not invertible");
		return NULL;
	}
	node *list = computeEROs(M);
	/* construct identity matrix */
	matrix *Id = new_matrix(M->ncols, M->ncols);
	vector *ei;
	int i;
	for (i=0; i<M->ncols; i++){
		ei = new_vector(M->ncols);
		ei->vals[i]=1;
		Id->cols[i] = ei;
	}
	Id = rowReduce(Id, list);
	return Id;
}

double determinant(matrix *M){
	double det = 1;
	node *head = computeEROs(M);
	mat_ERO op;
	while(head->next != NULL){
		op = head->op;
		printOP(op);
		switch (op.type){
			case 0:
				printf("undefined ERO\n");
				break;
			case 1:
				det = -1*det;
				break;
			case 2:
				det = det/op.scalar;
				break;
			case 3:
				break;
		}
		printf("det: %f, ", det);
		head = head->next;
	}
	/* don't forget the last op */
	op = head->op;
	printOP(op);
	switch (op.type){
		case 0:
			printf("undefined ERO\n");
			break;
		case 1:
			det = -1*det;
			break;
		case 2:
			det = det*op.scalar;
			break;
		case 3:
			break;
	} 
	return det;
}
