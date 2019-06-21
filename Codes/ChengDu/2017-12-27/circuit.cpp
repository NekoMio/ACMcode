#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

using namespace std;

const int MAXN = 2005;
int a[MAXN];
int b[MAXN];
int dis[MAXN][MAXN][4];
struct data
{
	int x, y, tp;
	data(int c, int d, int s = 0) {x = c, y = d, tp = s;}
};
queue<data> Q;
bool vis[MAXN][MAXN][4];
int W, H;
int Calc(int x, int y)
{
	memset (dis, -1, sizeof (dis));
	if (x - 1 > 0) Q.push(data(x - 1, y, 0)), dis[x - 1][y][0] = 1, vis[x - 1][y][0] = 1;
	if (y + 1 <= W)Q.push(data(x, y + 1, 1)), dis[x][y + 1][1] = 1, vis[x][y + 1][1] = 1; 
	if (x + 1 <= H)Q.push(data(x + 1, y, 2)), dis[x + 1][y][2] = 1, vis[x + 1][y][2] = 1;
	if (y - 1 > 0) Q.push(data(x, y - 1, 3)), dis[x][y - 1][3] = 1, vis[x][y - 1][3] = 1;
	int ans = 0;
	while (!Q.empty())
	{
		data x = Q.front();
		vis[x.x][x.y][x.tp] = 0;
		Q.pop();
		if (x.tp == 0)
		{
			if (a[x.x] < b[x.y])
			{
				if (x.x - 1 > 0)
				{
					if (dis[x.x - 1][x.y][0] < dis[x.x][x.y][0] + 1)
					{
						dis[x.x - 1][x.y][0] = dis[x.x][x.y][0] + 1;
						if (!vis[x.x - 1][x.y][0])
						{
							Q.push(data(x.x - 1, x.y, 0));
							vis[x.x - 1][x.y][0] = 1;
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][0]);
			}
			else
			{
				if (x.y + 1 <= W || x.y - 1 > 0)
				{
					if (x.y + 1 <= W)
					{
						if (dis[x.x][x.y + 1][1] < dis[x.x][x.y][0] + 1)
						{
							dis[x.x][x.y + 1][1] = dis[x.x][x.y][0] + 1;
							if (!vis[x.x][x.y + 1][1])
							{
								Q.push(data(x.x, x.y + 1, 1));
								vis[x.x][x.y + 1][1] = 1;
							}
						}
					}
					if (x.y - 1 > 0)
					{
						if (dis[x.x][x.y - 1][3] < dis[x.x][x.y][0] + 1)
						{
							dis[x.x][x.y - 1][3] = dis[x.x][x.y][0] + 1;
							if (!vis[x.x][x.y - 1][3])
							{
								Q.push(data(x.x, x.y - 1, 3));
								vis[x.x][x.y - 1][3] = 1;
							}
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][0]);
			}
		}
		else if (x.tp == 1)
		{
			if (b[x.y] < a[x.x])
			{
				if (x.y + 1 <= W)
				{
					if (dis[x.x][x.y + 1][1] < dis[x.x][x.y][1] + 1)
					{
						dis[x.x][x.y + 1][1] = dis[x.x][x.y][1] + 1;
						if (!vis[x.x][x.y + 1][1])
						{
							Q.push(data(x.x, x.y + 1, 1));
							vis[x.x][x.y + 1][1] = 1;
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][1]);
			}
			else
			{
				if (x.x + 1 <= H || x.x - 1 > 0)
				{
					if (x.x + 1 <= H)
					{
						if (dis[x.x + 1][x.y][2] < dis[x.x][x.y][1] + 1)
						{
							dis[x.x + 1][x.y][2] = dis[x.x][x.y][1] + 1;
							if (!vis[x.x + 1][x.y][2])
							{
								Q.push(data(x.x + 1, x.y, 2));
								vis[x.x + 1][x.y][2] = 1;
							}
						}
					}
					if (x.x - 1 > 0)
					{
						if (dis[x.x - 1][x.y][0] < dis[x.x][x.y][1] + 1)
						{
							dis[x.x - 1][x.y][0] = dis[x.x][x.y][1] + 1;
							if (!vis[x.x - 1][x.y][0])
							{
								Q.push(data(x.x - 1, x.y, 0));
								vis[x.x - 1][x.y][0] = 1;
							}
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][1]);
			}
		}
		else if (x.tp == 2)
		{
			if (a[x.x] < b[x.y])
			{
				if (x.x + 1 <= H)
				{
					if (dis[x.x + 1][x.y][2] < dis[x.x][x.y][2] + 1)
					{
						dis[x.x + 1][x.y][2] = dis[x.x][x.y][2] + 1;
						if (!vis[x.x + 1][x.y][2])
						{
							Q.push(data(x.x + 1, x.y, 2));
							vis[x.x + 1][x.y][2] = 1;
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][2]);
			}
			else
			{
				if (x.y + 1 <= W || x.y - 1 > 0)
				{
					if (x.y + 1 <= W)
					{
						if (dis[x.x][x.y + 1][1] < dis[x.x][x.y][2] + 1)
						{
							dis[x.x][x.y + 1][1] = dis[x.x][x.y][2] + 1;
							if (!vis[x.x][x.y + 1][1])
							{
								Q.push(data(x.x, x.y + 1, 1));
								vis[x.x][x.y + 1][1] = 1;
							}
						}
					}
					if (x.y - 1 > 0)
					{
						if (dis[x.x][x.y - 1][3] < dis[x.x][x.y][2] + 1)
						{
							dis[x.x][x.y - 1][3] = dis[x.x][x.y][2] + 1;
							if (!vis[x.x][x.y - 1][3])
							{
								Q.push(data(x.x, x.y - 1, 3));
								vis[x.x][x.y - 1][3] = 1;
							}
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][2]);
			}
		}
		else if (x.tp == 3)
		{
			if (b[x.y] < a[x.x])
			{
				if (x.y - 1 > 0)
				{
					if (dis[x.x][x.y - 1][3] < dis[x.x][x.y][3] + 1)
					{
						dis[x.x][x.y - 1][3] = dis[x.x][x.y][3] + 1;
						if (!vis[x.x][x.y - 1][3])
						{
							Q.push(data(x.x, x.y - 1, 3));
							vis[x.x][x.y - 1][3] = 1;
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][3]);
			}
			else
			{
				if (x.x + 1 <= H || x.x - 1 > 0)
				{
					if (x.x + 1 <= H)
					{
						if (dis[x.x + 1][x.y][2] < dis[x.x][x.y][3] + 1)
						{
							dis[x.x + 1][x.y][2] = dis[x.x][x.y][3] + 1;
							if (!vis[x.x + 1][x.y][2])
							{
								Q.push(data(x.x + 1, x.y, 2));
								vis[x.x + 1][x.y][2] = 1;
							}
						}
					}
					if (x.x - 1 > 0)
					{
						if (dis[x.x - 1][x.y][0] < dis[x.x][x.y][3] + 1)
						{
							dis[x.x - 1][x.y][0] = dis[x.x][x.y][3] + 1;
							if (!vis[x.x - 1][x.y][0])
							{
								Q.push(data(x.x - 1, x.y, 0));
								vis[x.x - 1][x.y][0] = 1;
							}
						}
					}
				}
				else ans = max(ans, dis[x.x][x.y][3]);
			}
		}
	}
	return ans;
}
int main()
{
	freopen ("circuit.in", "r", stdin);
	freopen ("circuit.out", "w", stdout);
	H = read(), W = read();
	int Q = read();
	for (int i = 1; i <= H; i++) a[i] = read();
	for (int i = 1; i <= W; i++) b[i] = read();
	for (int i = 1; i <= Q; i++)
	{
		int s = read(), t = read();
		printf ("%d\n", Calc(s, t));
	}
}
