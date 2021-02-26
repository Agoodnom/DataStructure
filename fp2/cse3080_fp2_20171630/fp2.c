#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VERTICES 10000
#define MAX_EDGES 100000000
#define INF 999999999

FILE* fp;
FILE *outfile;
int cost[MAX_VERTICES][MAX_VERTICES] = { 0, };
int distance[MAX_VERTICES] = { 0, };
int found[MAX_VERTICES] = { 0, };
int parent[MAX_VERTICES];
int vertex_num;
int edge_num;
int src_vertex;

void init();
void dijkstra();
int choose();
void print();

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: ./fp2 input_filename\n");
		exit(1);
	}
	double time = clock();
	int from, to, weight;

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("The input file dose not exist.\n");
		exit(1);
	}
	outfile = fopen("fp2_result.txt", "w");


	fscanf(fp, "%d ", &vertex_num);
	init();
	fscanf(fp, "%d ", &edge_num);
	for (int i = 0; i < edge_num; i++) {
		fscanf(fp, "%d %d %d ", &from, &to, &weight);
		cost[from][to] = weight;
	}
	fscanf(fp, "%d ", &src_vertex);

	dijkstra();
	print();

	fclose(fp);
	fclose(outfile);

	printf("output written to fp2_result.txt.\n");
	printf("running time: %f seconds\n", (clock() - time) / CLOCKS_PER_SEC);
	return 0;
}

void init() {
	int i, j;
	for (i = 0; i < vertex_num; i++) {
		parent[i] = -1;
		distance[i] = INF;
		for (j = 0; j < vertex_num; j++) {
			if (i != j)
				cost[i][j] = INF;
		}
	}
}

void dijkstra() {
	int i, w, u, prev = src_vertex;

	for (i = 0; i < vertex_num; i++) {
		distance[i] = cost[src_vertex][i];
		if (cost[src_vertex][i] != INF && i != src_vertex)
			parent[i] = src_vertex;
	}
	found[src_vertex] = 0;
	distance[src_vertex] = 0;

	for (i = 0; i < vertex_num; i++) {
		u = choose();
		if (u == -1)
			continue;
		found[u] = 1;
		for (w = 0; w < vertex_num; w++)
			if (!found[w]) {
				if (distance[u] + cost[u][w] < distance[w]) {
					distance[w] = distance[u] + cost[u][w];
					parent[w] = u;
				}
			}
	}
}

int choose() {
	int i, min, minpos;

	min = INF;
	minpos = -1;
	for (i = 0; i < vertex_num; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}

	return minpos;
}

void print() {
	int i, j;
	int p;
	int *path = (int*)malloc(sizeof(int)*vertex_num);
	int n;

	for (i = 0; i < vertex_num; i++) {
		n = vertex_num - 1;
		if (distance[i] == INF) {
			fprintf(outfile, "SRC: %d, DST: %d, LENGTH: -, PATH: -", src_vertex, i);
			fprintf(outfile, "\n");
		}
		else {
			fprintf(outfile, "SRC: %d, DST: %d, LENGTH: %d, PATH:", src_vertex, i, distance[i]);

			p = parent[i];
			for (j = i; (p = parent[j]) >= 0; j = p) {
				path[n] = p;
				n--;
			}
			n++;
			for (; n < vertex_num; n++) {
				fprintf(outfile, " %d", path[n]);
			}
			fprintf(outfile, " %d\n", i);
		}
	}
}