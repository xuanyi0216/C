#include <stdio.h>
#include <ctype.h>

typedef unsigned long long ull;

int char_to_value(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	c = (char)toupper((unsigned char)c);
	if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 10;
	}
	return -1;
}

char value_to_char(int v) {
	if (v >= 0 && v <= 9) {
		return (char)('0' + v);
	}
	return (char)('A' + (v - 10));
}

int main() {
	int m, n;
	char input[64];
	char out_rev[128];
	char out[128];
	ull decimal = 0;
	char *p;

	if (scanf("%d", &m) != 1) {
		return 0;
	}
	if (scanf("%63s", input) != 1) {
		return 0;
	}
	if (scanf("%d", &n) != 1) {
		return 0;
	}

	p = input;
	while (*p != '\0') {
		int val = char_to_value(*p);
		if (val < 0 || val >= m) {
			return 0;
		}
		decimal = decimal * (ull)m + (ull)val;
		p++;
	}

	if (decimal == 0) {
		printf("0\n");
		return 0;
	}

	p = out_rev;
	while (decimal > 0) {
		int digit = (int)(decimal % (ull)n);
		*p = value_to_char(digit);
		p++;
		decimal /= (ull)n;
	}
	*p = '\0';

	{
		char *src = p - 1;
		char *dst = out;
		while (src >= out_rev) {
			*dst = *src;
			dst++;
			src--;
		}
		*dst = '\0';
	}

	printf("%s\n", out);
	return 0;
}
