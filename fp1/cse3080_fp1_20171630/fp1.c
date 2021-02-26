#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VERTICES 10000
#define MAX_EDGES 50000000
#define HEAP_FULL(n) (n == MAX_EDGES-1)

int parent[MAX_VERTICES]; //부모 노드

typedef struct {
	int key;
	int u;
	int v;
}element;

element min_heap[MAX_EDGES];
int min_n = 0;
FILE* fp;
FILE *outfile;

int set_init(int n);
int set_find(int vertex);
int set_union(element e, int s1, int s2);
void insert_min_heap(element item, int *n);
element delete_min_heap(int *n);
void insert_heap_edge(int *n, int u, int v, int weight);
void kruskal(int vertex_n);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: ./fp1 input_filename\n");
		exit(1);
	}
	double time = clock();
	int vertex_num;
	int edge_num;
	int vertex1, vertex2, weight;

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("The input file dose not exist.\n");
		exit(1);
	}
	outfile = fopen("fp1_result.txt", "w");


	fscanf(fp, "%d ", &vertex_num);
	fscanf(fp, "%d ", &edge_num);
	set_init(vertex_num);
	for (int i = 0; i < edge_num; i++) {
		fscanf(fp, "%d %d %d ", &vertex1, &vertex2, &weight);
		insert_heap_edge(&min_n, vertex1, vertex2, weight);
	}

	kruskal(vertex_num);

	fclose(fp);
	fclose(outfile);

	printf("output written to fp1_result.txt.\n");
	printf("running time: %f seconds\n", (clock() - time) / CLOCKS_PER_SEC);
	return 0;
}

int set_init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		parent[i] = -1;
	}
}
int set_find(int vertex) {
	int i = -1;
	int p;
	for (i = vertex; (p = parent[i]) >= 0; i = p);	//루트 노드까지 반복

	return i;

}
int set_union(element e, int s1, int s2) {
	int temp = parent[s1] + parent[s2];
	if (parent[s1] > parent[s2]) {
		parent[s1] = s2;
		parent[s2] = temp;
	}
	else {
		parent[s2] = s1;
		parent[s1] = temp;
	}
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
element delete_min_heap(int *n) {
	int parent, child;
	element item, temp;

	item = min_heap[1];
	temp = min_heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (min_heap[child].key > min_heap[child + 1].key)) child++;
		if (temp.key <= min_heap[child].key) break;
		min_heap[parent] = min_heap[child];
		parent = child;
		child *= 2;
	}
	min_heap[parent] = temp;
	return item;
}
void insert_heap_edge(int *n, int u, int v, int weight) {
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(e, n);
}
void kruskal(int vertex_n) {
	int sel_edge = 0;//선택된 간선의 수
	int u, v;
	int sum = 0;
	int cnt = 0;
	element e;

	while (sel_edge < vertex_n - 1) {
		e = delete_min_heap(&min_n);
		u = set_find(e.u);
		v = set_find(e.v);
		if (u != v) {
			fprintf(outfile, "%d %d %d\n", e.u, e.v, e.key);
			cnt++;
			sum += e.key;
			sel_edge++;
			set_union(e, u, v);
		}
	}
	fprintf(outfile, "%d\n", sum);
	if (cnt == vertex_n - 1)
		fprintf(outfile, "CONNECTED\n");
	else
		fprintf(outfile, "DISCONNECTED\n");
}