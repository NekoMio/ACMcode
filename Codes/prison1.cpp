#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct edge
{
	int a, b, c;
	bool operator < (const edge &d) const
	{
		return c > d.c; 
	}
}a[100005];
int fa[50005];
int find(int x)
{
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
	freopen("prison1.in", "r", stdin);
	freopen("prison1.out", "w", stdout);
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
		a[i].a = read(), a[i].b = read(), a[i].c =read();
	sort(a + 1, a + m + 1);
	for (int i = 1; i <= 2 * n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		if (find(a[i].a) == find(a[i].b))
		{
			printf ("%d", a[i].c);
			return 0;
		}
		fa[find(a[i].a)] = find(a[i].b + n);
		fa[find(a[i].b)] = find(a[i].a + n);
	}
	printf ("0");
}
