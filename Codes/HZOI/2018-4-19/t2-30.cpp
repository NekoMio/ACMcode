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
const int MAXN = 262145;
const int MOD = 10007;
const int Inv2 = 5004;
void FWT(int *a, int n)
{
	for (int k = 1; k < (1 << n); k <<= 1)
		for (int i = 0; i < (1 << n); i++)
		{
			if (i & k) continue;
			int tmp = (a[i] + a[i + k]) % MOD;
			a[i + k] = (a[i] - a[i + k] + MOD) % MOD;
			a[i] = tmp;
		}
}
void IFWT(int *a, int n)
{
	for (int k = 1; k < (1 << n); k <<= 1)
		for (int i = 0; i < (1 << n); i++)
		{
			if (i & k) continue;
			int tmp = (a[i] + a[i + k]) % MOD * Inv2 % MOD;
			a[i + k] = (a[i] - a[i + k] + MOD) % MOD * Inv2 % MOD;
			a[i] = tmp;
		}
}
int a[2][MAXN];
int main()
{
	int n = read(), p = read(), j = read();
	int m = (1 << n) - 1;
	for (int i = 0; i <= m; i++)
	{
		a[0][i] = read();
	}
	int Sum = a[0][j];
	int now = 0;
	for (int i = 1; i <= p; i++)
	{
		now ^= 1;
		memset (a[now], 0, sizeof (a[now]));
		FWT(a[now ^ 1], n);
		for (int k = 0; k <= m; k++)
			a[now][k] = 1ll * a[now ^ 1][k] * a[now ^ 1][k] % MOD;
		IFWT(a[now], n);
		// printf ("%d\n", a[now][j]);
		Sum = (Sum + a[now][j]) % MOD;
	}
	printf ("%d\n", Sum);
}
