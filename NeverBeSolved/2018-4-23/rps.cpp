#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
// double F[2][1005][1005];
int la[4] = {0, 2, 3, 1}, to[4] = {0, 3, 1, 2};
double P[1005][4];
double mem[1005][2005], *F[1005];
// A - B;
bool Judge(double t, int n)
{
	// memset (mem, 0xdd, sizeof (mem));
	for (int i = -n; i <= n; i++)
	{
		if (i < 0) F[n + 1][i] = -t;
		if (i == 0) F[n + 1][i] = 0;
		if (i > 0) F[n + 1][i] = 1;
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = 1 - i; j < i; j++)
		{
			F[i][j] = -1e60;
			for (int k = 1; k <= 3; k++)
			{
				F[i][j] = max(F[i][j], F[i + 1][j] * P[i][k] + F[i + 1][j - 1] * P[i][la[k]] + F[i + 1][j + 1] * P[i][to[k]]);
			}
			// printf ("%.5f\n", F[i][j]);
		}
	}
	return F[1][0] < 0;
}
double pow_(double x, int b)
{
	double ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * x;
		b >>= 1;
		x = x * x;
	}
	return ans;
}
int main()
{
	// freopen ("1.out", "w", stdout);
	for (int i = 0; i < 1005; i++) F[i] = &mem[i][1002];
	while (1)
	{
		int n = read(), m1 = read(), m2 = read();
		if (n == 0 && m1 == 0 && m2 == 0) break;
		for (int i = 1; i <= n; i++)
			P[i][1] = 1.0 * read() / 100, P[i][2] = 1.0 * read() / 100, P[i][3] = 1.0 * read() / 100;
		double l = 0, r = 1e6;
		while (r - l >= 1e-6)
		{
			double mid = (l + r) / 2;
			if (Judge(mid, n)) r = mid;
			else l = mid;
		}
		double p = 1 - 1 / (1 + 1 / r);
		double q = 1 - p;
		printf ("%.5f\n", (1 - pow_(p / q, m2)) / (1 - pow_(p / q, m1 + m2)));
	}
}

