#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MOD = 998244353;
int pow_mod(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
int n, K;
int F[30005], B[500005];
long long C(int n, int m)
{
	if (n < m) return 0;
	return 1ll * F[n] * pow_mod(1ll * F[m] * F[n - m] % MOD, MOD - 2) % MOD;
}
int N, rev[500005];
int Inv;
void Init(int n)
{
	N = 1;
	while (N < (n << 1)) N <<= 1;
	Inv = pow_mod(N, MOD - 2);
	for (int i = 1; i < N; i++)
		if (i & 1)
			rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
		else
			rev[i] = (rev[i >> 1] >> 1);
}
void FFT(int *a, int op)
{
	int wn, w, t;
	for (int i = 1; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int k = 2; k <= N; k <<= 1)
	{
		wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
		for (int j = 0; j < N; j += k)
		{
			w = 1;
			for (int i = 0; i < (k >> 1); i++, w = 1ll * w * wn % MOD)
			{
				t = 1ll * a[i + j + (k >> 1)] * w % MOD;
				a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
				a[i + j] = (a[i + j] + t) % MOD;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i < N; i++)
			a[i] = 1ll * a[i] * Inv % MOD;
}
int f[2][500005];
int g[25];
int S[25][25];
void DP()
{
	f[0][0] = 1;
	g[0] = 1;
	int now = 0;
	Init(n);
	FFT(B, 1);
	for (int i = 1; i <= K; i++)
	{
		now ^= 1;
		memset(f[now], 0, sizeof (f[now]));
		// for (int j = 1; j <= n; j++) printf ("%d ", f[now][j]);
		// printf ("\n");
		for (int j = 0; j <= n; j++) f[now ^ 1][j] = 1ll * f[now ^ 1][j] * pow_mod(F[j], MOD - 2) % MOD;
		for (int j = n + 1; j < N; j++) f[now ^ 1][j] = 0;
		FFT(f[now ^ 1], 1);
		for (int j = 0; j < N; j++) f[now][j] = 1ll * f[now ^ 1][j] * B[j] % MOD;
		FFT(f[now], -1);
		for (int j = 1; j <= n; j++)
		{
			f[now][j] = 1ll * f[now][j] * F[j - 1] % MOD;
			g[i] = (g[i] + C(n, j) * f[now][j] % MOD * pow_mod(2, (n - j) * (n - j - 1) / 2) % MOD) % MOD;
		}
	}
}
signed main()
{
	n = read(), K = read();
	F[0] = 1;
	for (int i = 1; i <= 30000; i++) F[i] = 1ll * F[i - 1] * i % MOD;
	B[1] = 1;
	for (int i = 2; i <= n; i++) B[i] = 1ll * pow_mod(i, i - 2) * pow_mod(F[i - 1], MOD - 2) % MOD;
	int ans = 0;
	DP();
	S[1][1] = 1;
	for (int i = 2; i <= K; i++)
		for (int j = 1; j <= i; j++)
			S[i][j] = (S[i - 1][j - 1] + 1ll * j * S[i - 1][j] % MOD) % MOD;
	for (int i = 1; i <= K; i++)
		ans = (ans + 1ll * g[i] * F[i] % MOD * S[K][i] % MOD) % MOD;
	printf ("%d\n", ans);
	// while (1);
}
