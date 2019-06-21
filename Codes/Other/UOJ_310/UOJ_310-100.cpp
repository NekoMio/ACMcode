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
const int Inv2 = pow_mod(2, MOD - 2);
const int Inv4 = pow_mod(4, MOD - 2);
void FWT(int *a, int n)
{
	for (int j = 0; j < n; j++)
		for (int i = 0; i < (1 << n); i++)
		{
			if (i & (1 << j)) continue;
			int tmp = (a[i] + a[i + (1 << j)]) % MOD;
			a[i + (1 << j)] = (a[i] - a[i + (1 << j)] + MOD) % MOD;
			a[i] = tmp;
		}
}
void IFWT(int *a, int n)
{
	for (int j = 0; j < n; j++)
		for (int i = 0; i < (1 << n); i++)
		{
			if (i & (1 << j)) continue;
			int tmp = 1ll * (a[i] + a[i + (1 << j)]) % MOD * Inv2 % MOD;
			a[i + (1 << j)] = 1ll * (a[i] - a[i + (1 << j)] + MOD) % MOD * Inv2 % MOD;
			a[i] = tmp;
		}
}
const int MAXN = 1048577;
int a[MAXN], T[MAXN];
int main()
{
	int n = read();
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		T[a[i]] += 2;
		T[0] += 1;
	}
	FWT(T, 20);
	for (int i = 0; i < MAXN - 1; i++)
	{
		int X = (3ll * n - T[i] + MOD) * Inv4 % MOD;
		// printf ("%d\n", X);
		T[i] = (pow_mod(3, n - X) * (X & 1 ? -1 : 1) + MOD) % MOD;
		//printf ("%d\n", T[i]);
	}
	IFWT(T, 20);
	printf ("%d\n", (T[0] - 1 + MOD) % MOD);
}
