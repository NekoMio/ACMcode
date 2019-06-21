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
const int MOD = 998244353;
int v[25], w[25];
long long F[(1 << 15) + 1];
long long pow_mod(long long a, int b)
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
int Num(unsigned int x)
{
	unsigned int tmp = x
					 - ((x >> 1) & 033333333333)
					 - ((x >> 2) & 011111111111);
	tmp = (tmp + (tmp >> 3)) & 030707070707;
	return tmp % 63;
}
int n, m, p;
bool vis[25];
void DFS(int rt, int S)
{
	vis[rt] = 1;
	for (int i = 1; i <= n; i++)
		if ((S & (1 << (i - 1))) && (v[rt] & (1 << (i - 1))) && (!vis[i]))
			DFS(i, S);
}
bool OK(int S)
{
	memset (vis, 0, sizeof (vis));
	int h = 0;
	for (int i = 1; i <= n; i++)
		if (S & (1 << (i - 1))) { h = i; break; }
	DFS(h, S);
	for (int i = 1; i <= n; i++)
		if ((S & (1 << (i - 1))) && !vis[i])
			return 0;
	return 1;
}
int Judge(int S)
{
	bool ok = 1;
	int ans = 0;
	if (Num(S) == 1) return 0;
	for (int i = 1; i <= n; i += 1)
	{
		if (S & (1 << (i - 1)))
		{
			if (Num(S & v[i]) & 1)
			{
				ok = 0;
				// break;
			}
			ans += w[i];
		}
	}
	if (ok == 1 && OK(S)) return 0;
	else return ans;
}
int main()
{
	n = read(), m = read(), p = read();
	for (int i = 0; i < m; i += 1)
	{
		int a = read(), b = read();
		v[a] |= (1 << (b - 1));
		v[b] |= (1 << (a - 1));
	}
	for (int i = 1; i <= n; i += 1)
		w[i] = read();
	// fprintf (stderr, "-------");
	F[0] = 1;
	int N = (1 << n) - 1;
	for (int i = 1; i <= N; i += 1)
	{
		int S = 0;
		for (int k = 1; k <= n; k++) if (i & (1 << (k - 1))) S += w[k];
		for (int j = i; ; j = (j - 1) & i)
		{
			int t = j ^ i, W;
			if (W = Judge(t))
			{
				// printf ("%d %d\n", t, j);
				(F[i] += F[j] * pow_mod(W * pow_mod(S, MOD - 2) % MOD, p) % MOD) %= MOD;
			}
			if (!j) break;
		}
		// fprintf (stderr, "%d %d\n", i, F[i]);
	}
	printf ("%lld\n", F[N]);
}
