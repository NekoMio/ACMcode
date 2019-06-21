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
int F[233335], a[211986];
const int MOD = 1e9 + 7;
int main()
{
	int n = read();
	for (int i = 1; i <= n; i += 1)
	{
		a[i] = read();
	}
	int ans = 0;
	for (int i = 1; i <= n; i += 1)
	{
		int t = a[i];
		for (int k = (t - 1) & t; k; k = (k - 1) & t)
		{
			F[k] = (F[k] + F[t] + 1) % MOD;
		}
		ans = (ans + F[t]) % MOD;
	}
	printf ("%d\n", ans);
}
