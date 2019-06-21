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

int a[405][405], Sum[405][405];
int Num[1000005];
int main()
{
	freopen("rally.in", "r", stdin);
	freopen("rally.out", "w", stdout);
	int n = read(), m = read(), MOD = read();
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			a[i][j] = read();
			if(a[i][j] == MOD) a[i][j] = 0;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			Sum[i][j] = (Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1] + a[i][j] + MOD) % MOD;
	for (int i = 1; i <= n; i++)
	{
		for (int k = 0; k < i; k++)
		{
			Num[0] = 1;
			for (int j = 1; j <= m; j++)
			{
				ans += Num[(Sum[i][j] - Sum[k][j] + MOD) % MOD];
				Num[(Sum[i][j] - Sum[k][j] + MOD) % MOD]++;
			}
			for (int j = 1; j <= m; j++)
			{
				Num[(Sum[i][j] - Sum[k][j] + MOD) % MOD]--;
			}
		}
	}
	printf ("%lld\n", ans);
}
