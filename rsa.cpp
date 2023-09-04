#include<iostream>
#include<gmp.h>

#define ll unsigned long long

char *readLine(FILE *file)
{
	char *line = NULL;
	size_t n = 0;
	if (getline(&line, &n, file) == -1)
	{
		free(line);
		return NULL;
	}
	return line;
}
void f(mpz_t x, ll c, mpz_t mod)
{
	mpz_mul(x, x, x);
	mpz_add_ui(x, x, c);
	mpz_mod(x, x, mod);
}

void rho(char *num, ll x0, ll c)
{
	
	mpz_t x, g, p, xs, y, n, sub;

	mpz_init_set_ui(x, x0);
	mpz_init_set_ui(g, 1);
	mpz_init_set_ui(p, 1);
	mpz_init_set_str(n, num, 10);
	mpz_init(xs);
	mpz_init(y);
	mpz_init(sub);

	ll m = 128, l = 1;
	while (mpz_cmp_ui(g, 1) == 0)
	{
		mpz_set(y, x);
		for (ll i = 1; i < l; i++)
			f(x, c, n);
		ll k = 0;
		while (k < l && mpz_cmp_ui(g, 1) == 0)
		{
			mpz_set(xs, x);
			for (ll i = 0; i < m && i < l - k; i++)
			{
				f(x, c, n);
				mpz_sub(sub, x, y);
				mpz_abs(sub, sub);
				mpz_mul(p, p, sub);
				mpz_mod(p, p, n);
			}
			mpz_gcd(g, p, n);
			k += m;
		}
		l <<= 1;
		if (mpz_cmp(g, n) == 0)
		{
			do {
				f(xs, c, n);
				mpz_sub(sub, xs, y);
				mpz_abs(sub, sub);
				mpz_gcd(g, sub, n);
			} while (mpz_cmp_ui(g, 1) == 0);

			if (mpz_cmp(g, n) == 0)
			{
				mpz_add_ui(x, x, 1);
				mpz_set_ui(g, 1);
			}
		}
	}

	mpz_out_str(stdout, 10, n);
	printf("=");
	mpz_out_str(stdout, 10, g);
	printf("*");
	mpz_divexact(n, n, g);
	mpz_out_str(stdout, 10, n);
	printf("\n");

	mpz_clear(x); mpz_clear(g); mpz_clear(p); mpz_clear(xs);
	mpz_clear(y); mpz_clear(n); mpz_clear(sub);
}
int main (int argc, char **argv) {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char *num = NULL;
	FILE *file;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: factors file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		num = readLine(file);
		if (num == NULL)
			break;
		rho(num, 2, 1);
		free(num);
	}
	fclose(file);
	return 0;
}
