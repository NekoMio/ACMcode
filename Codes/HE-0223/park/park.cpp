#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
const int N = 100005;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct edge
{
	int END, next, v;
}v[N << 2], e[N << 2];
int first[N], p, Fanfirst[N];
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].v = c;
	v[p].next = first[a];
	e[p].END = a;
	e[p].v = c;
	e[p].next = Fanfirst[b];
	Fanfirst[b] = p;
	first[a] = p++;
}
int K, P, n, m;
bool ZeroRound;
int dis[N];
bool flag[N];
struct data
{
	int x, v;
	data(int a, int b)
	{
		x = a, v = b;
	}
};
queue<int> q;
bool Spfa(int x)
{
	memset(dis, 0x3f, sizeof (dis));
	memset(flag, 0, sizeof (flag));
	dis[x] = 0;
	flag[x] = 1;
	q.push(x);
	while (!q.empty())
	{
		int k = q.front();
		q.pop();
		flag[k] = 0;
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] > dis[k] + v[i].v)
			{
				dis[v[i].END] = dis[k] + v[i].v;
				if (!flag[v[i].END])
				{
					flag[v[i].END] = 1;
					q.push(v[i].END);
				}
			}
		}
	}
	return 0;
}
long long f[N][55];
bool vis[N][55];
long long DFS(int rt, int t)
{
	if (~f[rt][t]) return f[rt][t];
	f[rt][t] = 0;
	vis[rt][t] = 1;
	for (int i = Fanfirst[rt]; i != -1; i = e[i].next)
	{
		int nxt = dis[rt] - dis[e[i].END] + t - e[i].v;
		if (nxt < 0) continue;
		if (vis[e[i].END][nxt]) ZeroRound = 1;
		(f[rt][t] += DFS(e[i].END, nxt)) %= P;
	}
	vis[rt][t] = 0;
	return f[rt][t];
}
int main()
{
	freopen("2017park.in", "r", stdin);
	freopen("2017park.out", "w", stdout);
	int T = read();
	while (T--)
	{
		n = read(), m = read();
		K = read(), P = read();
		memset (first, -1, sizeof (first));
		memset (Fanfirst, -1, sizeof (Fanfirst));
		memset (f, -1, sizeof(f));
		p = 0;
		int a, b, c;
		for (int i = 1; i <= m; i++)
		{
			a = read(), b = read(), c = read();
			add(a, b, c);
		}
		Spfa(1);
		long long ans = 0;
		ZeroRound = 0;
		f[1][0] = 1;
		for (int i = 0; i <= K; i++) (ans += DFS(n, i)) %= P;
		DFS(n, K + 1);
		if (ZeroRound) puts("-1");
		else printf ("%lld\n", ans);
	}
	//fclose(stdin), fclose(stdout);
	return 0;
}
