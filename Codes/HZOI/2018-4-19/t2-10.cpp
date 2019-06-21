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
int Num(unsigned int x)
{
	unsigned int tmp = x
					 - ((x >> 1) & 033333333333)
					 - ((x >> 2) & 011111111111);
	tmp = (tmp + (tmp >> 3)) & 030707070707;
	return tmp % 63;
}
const int MAXN = 262145;
const int MOD = 10007;
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
		for (int k = 0; k <= m; k++)
		{
			for (int l = 0; l <= m; l++)
				(a[now][k] += 1ll * a[now ^ 1][l] * a[now ^ 1][l ^ k] % MOD) %= MOD;
		}
		Sum = (Sum + a[now][j]) % MOD;
	}
	printf ("%d\n", Sum);
}

