#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 1e6;
int prime[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
void Get_Prime()
{
	isnprime[1] = 1;
	for (int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt; j++)
		{
			if (i * prime[j] > MAXN) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
				break;
		}
	}
}
long long val[MAXN + 1], g[MAXN + 1], p[MAXN + 1], q[MAXN + 1];
long long f[MAXN + 1], Num[MAXN + 1];
#define pos(_) ((_) < MAXN ? p[(_)] : q[n / (_)])
long long Solve(long long n)
{
	int m = 0;
	for (long long i = 1; i <= n; i = (n / (n / i)) + 1) val[++m] = n / i;
	for (int i = 1; i <= m; i++) if (val[i] < MAXN) p[val[i]] = i; else q[n / val[i]] = i;
	for (int i = 1; i <= m; i++) g[i] = val[i] - 1;
	for (int i = 1; i <= cnt; i++)
	{
		long long t = 1ll * prime[i] * prime[i];
		if (t > n) break;
		for (int j = 1; val[j] >= t; j++) g[j] -= g[pos(val[j] / prime[i])] - (i - 1);
	}
	long long ans = 0;
	memset (f, 0, sizeof (f));
	memset (Num, 0, sizeof (Num));
	Num[1] = 1;
	for (int i = 1, h = m; i <= cnt; i++)
	{
		long long t = 1ll * prime[i] * prime[i];
		for (; h && val[h] < t; h--)
		{
			ans += f[h] * (g[h] - (i - 1));
			// printf ("%d ", f[h]);
		}
		// printf ("\n");
		if (!h) break;
		for (int j = 1; j <= h; j++)
		{
			int nxt = pos(val[j] / prime[i]);
			f[nxt] += prime[i] * Num[j];
			Num[nxt] += Num[j];
			if (nxt > h) ans += prime[i] * Num[j] * (g[nxt] - (i - 1));
			ans += f[j];
		}
		// printf ("%d\n", ans);
	}
	return ans;
}
int main()
{
	// freopen ("1.out", "w", stdout);
	long long l = read(), r = read();
	Get_Prime();
	printf ("%lld\n", Solve(r) - Solve(l - 1));
}
