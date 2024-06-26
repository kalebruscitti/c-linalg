#include "linalg.h"

node *new_list(){
    node *head = malloc(sizeof(node));
    head->next = NULL;
    head->index = 0;
    return head;
}

mat_ERO *new_ERO(){
    mat_ERO *op = malloc(sizeof(mat_ERO));
    return op;
}

node *append(mat_ERO op, node *list){
    node *head = list;
    int k = head->index;
    while (head->next != NULL){
        head = head->next;
        k++;
    }
    if (k==0){
        list->op = op; 
        list->index = k+1;
    }
    else{
        node *n_node = malloc(sizeof(node));
        head->next = n_node;
        n_node->op = op;
        n_node->next = NULL;
        n_node->index = k+1;

    }
    return list;
}

    void free_list(node *list){
        node *tmp;
        while (list!=NULL){
            tmp = list;
            list = list->next;
		tmp->next = NULL;
		free(tmp);
	}
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
