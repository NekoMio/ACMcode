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
int v[25];
int F[(1 << 20) + 1], Mx[(1 << 20) + 1];
int main()
{
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read();
		v[a] |= (1 << (b - 1));
		v[b] |= (1 << (a - 1));
	}
	v[0] |= 1;
	for (int i = 1; i <= n; i++) v[i] |= (1 << (i - 1));
	F[0] = 1;
	int N = (1 << n) - 1;
	for (int i = 1; i <= N; i++)
	{
		int tot = 0;
		for (int j = 1; j <= n; j++) if (i & (1 << (j - 1)))
		{
			int S = i & (~v[j]);
			if (Mx[i] < Mx[S] + 1) F[i] = F[S], Mx[i] = Mx[S] + 1;
			else if (Mx[i] == Mx[S] + 1) F[i] = (F[i] + F[S]) % MOD;
			tot++;
		}
		F[i] = 1ll * F[i] * pow_mod(tot, MOD - 2) % MOD;
	}
	printf ("%d\n", F[N]);
}