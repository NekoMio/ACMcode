#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const long long INF = 0x3f3f3f3f3f3f3f3f;
struct edge
{
	int END, next;
	long long cap;
}v[20005];
int first[105], p;
void add(int a, int b, long long f)
{
	v[p].END = b, v[p].next = first[a], v[p].cap = f, first[a] = p++;
	v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++;
}
int dis[105];
bool BFS(int S, int E)
{
	memset (dis, -1, sizeof (dis));
	queue<int> Q;
	Q.push(S);
	dis[S] = 0;
	while (!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] == -1 && v[i].cap)
			{
				dis[v[i].END] = dis[k] + 1;
				if (v[i].END == E) return 1;
				Q.push(v[i].END);
			}
		}
	}
	return 0;
}
long long DFS(int S, int E, long long a)
{
	if (S == E || a == 0) return a;
	long long flow = 0, f;
	for (int i = first[S]; i != -1; i = v[i].next)
	{
		if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
		{
			flow += f;
			a -= f;
			v[i].cap -= f;
			v[i ^ 1].cap += f;
			if (a == 0) break;
		}
	}
	if (!flow) dis[S] = -1;
	return flow;
}
long long Dinic(int S, int T)
{
	long long ans = 0;
	while (BFS(S, T))
	{
		ans += DFS(S, T, INF);
		if (ans >= INF) return -1;
	}
	return ans;
}
struct data
{
	int a, b;
}tt[2505];
bool v1[105], v2[105];
int main()
{
	memset (first, -1, sizeof (first));
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int a = read() + 1, b = read() + 1, c = read();
		tt[i].a = a, tt[i].b = b;
		add(a, b, c);
		// add(b, a, INF);
	}
	BFS(1, 0);
	for (int i = 1; i <= n; i++)
		v1[i] = (dis[i] != -1);
	for (int i = 1; i <= n; i++)		
		v2[i] = BFS(i, n);
	for (int i = 1; i <= m; i++)
		if (v1[tt[i].a] && v2[tt[i].b])
			add(tt[i].b, tt[i].a, INF);
	printf ("%lld\n", Dinic(1, n));
}
