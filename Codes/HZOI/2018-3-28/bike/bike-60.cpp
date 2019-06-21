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
long long f[MAXN][21], g[1005][1005], S[1005][1005], Sum[1005][1005];
long long Calc(int L, int R)
{
	int ll = L, rr = R, ans = 0;
	while (ll <= rr)
	{
		int mid = ll + rr >> 1;
		if (S[L][mid] >= S[R][mid]) ans = mid, rr = mid - 1;
		else ll = mid + 1;
	}
	return Sum[L][ans - 1] + Sum[R][ans];
}
int main()
{
	// freopen ("bike_example_3.in", "r", stdin);
	// freopen("12.txt", "w", stdout);
	int n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i < n; i++)
		l[i] = read();
	for (int i = 1; i <= n; i++)
	{
		for (int j = i - 1; j >= 1; j--)
		{
			S[i][j] = S[i][j + 1] + l[j];
			Sum[i][j] = Sum[i][j + 1] + S[i][j] * a[j];
		}
		for (int j = i + 1; j <= n; j++)
		{
			S[i][j] = S[i][j - 1] + l[j - 1];
			Sum[i][j] = Sum[i][j - 1] + S[i][j] * a[j];
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			g[i][j] = Calc(i, j);
	for (int i = 1; i <= n; i++)
		g[0][i] = Sum[i][1];
	for (int i = 1; i <= n; i++)
		g[i][n + 1] = Sum[i][n];
	memset (f, 0x3f, sizeof (f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i && j <= k; j++)
			for (int m = 0; m < i; m++)
				f[i][j] = min(f[i][j], f[m][j - 1] + g[m][i]);
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[i][k] + g[i][n + 1]);
	printf ("%lld\n", ans);
}