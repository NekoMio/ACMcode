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
int a[100005];
int F[2][16384];
int main()
{
	int n = read();
	for (int i = 0; i < n; i += 1)
		a[i] = read();
	F[0][0] = 1;
	int now = 0;
	for (int i = 0; i < n; i += 1)
	{
		now ^= 1;
		memset (F[now], 0, sizeof (F[now]));
		for (int j = 0; j <= 16383; j++)
			F[now][j] = (F[now][j] + F[now ^ 1][j ^ a[i]] * 2 % MOD) % MOD;
		for (int j = 0; j <= 16383; j++)
			F[now][j] = (F[now][j] + F[now ^ 1][j]) % MOD;
	}
	printf ("%d\n", F[now][0] - 1);
}
