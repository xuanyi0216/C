#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 210

typedef struct {
	int sign;               /* 1 for non-negative, -1 for negative */
	int len;                /* number of used digits */
	int d[MAX_DIGITS];      /* little-endian digits */
} BigInt;

void trim_newline(char *s) {
	size_t n = strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
		s[n - 1] = '\0';
		n--;
	}
}

void normalize(BigInt *a) {
	while (a->len > 1 && a->d[a->len - 1] == 0) {
		a->len--;
	}
	if (a->len == 1 && a->d[0] == 0) {
		a->sign = 1;
	}
}

void parse_bigint(const char *s, BigInt *a) {
	int start = 0;
	int n = (int)strlen(s);

	a->sign = 1;
	if (s[0] == '-') {
		a->sign = -1;
		start = 1;
	}

	a->len = n - start;
	for (int i = 0; i < a->len; i++) {
		a->d[i] = s[n - 1 - i] - '0';
	}
	normalize(a);
}

int cmp_abs(const BigInt *a, const BigInt *b) {
	if (a->len != b->len) {
		return (a->len > b->len) ? 1 : -1;
	}
	for (int i = a->len - 1; i >= 0; i--) {
		if (a->d[i] != b->d[i]) {
			return (a->d[i] > b->d[i]) ? 1 : -1;
		}
	}
	return 0;
}

BigInt add_abs(const BigInt *a, const BigInt *b) {
	BigInt r;
	int carry = 0;
	int max_len = (a->len > b->len) ? a->len : b->len;

	r.sign = 1;
	r.len = 0;
	for (int i = 0; i < max_len || carry; i++) {
		int sum = carry;
		if (i < a->len) sum += a->d[i];
		if (i < b->len) sum += b->d[i];
		r.d[r.len++] = sum % 10;
		carry = sum / 10;
	}
	normalize(&r);
	return r;
}

BigInt sub_abs(const BigInt *a, const BigInt *b) {
	/* assumes |a| >= |b| */
	BigInt r;
	int borrow = 0;

	r.sign = 1;
	r.len = a->len;
	for (int i = 0; i < a->len; i++) {
		int diff = a->d[i] - borrow - (i < b->len ? b->d[i] : 0);
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}
		r.d[i] = diff;
	}
	normalize(&r);
	return r;
}

BigInt add_bigint(const BigInt *a, const BigInt *b) {
	if (a->sign == b->sign) {
		BigInt r = add_abs(a, b);
		r.sign = a->sign;
		normalize(&r);
		return r;
	}

	int cmp = cmp_abs(a, b);
	if (cmp == 0) {
		BigInt z;
		z.sign = 1;
		z.len = 1;
		z.d[0] = 0;
		return z;
	}
	if (cmp > 0) {
		BigInt r = sub_abs(a, b);
		r.sign = a->sign;
		normalize(&r);
		return r;
	} else {
		BigInt r = sub_abs(b, a);
		r.sign = b->sign;
		normalize(&r);
		return r;
	}
}

BigInt sub_bigint(const BigInt *a, const BigInt *b) {
	BigInt nb = *b;
	if (!(nb.len == 1 && nb.d[0] == 0)) {
		nb.sign *= -1;
	}
	return add_bigint(a, &nb);
}

BigInt mul_bigint(const BigInt *a, const BigInt *b) {
	BigInt r;
	for (int i = 0; i < MAX_DIGITS; i++) {
		r.d[i] = 0;
	}

	r.len = a->len + b->len;
	r.sign = a->sign * b->sign;

	for (int i = 0; i < a->len; i++) {
		int carry = 0;
		for (int j = 0; j < b->len || carry; j++) {
			long long cur = r.d[i + j] + carry;
			if (j < b->len) {
				cur += (long long)a->d[i] * b->d[j];
			}
			r.d[i + j] = (int)(cur % 10);
			carry = (int)(cur / 10);
		}
	}

	normalize(&r);
	return r;
}

void print_bigint(const BigInt *a) {
	if (a->sign < 0) {
		putchar('-');
	}
	for (int i = a->len - 1; i >= 0; i--) {
		putchar((char)('0' + a->d[i]));
	}
	putchar('\n');
}

int main(void) {
	char s1[256], s2[256];
	BigInt a, b;

	if (fgets(s1, sizeof(s1), stdin) == NULL) {
		return 0;
	}
	if (fgets(s2, sizeof(s2), stdin) == NULL) {
		return 0;
	}

	trim_newline(s1);
	trim_newline(s2);

	parse_bigint(s1, &a);
	parse_bigint(s2, &b);

	BigInt sum = add_bigint(&a, &b);
	BigInt diff = sub_bigint(&a, &b);
	BigInt prod = mul_bigint(&a, &b);

	print_bigint(&sum);
	print_bigint(&diff);
	print_bigint(&prod);

	return 0;
}
