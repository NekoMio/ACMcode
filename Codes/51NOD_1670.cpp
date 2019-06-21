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
const int MAXN = 100005;
int a[MAXN], Sum[MAXN];
const int MOD = 1000000007;
long long DP[MAXN];
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
int main()
{
	int n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) Sum[a[i]]++;
	for (int i = 1; i <= n; i++) Sum[i] += Sum[i - 1];
	DP[0] = 1;
	for (int i = 1; i <= n; i++) DP[0] = DP[0] * i % MOD;
	for (int i = 1; i <= n; i++)
		DP[i] = DP[i - 1] * (Sum[i - 1] - i + 1) % MOD * pow_mod(n - i + 1, MOD - 2) % MOD;
	// for (int i = 0; i <= n; i++) printf ("%lld\n", DP[i]);
	long long ans = 0;
	for (int i = 0; i <= n; i++)
	{
		ans = (ans + (DP[i] - DP[i + 1]) * i % MOD) % MOD;
	}
	printf ("%lld\n", ans);
}