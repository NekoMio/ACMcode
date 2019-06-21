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
const int MAXN = 1e5 + 5;
int prime[MAXN], mu[MAXN], cnt;
bool isnprime[MAXN];
void Get_Prime()
{
	isnprime[1] = 1, mu[1] = 1;
	for (int i = 2; i <= MAXN - 5; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt; j++)
		{
			if (i * prime[j] > MAXN - 5) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
}
int a[MAXN], t[MAXN], Min, n, Max;
int Sum[4 * MAXN];
const int MOD = 1e9 + 7;
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
int Calc(int x)
{
	int ans = 1;
	for (int i = 2; (i - 1) * x <= Max; i++)
		ans = 1ll * ans * pow_mod(i - 1, Sum[i * x - 1] - Sum[(i - 1) * x - 1]) % MOD;
	return ans;
}
int main()
{
	int T = read();
	Get_Prime();
	for (int tt = 1; tt <= T; tt++)
	{
		memset (Sum, 0, sizeof (Sum));
		Min = 0x3f3f3f3f;
		Max = 0;
		n = read();
		for (int i = 1; i <= n; i++)
		{
			a[i] = read();
			Min = min(Min, a[i]);
			Max = max(Max, a[i]);
		}
		for (int i = 1; i <= n; i++) Sum[a[i]]++;
		for (int i = 1; i <= 2 * Max + 1; i++) Sum[i] += Sum[i - 1];
		int ans = 0;
		for (int i = 2; i <= Min; i++)
			if (mu[i])
				ans = ((ans - mu[i] * Calc(i)) % MOD + MOD) % MOD;
		printf ("Case #%d: %d\n", tt, ans);
	}
}