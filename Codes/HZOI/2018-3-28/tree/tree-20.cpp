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
const int MAXN = 70005;
struct edge
{
	int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
long long dis[MAXN], ans;
void DFS(int rt, int fa, int L, int R)
{
	if (L <= rt && R >= rt) ans += dis[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dis[v[i].END] = dis[rt] + v[i].v;
		DFS(v[i].END, rt, L, R);
	}
}
char op[10];
int main()
{
	memset (first, -1, sizeof (first));
	int n = read(), m = read(), type = read();
	for (int i = 1; i <= n - 1; i++)
	{
		int a = read(), b = read(), c = read();
		add(a, b, c);
		add(b, a, c);
	}
	long long lastans = 0;
	while (m--)
	{
		lastans *= type;
		scanf("%s", op);
		// int op = read();
		if (op[0] == 'm')
		{
			int x = read() ^ lastans, y = read() ^ lastans;
			v[(x - 1) << 1].v = y, v[(x - 1) << 1 | 1].v = y;
		}
		else
		{
			int L = read() ^ lastans, R = read() ^ lastans, x = read() ^ lastans;
			ans = 0, dis[x] = 0;
			DFS(x, 0, L, R);
			printf ("%lld\n", lastans = ans);
			lastans %= n;
		}
	}
}