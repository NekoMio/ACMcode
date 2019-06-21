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
long long q[5005], p[5005];
long long f[2][5005];
int main()
{
	freopen("kill.in", "r", stdin);
	freopen("kill.out", "w", stdout);
	long long n = read(), m = read(), s = read();
	for (int i = 1; i <= n; i++)
		p[i] = read();
	for (int i = 1; i <= m; i++)
		q[i] = read();
	sort(p + 1, p + n + 1);
	sort(q + 1, q + m + 1);
	int now = 0;
	for (int i = 1; i <= n; i++) f[now][i] = 0x3f3f3f3f3f3f3f3fll;
	for (int i = 1; i <= m; i++)
	{
		now ^= 1;
		for (int j = 1; j <= n; j++) f[now][j] = 0x3f3f3f3f3f3f3f3fll;
		for (int j = 1; j <= i && j <= n; j++)
		{
			f[now][j] = max(f[now ^ 1][j - 1], abs(p[j] - q[i]) + abs(q[i] - s));
			f[now][j] = min(f[now][j], f[now ^ 1][j]);

		}
	}
	printf ("%lld", f[now][n]);
	fclose(stdin), fclose(stdout);
	return 0;
}
