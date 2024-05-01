#include<stdio.h>
#include<stdlib.h>

typedef struct mat_ERO{
	/* elementary row operation */
	int type; // 1-swap, 2-scale, 3-add
	int rows[2]; 
	double scalar;
} mat_ERO;

typedef struct node{
	struct mat_ERO op;
	struct node *next;
	int index;
} node;

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
	node *n_node = malloc(sizeof(node));
	n_node->op = op;
	n_node->next = NULL;
	n_node->index = k+1;
	if (k==0){
		list = n_node;
	}
	else{
		head->next = n_node;
	}
	return list;
}

