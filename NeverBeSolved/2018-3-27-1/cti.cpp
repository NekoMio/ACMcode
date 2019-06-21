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
const int INF = 0x3f3f3f3f;
const int MAXM = 1000005;
const int MAXN = 5005;
struct edge
{
	int END, next, cap;
}v[MAXM];
int first[MAXN], p;
void add(int a, int b, int f)
{
	v[p].END = b, v[p].next = first[a], v[p].cap = f, first[a] = p++;
	v[p].END = a, v[p].next = first[b], v[p].cap = 0, first[b] = p++; 
}
int dis[MAXN], Q[MAXN];
bool BFS(int S, int E)
{
	memset (dis, -1, sizeof (dis));
	dis[S] = 1;
	int l = 1, r = 0;
	Q[++r] = S;
	while (l <= r)
	{
		int k = Q[l++];
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] == -1 && v[i].cap > 0)
			{
				dis[v[i].END] = dis[k] + 1;
				Q[++r] = v[i].END;
				if (v[i].END == E) return 1;
			}
		}
	}
	return 0;
}
int DFS(int S, int E, int a)
{
	if (S == E || a == 0) return a;
	int flow = 0, f;
	for (int i = first[S]; i != -1; i = v[i].next)
	{
		if (dis[v[i].END] == dis[S] + 1 && (f = DFS(v[i].END, E, min(a, v[i].cap))) > 0)
		{
			v[i].cap -= f;
			v[i ^ 1].cap += f;
			flow += f;
			a -= f;
			if (a == 0) break;
		}
	}
	if (!flow) dis[S] = -1;
	return flow;
}
int Dinic(int S, int E)
{
	int ans = 0;
	while (BFS(S, E))
		ans += DFS(S, E, INF);
	return ans;
}
int a[55][55], id[2][55][55];
int main()
{
	memset (first, -1, sizeof (first));
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = read();
	int Index = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			id[0][i][j] = ++Index, id[1][i][j] = ++Index;
	int S = ++Index, T = ++Index;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			add(id[0][i][j], id[1][i][j], INF);
			if (a[i][j] == -1)
			{
				add(S, id[0][i][j], INF);
				int Max = 0;
				for (int k = i - 1; k >= 1; k--)
					Max = max(Max, a[k][j]);
				for (int k = i - 1; k >= 1; k--)
					add(id[0][k + 1][j], id[0][k][j], Max - (a[k + 1][j] > 0 ? a[k + 1][j] : 0));
				ans += Max;
			}
			else if (a[i][j] == -2)
			{
				add(S, id[0][i][j], INF);
				int Max = 0;
				for (int k = i + 1; k <= n; k++)
					Max = max(Max, a[k][j]);
				for (int k = i + 1; k <= n; k++)
					add(id[0][k - 1][j], id[0][k][j], Max - (a[k - 1][j] > 0 ? a[k - 1][j] : 0));
				ans += Max;
			}
			else if (a[i][j] == -3)
			{
				add(id[1][i][j], T, INF);
				int Max = 0;
				for (int k = j - 1; k >= 1; k--)
					Max = max(Max, a[i][k]);
				for (int k = j - 1; k >= 1; k--)
					add(id[1][i][k], id[1][i][k + 1], Max - (a[i][k + 1] > 0 ? a[i][k + 1] : 0));
				ans += Max;
			}
			else if (a[i][j] == -4)
			{
				add(id[1][i][j], T, INF);
				int Max = 0;
				for (int k = j + 1; k <= m; k++)
					Max = max(Max, a[i][k]);
				for (int k = j + 1; k <= m; k++)
					add(id[1][i][k], id[1][i][k - 1], Max - (a[i][k - 1] > 0 ? a[i][k - 1] : 0));
				ans += Max;
			}
		}
	}
	printf ("%d\n", ans - Dinic(S, T));
}