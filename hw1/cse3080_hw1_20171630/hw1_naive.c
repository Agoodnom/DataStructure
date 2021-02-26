#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 10000000
#define PAT_MAX 3000

char str[STR_MAX] = { 0, };
char pat[PAT_MAX] = { 0, };
int strindex[STR_MAX] = { 0, };
int cnt = 0;

void nfind();

int main() {

	FILE *fp1 = fopen("string.txt", "r");
	if (fp1 == NULL) {
		printf("The string file does not exist.\n");
		return -1;
	}
	fgets(str, STR_MAX, fp1);

	FILE *fp2 = fopen("pattern.txt", "r");
	if (fp2 == NULL) {
		printf("The pattern file does not exist.\n");
		return -1;
	}
	fgets(pat, PAT_MAX, fp2);

	FILE *fp3 = fopen("result_naive.txt", "w");

	nfind();

	fprintf(fp3, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		fprintf(fp3, "%d ", strindex[i]);
	}

	printf("Program complete. Result saved to result_naive.txt\n");


	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}

void nfind() {
	int i = 0, j = 0, start = 0;
	int lasts = strlen(str) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (str[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && str[i] == pat[j]; i++, j++)
				;
		if (j == lastp) {
			cnt++;
			strindex[cnt - 1] = start;
		}
		j = 0;
	}
	strindex[cnt] = '\0';
}
