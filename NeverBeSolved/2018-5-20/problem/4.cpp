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
int fa[1005], Size[1005];
int find(int x)
{
	if (x != fa[x]) fa[x] = find(fa[x]);
	return fa[x];
}
double dis(const Point &x, const Point &y)
{
	return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}
vector<int> vc[1005];
int main()
{
	int n = read(), m = read(), t = read();
	for (int i = 1; i <= n; i++) scanf ("%lf%lf", &p[i].x, &p[i].y);
	int cnt = 0;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int a = read(), b = read();
		if (find(a) != find(b))
			fa[find(a)] = find(b);
	}
	for (int i = 1; i <= n; i++)
		vc[find(i)].push_back(i);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) if (vc[i].size())
	{
		cnt = 0;
		for (auto z : vc[i])
			for (auto x : vc[i])
				d[++cnt] = (data){z, x, dis(p[z], p[x])};
		sort(d + 1, d + cnt + 1);
		for (int i = 1; i <= cnt; i++)
		{
			if (find(d[i].a) != find(d[i].b))
			{
				printf ("%d %d\n", d[i].a, d[i].b);
				fa[find(d[i].a)] = find(d[i].b);
			}
		}
	}
	// sort(d + 1, d + cnt + 1);
	// for (int i = 1; i <= n; i++) fa[i] = i;
	// for (int i = 1; i <= cnt; i++)
	// {
	//	if (find(d[i].a) != find(d[i].b))
	//	{
	//		printf ("%d %d\n", d[i].a, d[i].b);
	//		fa[find(d[i].a)] = find(d[i].b);
	//	}
	//}
}
