#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct data
{
	int a, b, S;
	double v;
}v[2005];
int n, m;
bool cmp(const data &a, const data &b)
{
	return a.v < b.v;
}
bool cmp1(const data &a, const data &b)
{
	return a.S < b.S;
}
bool cmp2(const data &a, const data &b)
{
	return a.S > b.S;
}
int fa[305];
int find(int x)
{
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}

double Calc(int mid)
{
	double ans = 0;
	double avg = (double)mid / (n - 1);
	for (int i = 1; i <= m; i++) v[i].v = (v[i].S - avg) * (v[i].S - avg);
	sort(v + 1, v + m + 1, cmp);
	int t = 0;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		if (find(v[i].a) != find(v[i].b))
		{
			fa[find(v[i].a)] = find(v[i].b);
			ans += v[i].v;
			t++;
			if (t == n - 1) break;
		}
	}
	return sqrt(ans / (n - 1));
}
int Kruskal(bool (*cp)(const data &a, const data &b))
{
	sort(v + 1, v + m + 1, cp);
	int ans = 0, t = 0;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		if (find(v[i].a) != find(v[i].b))
		{
			fa[find(v[i].a)] = find(v[i].b);
			ans += v[i].S;
			t++;
			if (t == n - 1) break;
		}
	}
	return ans;
}
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
		v[i].a = read(), v[i].b = read(), v[i].S = read();
	double ans = 1e300;
	int l = Kruskal(cmp1), r = Kruskal(cmp2);
	for (int i = l; i <= r; i++) ans = min(ans, Calc(i));
	printf ("%.4lf", ans);	
}
