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
int Pos[40005], b[40005], C[40005];
int n, k, m;
struct edge
{
	int END, next, v;
}v[40005 * 64 * 2];
int first[40005], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
int id[40005], Index;
int d[50][50], dis[40005];
queue<int> Q;
bool vis[40005];
void Spfa(int x)
{
	memset (dis, 0x3f, sizeof (dis));
	memset (vis, 0, sizeof (vis));
	Q.push(x);
	dis[x] = 0;
	vis[x] = 1;
	while (!Q.empty())
	{
		int rt = Q.front();
		Q.pop();
		vis[rt] = 0;
		for (int i = first[rt]; i != -1; i = v[i].next)
		{
			if (dis[v[i].END] > dis[rt] + 1)
			{
				dis[v[i].END] = dis[rt] + 1;
				if (!vis[v[i].END])
				{
					vis[v[i].END] = 1;
					Q.push(v[i].END);
				}
			}
		}
	}
}
int f[65539];
int main()
{
	// freopen("starlit.in", "r", stdin);
	// freopen("starlit.out", "w", stdout);
	n = read(), k = read(), m = read();
	// for (int i = 1; i <= n; i++) Pos[i] = 1;
	memset (first, -1, sizeof (first));
	for (int i = 1; i <= k; i++)
		Pos[read()] = 1;
	for (int i = 1; i <= m; i++)
		b[i] = read();
	for (int i = 0; i <= n; i++) C[i] = Pos[i] ^ Pos[i + 1];
//	for (int i = 0; i <= n; i++) {
//		printf ("%d ", C[i]);
//	}
//	printf("\n");
	for (int i = 0; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (i - b[j] >= 0) add(i, i - b[j], 1);
			if (i + b[j] <= n) add(i, i + b[j], 1);
		}
	}
//	printf("1\n");
	for (int i = 0; i <= n; i++)
		if (C[i] == 1)
			id[i] = ++Index;
	memset (vis, -1, sizeof (vis));
	for (int i = 0; i <= n; i++)
	{
		if (C[i] == 1)
		{
			Spfa(i);
			for (int j = 0; j <= n; j++)
				if (C[j] == 1 && i != j)
					d[id[i]][id[j]] = dis[j];
		}
	}
	memset (f, 0x3f, sizeof (f));
	f[0] = 0;
	int N = (1 << Index) - 1;
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j < Index; j++)
		{
			if ((1 << j) & i) continue;
			for (int l = 0; l < Index; l++)
			{
				if (l == j) continue;
				if (((1 << l) & i)) continue;
				f[i ^ (1 << j) ^ (1 << l)] = min(f[i ^ (1 << j) ^ (1 << l)], f[i] + d[l + 1][j + 1]);
			}
		}
	}
	printf ("%d\n", f[N]);
}
