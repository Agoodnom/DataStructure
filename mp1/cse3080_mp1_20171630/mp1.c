#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUM 1000

typedef struct _node {
	int data;
	struct _node* prev;
	struct _node* next;
}node;

typedef node* listPointer;

listPointer head;

void insert(int data);
void delete(int data);
void print_forward(listPointer list);
void print_reverse(listPointer list);
void freeAll();

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: ./mp1 input_filename\n");
		exit(1);
	}
	char input[20];
	char* temp;
	char* command;
	int data;


	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("The input file dose not exist.\n");
		exit(1);
	}
	FILE *outfile;
	outfile = fopen("mp1_result.txt", "w");
	fclose(outfile);
	while (!feof(fp)) {
		input[2] = 0;
		fgets(input, 19, fp);
		temp = strtok(input, "\n");
		command = strtok(input, " ");
		if (!strcmp(command, "INSERT")) {
			temp = strtok(NULL, " ");
			if (temp != NULL) {
				data = atoi(temp);
				insert(data);
			}
		}
		else if (!strcmp(command, "DELETE")) {
			temp = strtok(NULL, " ");
			if (temp != NULL) {
				data = atoi(temp);
				delete(data);
			}
		}
		else if (!strcmp(command, "ASCEND")) {
			print_forward(head);
		}
		else if (!strcmp(command, "DESCEND")) {
			print_reverse(head);
		}

	}
	freeAll();
	return 0;
}

void insert(int data) {
	listPointer cur,ptr,min;
	listPointer newnode = (listPointer)malloc(sizeof(node));

	newnode->data = data;
	newnode->next = newnode;
	newnode->prev = newnode;

	if (head == NULL) {
		head = newnode;
		return;
	}

	cur = head;
	while (cur->data < data&&cur != head->prev) {
		cur = cur->next;
	}
	if (cur->data == data) {
		return;
	}
	if (cur->data < data) {
		cur = cur->next;
	}
	cur = cur->prev;
	newnode->prev = cur;
	newnode->next = cur->next;
	cur->next->prev = newnode;
	cur->next = newnode;

	ptr = head;
	min = ptr;
	while (ptr != head->prev) {
		ptr = ptr->next;
		if (min->data > ptr->data)
			min = ptr;
	}
	if (min->data > ptr->data)
		min = ptr;

	head = min;

	
}
void delete(int data) {
	listPointer cur;
	cur = head;
	while (cur->data != data && cur != head->prev) {
		cur = cur->next;
	}
	if (cur == head) {
		head = cur->next;
	}
	if (cur->data == data) {
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		free(cur);
	}
}
void print_forward(listPointer list) {
	listPointer curr;
	FILE *outfile;

	outfile = fopen("mp1_result.txt", "a");
	if (list) {
		curr = list;
		while (1) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->next;
			if (curr == list) break;
		}
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}
void print_reverse(listPointer list) {

	listPointer curr;
	FILE *outfile;

	outfile = fopen("mp1_result.txt", "a");
	if (list) {
		curr = list->prev;

		while (curr != list) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->prev;
		} fprintf(outfile, "%d ", curr->data);
		printf("%d ", curr->data);
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}
void freeAll() {
	listPointer cur,pre;
	cur = head->next;
	while (cur != head) {
		pre = cur;
		cur = cur->next;
		pre->prev->next = pre->next;
		pre->next->prev = pre->prev;
		free(pre);
	}
	free(head);
	head = NULL;
}