#include"matrices.h"
#include"row_ops.h"
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
	free_vector(Mi);free_vector(Mj);
	return M;
}

matrix *scalerow(matrix* M, unsigned int i, double c){
	vector* tmp = getrow(M,i);
	vector* Mi = scalmul(tmp, c);
	free_vector(tmp);
	int k;
	for (k=0; k < M->ncols; k++){
		M->cols[k]->vals[i] = Mi->vals[k];
	}	
	free_vector(Mi);
	return M;
}

matrix *addrows(matrix* M, unsigned int i, double c, unsigned int j){
	vector* tmp = getrow(M,i);
	vector* Mi = scalmul(tmp,c);
	free_vector(tmp);
	vector* Mj = getrow(M, j);
	vector* Msum = v_add(Mi,Mj);
	int k;
	for (k=0; k < M->ncols; k++){
		M->cols[k]->vals[j] = Msum->vals[k];
	}
	free_vector(Mi);free_vector(Mj);free_vector(Msum);
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

matrix *rowReduce(matrix* A, node* head){
	mat_ERO op;
	matrix *M = matcpy(A);
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
					printOP(op);
					A = scalerow(A,j,(1/val));
				}
				if (j!= 0 && j!= pivot){
					op.type = 1;
					op.rows[0] = pivot;
					op.rows[1] = j;
					EROlist = append(op, EROlist);
					printOP(op);
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
						printOP(op);
						A = addrows(A, pivot, -1*val, k);
					}
				}
				pivot++;
				break;
			}
		}	
	}
	free_matrix(A);
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

matrix *minor(matrix *M,int n,int m){
	matrix *A = new_matrix(M->ncols-1, M->nrows-1);
	vector *v = new_vector(M->nrows-1);
	int i;
	int j;
	int k;
	int l = 0;
	for (int i=0; i<M->ncols; i++){
		if (i==n){
			continue;
		}
		k = 0;
		for (int j=0; j<M->nrows; j++){
			if (j==m){
				continue;
			}
			v->vals[k]=M->cols[i]->vals[j];
			k++;
		}
		A->cols[l] = veccopy(v);
		l++;
	}
	return A;
}

double slow_determinant(matrix *M){
	if (M->ncols != M->nrows){
		printf("Non-square matrices do not have determinants.");
	}
	if (M->ncols == 2){
		return (M->cols[0]->vals[0])*(M->cols[1]->vals[1])-(M->cols[1]->vals[0])*(M->cols[0]->vals[1]);
	}
	/* Do cofactor expansion along the first column */
	vector *v1 = M->cols[0];
	int i;
	double det = 0;
	matrix *M0i;
	for (i=0; i<v1->dim; i++){
		if (v1->vals[i] == 0){continue;}
		// 1-((i*1)<<1) = (-1)**i
		M0i = minor(M,0,i); 
		det += (1-((i&1)<<1))*(v1->vals[i])*slow_determinant(M0i); 
	}
	return det;
}

double determinant(matrix *M){
	/* Row reduce, compute det of RREF first */ 
	node *head = computeEROs(M);
	matrix *R = rowReduce(M, head);
	double det = slow_determinant(R);
	free_matrix(R);
	if (det == 0){
		return 0;
	}
	/* now apply the row rules in reverse */
	mat_ERO op;
	while(head->next != NULL){
		op = head->op;
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
		head = head->next;
	}
	/* don't forget the last op */
	op = head->op;
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
