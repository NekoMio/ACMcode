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
	double k;
	int id;
	bool operator < (const Point z) const
	{
		return atan2(y, x) < atan2(z.y, z.x);
	}
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
int main()
{
	int n = read(), m = read(), t = read();
	for (int i = 1; i <= n; i++)
	{
		scanf ("%lf%lf", &p[i].x, &p[i].y);
		p[i].id = i;
	}
	sort(p + 1, p + n + 1);
	for (int i = 2; i <= n; i++)
		printf ("%d %d\n", p[i].id, p[i - 1].id);
	printf ("%d %d\n", p[n].id, p[1].id);
}
