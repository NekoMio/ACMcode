#include <cstdio>
#include <cstring>
#include <algorithm>

int MOD;
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while(b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}

const int MAXN = 100005;
long long f[MAXN];

int main()
{
	freopen ("color.in", "r", stdin);
	freopen ("color.out", "w", stdout);
	int n = read(), m = read();
	MOD = read();
	f[1] = 1ll * m * (m - 1) % MOD;
	long long base = (1ll * (m - 2) * (m - 2) % MOD + (m - 1)) % MOD;
	long long ans = f[1] * pow_mod(2, m) % MOD;
	for (int i = 2; i <= n; i++)
	{
		f[i] = f[i - 1] * base % MOD;
		ans = (ans + f[i] * pow_mod(2 * i, m) % MOD) % MOD;
	}
	printf ("%lld", ans);
}