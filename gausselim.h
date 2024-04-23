#include"matmul.h"
#include<stdbool.h>

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

matrix *rowechelon(matrix *M, bool reduced){
	int i;
	int j;
	int k;
	int pivot = 0;
	double val;
	vector *Mi;
	for (i=0; i < M->ncols; i++){
		Mi = M->cols[i];
		/* find highest non-zero entry in column i 
		 * and swap it to the top row 	*/
		for (j=pivot; j < M->nrows; j++){
			if (Mi->vals[j] != 0){
				val = Mi->vals[j];
				if (val != 1){
					M = scalerow(M, j, (1/val));
				}
				if (j!= 0){
					swaprow(M, pivot, j);
				}
				/* since we moved things, refresh Mi */
				Mi = M->cols[i]; 
				/* use this to eliminate all others */
				for (k=0; k < M->nrows; k++){
					if (k!=pivot){
						val = Mi->vals[k];
						M = addrows(M, pivot, -1*val, k);
					}
				}
				pivot++;
				break;
			}

		}	
	}
	return M;
}
