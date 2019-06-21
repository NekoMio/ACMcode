#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Point
{
	double x, y;
}p[1005];
struct data
{
	int a, b;
	double c;
	bool operator < (const data &d) const 
	{
		return c < d.c;
	}
}d[499505];
int fa[1005];
int find(int x)
{
	if (x != fa[x]) fa[x] = find(fa[x]);
	return fa[x];
}
double dis(const Point &x, const Point &y)
{
	return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}
int main()
{
	int n = read(), m = read(), t = read();
	for (int i = 1; i <= n; i++) scanf ("%lf%lf", &p[i].x, &p[i].y);
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			d[++cnt] = (data){i, j, dis(p[i], p[j])};
	sort(d + 1, d + cnt + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= cnt; i++)
	{
		if (find(d[i].a) != find(d[i].b))
		{
			printf ("%d %d\n", d[i].a, d[i].b);
			fa[find(d[i].a)] = find(d[i].b);
		}
	}
	for (int i = n; i <= t; i++)
		printf ("%d %d\n", rand() % n + 1, rand() % n + 1);
}
