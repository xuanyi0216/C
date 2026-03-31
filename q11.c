#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
	ll num;
	ll den;
} Fraction;

ll abs_ll(ll x) {
	return (x < 0) ? -x : x;
}

ll gcd_ll(ll a, ll b) {
	a = abs_ll(a);
	b = abs_ll(b);
	while (b != 0) {
		ll t = a % b;
		a = b;
		b = t;
	}
	return (a == 0) ? 1 : a;
}

void normalize(Fraction *f) {
	if (f->den < 0) {
		f->den = -f->den;
		f->num = -f->num;
	}
	if (f->num == 0) {
		f->den = 1;
		return;
	}
	ll g = gcd_ll(f->num, f->den);
	f->num /= g;
	f->den /= g;
}

int parse_fraction(const char *s, Fraction *out) {
	const char *lp = strchr(s, '(');
	if (lp != NULL) {
		const char *rp = strchr(s, ')');
		const char *slash = strchr(s, '/');
		if (rp == NULL || slash == NULL || !(lp < slash && slash < rp)) {
			return 0;
		}

		char int_part[64];
		char num_part[64];
		char den_part[64];
		ll integer_value, numerator_value, denominator_value;
		size_t len_int = (size_t)(lp - s);
		size_t len_num = (size_t)(slash - lp - 1);
		size_t len_den = (size_t)(rp - slash - 1);

		if (len_int == 0 || len_num == 0 || len_den == 0) {
			return 0;
		}
		if (len_int >= sizeof(int_part) || len_num >= sizeof(num_part) || len_den >= sizeof(den_part)) {
			return 0;
		}

		memcpy(int_part, s, len_int);
		int_part[len_int] = '\0';
		memcpy(num_part, lp + 1, len_num);
		num_part[len_num] = '\0';
		memcpy(den_part, slash + 1, len_den);
		den_part[len_den] = '\0';

		integer_value = atoll(int_part);
		numerator_value = atoll(num_part);
		denominator_value = atoll(den_part);

		if (denominator_value == 0) {
			return 0;
		}

		if (integer_value >= 0) {
			out->num = integer_value * denominator_value + numerator_value;
		} else {
			out->num = integer_value * denominator_value - numerator_value;
		}
		out->den = denominator_value;
		normalize(out);
		return 1;
	} else {
		const char *slash = strchr(s, '/');
		if (slash == NULL) {
			return 0;
		}

		char num_part[64];
		char den_part[64];
		ll numerator_value, denominator_value;
		size_t len_num = (size_t)(slash - s);
		size_t len_den = strlen(slash + 1);

		if (len_num == 0 || len_den == 0) {
			return 0;
		}
		if (len_num >= sizeof(num_part) || len_den >= sizeof(den_part)) {
			return 0;
		}

		memcpy(num_part, s, len_num);
		num_part[len_num] = '\0';
		memcpy(den_part, slash + 1, len_den);
		den_part[len_den] = '\0';

		numerator_value = atoll(num_part);
		denominator_value = atoll(den_part);
		if (denominator_value == 0) {
			return 0;
		}

		out->num = numerator_value;
		out->den = denominator_value;
		normalize(out);
		return 1;
	}
}

int calculate(Fraction a, char op, Fraction b, Fraction *res) {
	if (op == '+') {
		res->num = a.num * b.den + b.num * a.den;
		res->den = a.den * b.den;
	} else if (op == '-') {
		res->num = a.num * b.den - b.num * a.den;
		res->den = a.den * b.den;
	} else if (op == '*') {
		res->num = a.num * b.num;
		res->den = a.den * b.den;
	} else if (op == '/') {
		if (b.num == 0) {
			return 0;
		}
		res->num = a.num * b.den;
		res->den = a.den * b.num;
	} else {
		return 0;
	}

	if (res->den == 0) {
		return 0;
	}
	normalize(res);
	return 1;
}

void print_fraction(Fraction f) {
	ll abs_num;
	ll integer_part;
	ll rem;

	normalize(&f);
	if (f.num == 0) {
		printf("0\n");
		return;
	}

	abs_num = abs_ll(f.num);
	if (abs_num < f.den) {
		if (f.num < 0) {
			printf("-%lld/%lld\n", abs_num, f.den);
		} else {
			printf("%lld/%lld\n", abs_num, f.den);
		}
		return;
	}

	integer_part = abs_num / f.den;
	rem = abs_num % f.den;

	if (rem == 0) {
		if (f.num < 0) {
			printf("-%lld\n", integer_part);
		} else {
			printf("%lld\n", integer_part);
		}
		return;
	}

	if (f.num < 0) {
		printf("-%lld(%lld/%lld)\n", integer_part, rem, f.den);
	} else {
		printf("%lld(%lld/%lld)\n", integer_part, rem, f.den);
	}
}

int main() {
	char s1[128], s2[128], op_str[16], cont[16];

	while (1) {
		Fraction a, b, r;
		int ok_a, ok_b, ok_calc;

		if (scanf("%127s", s1) != 1) {
			break;
		}
		if (scanf("%15s", op_str) != 1) {
			break;
		}
		if (scanf("%127s", s2) != 1) {
			break;
		}
		if (scanf("%15s", cont) != 1) {
			break;
		}

		ok_a = parse_fraction(s1, &a);
		ok_b = parse_fraction(s2, &b);

		if (!ok_a || !ok_b) {
			printf("error\n");
		} else {
			ok_calc = calculate(a, op_str[0], b, &r);
			if (!ok_calc) {
				printf("error\n");
			} else {
				print_fraction(r);
			}
		}

		if (cont[0] == 'n' || cont[0] == 'N') {
			break;
		}
	}

	return 0;
}
