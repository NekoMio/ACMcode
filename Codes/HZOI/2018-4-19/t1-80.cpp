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
int F[6][10008], a[20], MOD;
int P[6] = {10007, 2, 3, 11, 397, 0};
long long pow_mod(long long a, int b, int p)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return ans;
}
int C(int n, int m, int id)
{
	if (n < m || m < 0 || n < 0) return 0;
	return 1ll * F[id][n] * pow_mod(1ll * F[id][m] * F[id][n - m] % P[id], P[id] - 2, P[id]) % P[id];
}
int lucas(int n, int m, int id)
{
	if (n < m || n < 0 || m < 0) return 0;
	if (m == n || m == 0) return 1;
	return 1ll * lucas(n / P[id], m / P[id], id) * C(n % P[id], m % P[id], id) % P[id];
}
int Num(unsigned int x)
{
	unsigned int tmp = x
					 - ((x >> 1) & 033333333333)
					 - ((x >> 2) & 011111111111);
	tmp = (tmp + (tmp >> 3)) & 030707070707;
	return tmp % 63;
}
long long CRT(int *a, int *b, int n)
{
    long long N = 1, Ni, now, ans = 0;
    for (int i = 0; i <= n; i++) N *= a[i];
    for (int i = 0; i <= n; i++)
    {
        Ni = N / a[i];
        now = pow_mod(Ni, a[i] - 2, a[i]);
        ans = (ans + (b[i] * now % N) * Ni % N) % N;    
    }
    return ans;
}
int b[6];
long long Calc(int n, int m)
{
	if (n < 0 || m < 0 || n < m) return 0;
	for (int i = 0; i <= 4; i++)
		b[i] = lucas(n, m, i);
	return CRT(P, b, 4);
}
int f[2][10005];
int main()
{
	int T = read();
	MOD = read();
	for (int j = 0; j <= 4; j++)
	{
		F[j][0] = 1;
		for (int i = 1; i <= 10006; i++)
			F[j][i] = 1ll * F[j][i - 1] * i % P[j];
	}
	while (T--)
	{
		int n = read(), n1 = read(), n2 = read(), m = read();
		for (int i = 1; i <= n1; i++) a[i] = read();
		for (int i = 1; i <= n2; i++) m -= (read() - 1);
		if (n <= 50 && m <= 50)
		{
			memset (f, 0, sizeof (f));
			f[0][m] = 1;
			int now = 0;
			for (int i = 1; i <= n1; i++)
			{
				now ^= 1;
				memset (f[now], 0, sizeof (f[now]));
				for (int j = 1; j <= m; j++) if (f[now ^ 1][j])
					for (int k = 1; k <= a[i]; k++) if (j - k >= 0)
						f[now][j - k] = (f[now][j - k] + f[now ^ 1][j]) % MOD;
			}
			for (int i = 1; i <= n - n1; i++)
			{
				now ^= 1;
				memset (f[now], 0, sizeof (f[now]));
				for (int j = 1; j <= m; j++) if (f[now ^ 1][j])
					for (int k = 1; k <= m; k++) if (j - k >= 0)
						f[now][j - k] = (f[now][j - k] + f[now ^ 1][j]) % MOD;
			}
			printf ("%d\n", f[now][0]);
		}
		/*
		else if (m <= 10000 && MOD == 10007)
		{
			memset (f, 0, sizeof (f));
			f[0][m] = 1;
			int now = 0;
			for (int i = 1; i <= n1; i++)
			{
				now ^= 1;
				memset (f[now], 0, sizeof (f[now]));
				for (int j = 1; j <= m; j++) if (f[now ^ 1][j])
					for (int k = 1; k <= a[i]; k++) if (j - k >= 0)
						f[now][j - k] = (f[now][j - k] + f[now ^ 1][j]) % MOD;
			}
			int ans = 0;
			for (int i = 1; i <= m; i++)
			{
				ans = (ans + 1ll * f[now][i] * C(i - 1, n - n1 - 1, 0) % MOD) % MOD;
			}
			printf ("%d\n", ans);
		}*/
		else
		{
			if (MOD == 10007)
			{
				int N = (1 << n1) - 1;
				int ans = 0;
				for (int i = 0; i <= N; i++)
				{
					int tmp = m;
					for (int j = 1; j <= n1; j++) 
						if (i & (1 << (j - 1)))
							tmp -= a[j];
					if (Num(i) & 1) ans = (ans - lucas(tmp - 1, n - 1, 0) + MOD) % MOD;
					else ans = (ans + lucas(tmp - 1, n - 1, 0)) % MOD;
				}
				printf ("%d\n", ans);
			}
			else if (MOD == 262203414)
			{
				int N = (1 << n1) - 1;
				int ans = 0;
				for (int i = 0; i <= N; i++)
				{
					int tmp = m;
					for (int j = 1; j <= n1; j++) 
						if (i & (1 << (j - 1)))
							tmp -= a[j];
					if (Num(i) & 1) ans = (ans - Calc(tmp - 1, n - 1) + MOD) % MOD;
					else ans = (ans + Calc(tmp - 1, n - 1)) % MOD;
				}
				printf ("%d\n", ans);
			}
		}
		
	}
}
