#pragma GCC optimize("O2")
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
const int MAXN = 16;
int f[MAXN], m, n;
inline bool Judge(int *b, int *c)
{
	int t = 1;
	for (int i = 1; i <= n; i++)
		if (b[i] == c[t])
			t++;
	if (t != m + 1) return 0;
	memset (f, 0, sizeof (f));
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		f[i] = 1;
		for (int j = 1; j < i; j++)
			if (b[j] < b[i] && f[i] < f[j] + 1)
				f[i] = f[j] + 1;
		if (f[i] > ans) ans = f[i];
	}
	return ans == m;
}
int a[MAXN], b[MAXN], ans;
bool vis[MAXN];
void DFS(int x, int y)
{
	if (n - x < m - y) return;
	if (x == n + 1)
	{
		if (Judge(b, a)) ans++;
		return;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i] && (y > m || i < a[y - 1] || i > a[y]))
		{
			vis[i] = 1, b[x] = i;
			DFS(x + 1, y);
			vis[i] = 0;
		}
	if (y <= m && !vis[a[y]]) vis[a[y]] = 1, b[x] = a[y], DFS(x + 1, y + 1), vis[a[y]] = 0;
}
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
		a[i] = read();
	DFS(1, 1);
	printf ("%d\n", ans);
}