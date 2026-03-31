#include <stdio.h>
#include <string.h>

int feedback_count(int m) {
	if (m == 0 || m == 1) {
		return 0;
	}
	if (m % 2 == 0) {
		return 1 + feedback_count(m / 2);
	}
	return 1 + feedback_count((m + 1) / 2);
}

int binary_to_int(const char s[]) {
	int value = 0;
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		value = value * 2 + (s[i] - '0');
	}
	return value;
}

void print_4bit_binary(int value) {
	int i;
	for (i = 3; i >= 0; i--) {
		putchar(((value >> i) & 1) + '0');
	}
	putchar('\n');
}

int main() {
	char input[16];

	while (scanf("%15s", input) == 1) {
		if (strcmp(input, "-1") == 0) {
			break;
		}

		int m = binary_to_int(input);
		int count = feedback_count(m);
		print_4bit_binary(count);
	}

	return 0;
}
