// WildRage cheese T1

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
#define q(_) ((_) * (_))
struct data
{
	long long x, y, z;
}a[1005];
struct edge
{
	int END, next;
}v[2005005];
int first[1005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
bool flag = 0;
bool vis[1005];
void dfs(int rt, int E)
{
	vis[rt] = 1;
	if (rt == E)
	{
		flag = 1;
		return;
	}
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (vis[v[i].END]) continue;
		dfs(v[i].END, E);
		if (flag) return;
	}
}
int main()
{
	freopen ("2017cheese.in", "r", stdin);
	freopen ("2017cheese.out", "w", stdout);
	int T = read();
	while (T--)
	{
		memset (first, -1, sizeof (first));
		memset (vis, 0, sizeof (vis));
		p = 0;
		int n = read(), h = read(), r = read();
		for (int i = 1; i <= n; i++)
			a[i].x = read(), a[i].y = read(), a[i].z = read();
		for (int i = 1; i <= n; i++)
		{
			for (int j = i + 1; j <= n; j++)
			{
				if (4ll * r * r >= q(a[i].x - a[j].x) + q(a[i].y - a[j].y) + q(a[i].z - a[j].z))
					add(i, j), add(j, i);
			}
		}
		for (int i = 1; i <= n; i++)
		{
			if (a[i].z <= r) add(0, i);
			if (a[i].z + r >= h) add(i, n + 1);
		}
		flag = 0;
		dfs(0, n + 1);
		if (flag) printf ("Yes\n");
		else printf ("No\n");
	}
	//fclose(stdin), fclose(stdout);
	return 0;
}
