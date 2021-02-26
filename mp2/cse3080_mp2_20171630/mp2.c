#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ELEMENTS 1000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
} element;
element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];
element tempH[MAX_ELEMENTS];
int max_n = 0;
int min_n = 0;
int tempN = 0;

void insert_max_heap(element item, int *n);
void insert_min_heap(element item, int *n);

element print_delete_max_heap(int *n);
element print_delete_min_heap(int *n);

void print_max_heap();
void print_min_heap();

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: ./mp2 input_filename\n");
		exit(1);
	}
	double time=clock();
	char input[20];
	char* temp;
	char* command;
	element data;


	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("The input file dose not exist.\n");
		exit(1);
	}
	FILE *outfile;
	outfile = fopen("mp2_result.txt", "w");
	fclose(outfile);
	while (!feof(fp)) {
		input[2] = 0;
		fgets(input, 19, fp);
		temp = strtok(input, "\n");
		command = strtok(input, " ");
		if (!strcmp(command, "INSERT")) {
			temp = strtok(NULL, " ");
			if (temp != NULL) {
				data.key = atoi(temp);
				insert_max_heap(data, &max_n);
				insert_min_heap(data, &min_n);
			}
		}
		else if (!strcmp(command, "ASCEND")) {
			for (int i = 0; i <= min_n; i++) {
				tempH[i] = min_heap[i];
			}
			tempN = min_n;
			print_min_heap();
		}
		else if (!strcmp(command, "DESCEND")) {
			for (int i = 0; i <= max_n; i++) {
				tempH[i] = max_heap[i];
			}
			tempN = max_n;
			print_max_heap();
		}
	}
	printf("output written to mp2_result.txt.\n");
	printf("running time: %f seconds\n", (clock() - time)/CLOCKS_PER_SEC);
	return 0;
}

void insert_max_heap(element item, int *n) {
	int i;
	if (HEAP_FULL(*n)) {
		printf("ERROR: The heap is full.\n");
		exit(1);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > max_heap[i / 2].key)) {
		max_heap[i] = max_heap[i / 2];
		i /= 2;
	}
	max_heap[i] = item;
}

void insert_min_heap(element item, int *n) {
	int i;
	if (HEAP_FULL(*n)) {
		printf("ERROR: The heap is full.\n");
		exit(1);
	}
	i = ++(*n);
	while ((i != 1) && (item.key < min_heap[i / 2].key)) {
		min_heap[i] = min_heap[i / 2];
		i /= 2;
	}
	min_heap[i] = item;
}

element print_delete_max_heap(int *n) {

	
	int parent, child;
	element item, temp;

	item = tempH[1];
	temp = tempH[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (tempH[child].key < tempH[child + 1].key)) child++;
		if (temp.key >= tempH[child].key) break;
		tempH[parent] = tempH[child];
		parent = child;
		child *= 2;
	}
	tempH[parent] = temp;
	return item;
}

element print_delete_min_heap(int *n) {


	int parent, child;
	element item, temp;

	item = tempH[1];
	temp = tempH[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (tempH[child].key > tempH[child + 1].key)) child++;
		if (temp.key <= tempH[child].key) break;
		tempH[parent] = tempH[child];
		parent = child;
		child *= 2;
	}
	tempH[parent] = temp;
	return item;
}

void print_max_heap() {
	FILE *outfile;
	element item;
	int n = tempN;
	outfile = fopen("mp2_result.txt", "a");
	
	for (int i = 0; i < n; i++) {
		item = print_delete_max_heap(&tempN);
		fprintf(outfile,"%d ", item.key);
	}



	fprintf(outfile, "\n");
	fclose(outfile);
}
void print_min_heap() {
	FILE *outfile;
	element item;
	int n = tempN;
	outfile = fopen("mp2_result.txt", "a");
	
	for (int i = 0; i < n; i++) {
		item = print_delete_min_heap(&tempN);
		fprintf(outfile,"%d ", item.key);
	}

	fprintf(outfile, "\n");
	fclose(outfile);
}
