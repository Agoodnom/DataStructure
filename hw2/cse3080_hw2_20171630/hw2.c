#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int cnt = 0;
int t;

void hanoi(FILE*fp,int n, char FROM, char TMEP, char TO);

int main(int argc, char *argv[]) {
	clock_t start = clock();
	if (argc != 2) {
		printf("usage: ./hw2 number-of-disks\n");
		exit(1);
	}
	FILE* fp = fopen("hw2_result.txt", "w");
	int n = atoi(argv[1]);
	t = n;

	char A = 'A', B = 'B', C = 'C';
	hanoi(fp,n, A, B, C);
	
	fprintf(fp,"Total number of moves for %d disks: %d\n", n, cnt);
	fprintf(fp,"Runnig time: %lf seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	fclose(fp);
	printf("Program Complete. Output saved to hw2_result.txt.\n");
	return 0;
}

void hanoi(FILE* fp,int n, char FROM, char TMEP, char TO) {
	if (n == 1) {

		fprintf(fp,"MOVE DISK #%d FROM %c TO %c (moves: %d)\n", t + 1 - n, FROM, TO, ++cnt);
	}
	else {
		hanoi(fp,n - 1, FROM, TO, TMEP);
		fprintf(fp,"MOVE DISK #%d FROM %c TO %c (moves: %d)\n", t + 1 - n, FROM, TO, ++cnt);
		hanoi (fp,n - 1, TMEP, FROM, TO);
	}
}
