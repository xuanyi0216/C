#include <stdio.h>

typedef long long ll;

typedef struct {
	ll num;
	ll den;
} Rational;

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

void reduce_fraction(ll *num, ll *den) {
	ll g;
	if (*den < 0) {
		*den = -*den;
		*num = -*num;
	}
	if (*num == 0) {
		*den = 1;
		return;
	}
	g = gcd_ll(*num, *den);
	*num /= g;
	*den /= g;
}

void set_rational(Rational *r, ll num, ll den) {
	r->num = num;
	r->den = den;
	reduce_fraction(&r->num, &r->den);
}

void compute_line(int *x1, int *y1, int *x2, int *y2, Rational *m, Rational *b) {
	ll m_num = (ll)(*y1) - (ll)(*y2);
	ll m_den = (ll)(*x1) - (ll)(*x2);
	ll b_num = (ll)(*x2) * (ll)(*y1) - (ll)(*x1) * (ll)(*y2);
	ll b_den = (ll)(*x2) - (ll)(*x1);

	set_rational(m, m_num, m_den);
	set_rational(b, b_num, b_den);
}

void print_abs_rational(const Rational *r) {
	ll n = abs_ll(r->num);
	if (r->den == 1) {
		printf("%lld", n);
	} else {
		printf("%lld/%lld", n, r->den);
	}
}

void print_line_equation(const Rational *m, const Rational *b) {
	printf("y = ");

	if (m->num == 0) {
		if (b->num == 0) {
			printf("0\n");
			return;
		}
		if (b->num < 0) {
			printf("-");
		}
		print_abs_rational(b);
		printf("\n");
		return;
	}

	if (m->num == m->den) {
		printf("x");
	} else if (m->num == -m->den) {
		printf("-x");
	} else {
		if (m->num < 0) {
			printf("-");
		}
		print_abs_rational(m);
		printf("x");
	}

	if (b->num > 0) {
		printf(" + ");
		print_abs_rational(b);
	} else if (b->num < 0) {
		printf(" - ");
		print_abs_rational(b);
	}

	printf("\n");
}

int main() {
	int n, i;

	if (scanf("%d", &n) != 1) {
		return 0;
	}

	for (i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		Rational m, b;

		if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4) {
			return 0;
		}

		compute_line(&x1, &y1, &x2, &y2, &m, &b);
		print_line_equation(&m, &b);
	}

	return 0;
}
