#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 10000000
#define PAT_MAX 3000

char str[STR_MAX] = { 0, };
char pat[PAT_MAX] = { 0, };
int strindex[STR_MAX] = { 0, };
int failure[PAT_MAX];
int cnt = 0;

void pmatch();
void fail();


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

	FILE *fp3 = fopen("result_kmp.txt", "w");

	fail();
	pmatch();


	fprintf(fp3, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		fprintf(fp3, "%d ", strindex[i]);
	}

	printf("Program complete. Result saved to result_kmp.txt\n");

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}

void fail() {

	int i, j, n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) i = failure[i];
		if (pat[j] == pat[i + 1]) failure[j] = i + 1;
		else failure[j] = -1;
	}
}

void pmatch() {

	int i = 0, j = 0;
	int lens = strlen(str);
	int lenp = strlen(pat);
	while (i < lens) {
		if (str[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;
		if (j == lenp) {
			cnt++;
			strindex[cnt - 1] = i - lenp;
			j = failure[j - 1] + 1;
		}
	}
}
