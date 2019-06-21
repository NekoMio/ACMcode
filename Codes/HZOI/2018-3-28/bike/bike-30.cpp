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
const int MAXN = 50005;
int a[MAXN], l[MAXN];
long long f[MAXN][21];
long long dis[MAXN];
int n, k;
long long Calc(int L, int r)
{
	if (L == 0)
	{
		long long ans = 0, len = 0;
		for (int i = r - 1; i >= 1; i--)
			len += l[i], ans += len * a[i];
		return ans;
	}
	else if (r == n + 1)
	{
		long long ans = 0, len = 0;
		for (int i = L + 1; i <= n; i++)
			len += l[i - 1], ans += len * a[i];
		return ans;
	}
	else
	{
		long long ans = 0, len = 0;
		dis[L] = 0;
		for (int i = L + 1; i <= r; i++)
			dis[i] = dis[i - 1] + l[i - 1];
		for (int i = r - 1; i >= L; i--)
			if (len + l[i] < dis[i])
				len += l[i], ans += len * a[i];
			else
				len += l[i], ans += dis[i] * a[i];
		return ans;
	}
}
int main()
{
	n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n - 1; i++)
		l[i] = read();
	memset (f, 0x3f, sizeof (f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i && j <= k; j++)
			for (int m = 0; m < i; m++)
				f[i][j] = min(f[i][j], f[m][j - 1] + Calc(m, i));
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[i][k] + Calc(i, n + 1));
	printf ("%lld\n", ans);
}