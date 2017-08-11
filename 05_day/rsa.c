#include <stdio.h>

int gcd(int a, int b)
{
	int r;

	if (!b)
		return a;
	while ((r = a % b) != 0) {
		a = b;
		b = r;
	}
	return b;
}
int find_e(int pi_n)
{
	int e;
	for (e = 2; ; e++)
		if (1 == gcd(e, pi_n))
			break;
	printf("e=%d\n", e);
	return e;
}
int find_d(int pi_n, int e)
{
	int a = pi_n, b = pi_n, c = e, d = 1, t;
	int old_c, old_d;

	while (c != 1)
	{
		old_c = c;
		old_d = d;
		t = a / c;
		c = a - c*t;
		d = b - d*t;
		a = old_c;
		b = old_d;
	}
	if (d < 0)
		d = pi_n + d%pi_n;
	d = d%pi_n;
	printf("d=%d\n", d);
	return d;
}

int encrypt(int data, int e, int n)
{
	int temp = 1;
	int i;
	for (i = 0; i < e; i++)
		temp = (temp*data)%n;
	
	return temp;
}

int decrypt(int data, int d, int n)
{
	int temp = 1;
	int i;
	for (i = 0; i < d; i++)
		temp = (temp*data) % n;

	return temp;
}

int main()
{
	int p = 7, q = 17;
	int n = p*q;
	int pi_n = (p - 1)*(q - 1);
	int e;
	int d;

	int data = 'a';
	int cyper;
	printf("p=%d\n", p);
	printf("q=%d\n", q);
	printf("n=%d\n", n);
	printf("pi_n=%d\n", pi_n);
	e = find_e(pi_n);
	d = find_d(pi_n, e);
	printf("평문: %d\n", data);
	cyper = encrypt(data, e, n);
	printf("암호문 : %d\n", cyper);
	data = decrypt(cyper, d, n);
	printf("평문: %d\n", data);

	return 0;
}