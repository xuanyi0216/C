#include <stdio.h>

void build_gray(int n, int k, char result[], int idx) {
	if (n == 1) {
		result[idx] = (k == 0) ? '0' : '1';
		return;
	}

	int half = 1 << (n - 1);
	if (k < half) {
		result[idx] = '0';
		build_gray(n - 1, k, result, idx + 1);
	} else {
		result[idx] = '1';
		build_gray(n - 1, (1 << n) - 1 - k, result, idx + 1);
	}
}

int main() {
	int n, k;

	while (scanf("%d", &n) == 1) {
		if (n == -1) {
			break;
		}
		if (scanf("%d", &k) != 1) {
			break;
		}

		char gray[9];
		build_gray(n, k, gray, 0);
		gray[n] = '\0';

		printf("%s\n", gray);
	}

	return 0;
}
