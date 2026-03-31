#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int g_m;

int window_cmp(const void *a, const void *b) {
	const int *wa = (const int *)a;
	const int *wb = (const int *)b;

	for (int i = 0; i < g_m; i++) {
		if (wa[i] != wb[i]) {
			return wa[i] - wb[i];
		}
	}
	return 0;
}

int is_unique_window(const int *arr, int start, int m) {
	int seen[10] = {0};

	for (int i = 0; i < m; i++) {
		int v = arr[start + i];
		if (seen[v]) {
			return 0;
		}
		seen[v] = 1;
	}
	return 1;
}

int exists_window(int uniq[][10], int uniq_count, const int *arr, int start, int m) {
	for (int i = 0; i < uniq_count; i++) {
		int same = 1;
		for (int j = 0; j < m; j++) {
			if (uniq[i][j] != arr[start + j]) {
				same = 0;
				break;
			}
		}
		if (same) {
			return 1;
		}
	}
	return 0;
}

int main(void) {
	int m;
	int arr[20];
	int n = 0;
	char line[256];

	if (scanf("%d", &m) != 1) {
		return 0;
	}

	getchar();
	if (fgets(line, sizeof(line), stdin) == NULL) {
		return 0;
	}

	char *token = strtok(line, " \t\r\n");
	while (token != NULL && n < 20) {
		arr[n++] = atoi(token);
		token = strtok(NULL, " \t\r\n");
	}

	int total = 0;
	int uniq[20][10];
	int uniq_count = 0;

	for (int i = 0; i <= n - m; i++) {
		if (!is_unique_window(arr, i, m)) {
			continue;
		}

		total++;
		if (!exists_window(uniq, uniq_count, arr, i, m)) {
			for (int j = 0; j < m; j++) {
				uniq[uniq_count][j] = arr[i + j];
			}
			uniq_count++;
		}
	}

	g_m = m;
	qsort(uniq, uniq_count, sizeof(uniq[0]), window_cmp);

	printf("%d\n", total);
	for (int i = 0; i < uniq_count; i++) {
		for (int j = 0; j < m; j++) {
			if (j > 0) {
				printf(" ");
			}
			printf("%d", uniq[i][j]);
		}
		printf("\n");
	}

	return 0;
}
