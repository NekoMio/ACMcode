#include <bits/stdc++.h>
// #include <queue>
using namespace std;
struct Point
{
	double x, y;
}P[1005];
struct data
{
	int a, b;
	double c;
}d[1005 * 1005];
struct Query
{
	int a, b;
}c[1005 * 1005];
double Dis(const Point &x, const Point &y)
{
	return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}
struct edge
{
	int END, next;
	double v;
}v[1005 * 1005];
int first[1005], p;
void add(int a, int b, double c)
{
	v[p].END = b;
	v[p].v = c;
	v[p].next = first[a];
	first[a] = p++;
}
double dis[1005][1005];
bool vis[1005];
void Spfa(int S)
{
	queue<int> Q;
	vis[S] = 1;
	dis[S][S] = 0;
	Q.push(S);
	while (!Q.empty())
	{
		int k = Q.front(); Q.pop();
		vis[k] = 0;
		for (int i = first[k]; i != -1; i = v[i].next)
		{
			if (dis[S][v[i].END] > dis[S][k] + v[i].v)
			{
				dis[S][v[i].END] = dis[S][k] + v[i].v;
				if (!vis[v[i].END])
				{
					vis[v[i].END] = 1;
					Q.push(v[i].END);
				}
			}
		}
	}
}
FILE *inf, *ouf, *ans;
int main(int argc, char *argv[])
{
	inf = fopen("input", "r");
	ouf = fopen("user_out", "r");
	ans = fopen("answer", "r");
	// registerTestlibCmd(argc, argv);
	memset (first, -1, sizeof (first));
	int n, m, k;
	fscanf (inf, "%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		fscanf (inf, "%lf%lf", &P[i].x, &P[i].y);
		// P[i].x = inf.readDouble(), P[i].y = inf.readDouble();
	}
	for (int i = 1; i <= m; i++)
	{
		fscanf (inf, "%d%d", &c[i].a, &c[i].b);
		// c[i].a = inf.readInt(), c[i].b = inf.readInt();
	}
	for (int i = 1; i <= k; i++)
	{
		int a, b;
		if (fscanf (ouf, "%d%d", &a, &b) == EOF)
		{
			printf ("0\n");
			return 0;
		}
		// int a = ouf.readInt(), b = ouf.readInt();
		add(a, b, Dis(P[a], P[b]));
		add(b, a, Dis(P[a], P[b]));
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dis[i][j] = 1e30;
	for (int i = 1; i <= n; i++)
		Spfa(i);
	double out = 0;
	for (int i = 1; i <= m; i++)
	{
		if (dis[c[i].a][c[i].b] >= 1e20)
		{
			printf ("0\n");
			fprintf(stderr, "0 There is at least one person who cannot reach his destination. %d %d\n", c[i].a, c[i].b);
		}
		out += dis[c[i].a][c[i].b];
	}

	double Ans/* = ans.readDouble()*/;
	fscanf (ans, "%lf", &Ans);
	if (out > 1e18)
	{
		printf ("0\n");
		fprintf(stderr, "0 Your answer is too large.\n");
	}
	out *= 100000, Ans *= 100000;
	int ans = (pow((Ans / out), 3) * 10 + 0.00001);
	if (ans > 10) ans = 10;
	ans = ans * 10;
	printf ("%d\n", ans);
	if (ans == 100) fprintf(stderr, "%d Right %.8f", ans, out / 100000);
	else if (ans == 0) fprintf(stderr, "0 Your answer is too large.\n");
	else fprintf(stderr, "%d Right %.8f", ans, out / 100000);
}
