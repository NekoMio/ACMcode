#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MOD = 1e9 + 7;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a[350];
int x[305];
long long f[305];
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
priority_queue<int, vector<int>, greater<int> > Q;
int main()
{
	//freopen ("strategy.in", "r", stdin);
	//freopen ("strategy.out", "w", stdout);
	int n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	if (n <= 10)
	{
		int N = 1;
		for (int i = 1; i <= n; i++)
			x[i] = i, N = N * i;
		long long ans = 0;
		for (int t = 1; t <= N; t++)
		{
			for (int i = 1; i <= k; i++) Q.push(a[x[i]]);
			int Sum = 0;
			for (int i = k + 1; i <= n; i++)
			{
				Sum = (Sum + Q.top()) % MOD, Q.pop();
				ans = (ans + Sum) % MOD;
				Q.push(a[x[i]]);
			}
			while (!Q.empty())
			{
				Sum = (Sum + Q.top()) % MOD, Q.pop();
				ans = (ans + Sum) % MOD;
			}
			next_permutation(x + 1, x + n + 1);
		}
		printf ("%lld\n", ans * pow_mod(N, MOD - 2) % MOD);
	}
	else if (k == 1)
	{
		f[0] = 1;
		for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % MOD;
		long long ans = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int k = 1; k <= n; k++)
			{
				for (int j = 1; j <= n; j++)
				{
					if (j == i) continue;
					ans = (ans + (k - 1) * a[j] * f[n - 2] % MOD) % MOD;
				}
			}
		}
		ans = ans * pow_mod(f[n], MOD - 2) % MOD;
		for (int i = 1; i <= n; i++)
			ans = (ans + a[i]) % MOD;
		printf ("%lld\n", ans);
	}
}
