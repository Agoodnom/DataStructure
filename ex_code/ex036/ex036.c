#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

struct node {
  char data;
  struct node *left_child, *right_child;
};
typedef struct node *tree_pointer;

tree_pointer create_tree_node(char data);
void recursive_inorder(tree_pointer ptr);
void recursive_preorder(tree_pointer ptr);
void recursive_postorder(tree_pointer ptr);
void iter_inorder(tree_pointer ptr);
void iter_postorder(tree_pointer ptr);
void iter_preorder(tree_pointer ptr);
void level_order(tree_pointer ptr);
void add(int *top, tree_pointer ptr);
tree_pointer delete(int *top);
/* TODO: add function prototype if necessary */
tree_pointer stack[MAX_STACK_SIZE];

void main() {

  /* create a tree that represents an arithmetic expression */
  tree_pointer ptr, ptr1, ptr2;

  ptr1 = create_tree_node('A');
  ptr2 = create_tree_node('B');
  ptr = create_tree_node('/');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  ptr1 = ptr;
  ptr2 = create_tree_node('C');
  ptr = create_tree_node('*');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  ptr1 = ptr;
  ptr2 = create_tree_node('D');
  ptr = create_tree_node('*');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  ptr1 = ptr;
  ptr2 = create_tree_node('E');
  ptr = create_tree_node('+');
  ptr->left_child = ptr1;
  ptr->right_child = ptr2;

  /* call traversal functions */
  recursive_inorder(ptr);
  printf("\n");
  iter_inorder(ptr);
  printf("\n\n");
  recursive_preorder(ptr);
  printf("\n");
  iter_preorder(ptr);
  printf("\n\n");
  recursive_postorder(ptr);
  printf("\n");
  iter_postorder(ptr);
  printf("\n\n");
  level_order(ptr);
  printf("\n");
}
  
tree_pointer create_tree_node(char data) {
  tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node));
  ptr->data = data;
  ptr->left_child = NULL;
  ptr->right_child = NULL;
  return ptr;
}

void recursive_inorder(tree_pointer ptr) {
  if(ptr) {
    recursive_inorder(ptr->left_child);
    printf("%c ", ptr->data);
    recursive_inorder(ptr->right_child);
  }
}
void recursive_preorder(tree_pointer ptr) {
	if (ptr) {
		printf("%c ", ptr->data);
		recursive_preorder(ptr->left_child);
		recursive_preorder(ptr->right_child);
	}
}
void recursive_postorder(tree_pointer ptr) {
	if (ptr) {
		recursive_postorder(ptr->left_child);
		recursive_postorder(ptr->right_child);
		printf("%c ", ptr->data);
	}
}

void iter_inorder(tree_pointer ptr) { 
  /* TODO: you must complete this function */
	int top = -1;
	while (1) {
		while (ptr) {
			add(&top, ptr);
			ptr = ptr->left_child;
		}
			ptr = delete(&top);
			if (!ptr) break;
			printf("%c ", ptr->data);
			ptr = ptr->right_child;
		
	}
}
void iter_preorder(tree_pointer ptr) {
  /* TODO: you must complete this function */
	int top = -1;
	while (1) {
		
		while (ptr) {
			printf("%c ", ptr->data);
			add(&top, ptr);
			ptr = ptr->left_child;
		}
		ptr = delete(&top);
		if (!ptr) break;
		ptr = ptr->right_child;

	}
}
void iter_postorder(tree_pointer ptr) {
  /* TODO: you must complete this function */
	int top = -1;
	tree_pointer node=ptr;
	while (1) {
		
		while (node) {
			add(&top, node);
			node = node->left_child;
 		}
		node = NULL;
		ptr = delete(&top);
		printf("%c ", ptr->data);
		if (!ptr||top==-1) break;
		ptr = delete(&top);
		add(&top, ptr);
		ptr = ptr->right_child;
		if (ptr) {
			printf("%c ", ptr->data);
		}
	}
}
void level_order(tree_pointer ptr) {
  /* TODO: you must complete this function */
}
void add(int *top, tree_pointer ptr) {
	(*top)++;
	stack[*top] = ptr;
}
tree_pointer delete(int *top) {
	tree_pointer node = stack[*top];
	stack[*top] = NULL;
	(*top)--;
	return node;
}
/* TODO: add function implementations here */



