#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int dx[8] = {1,1,-1,-1,2,2,-2,-2},
	dy[8] = {2,-2,2,-2,1,-1,1,-1};
int map[55][55], n, m;
#define ID(_ , __) ((_) * 51 + (__))
vector<int> v[55 * 55];
bool Check(int x, int y, int i)
{
	if(x + dx[i] > n || x + dx[i] < 1 || y + dy[i] > m || y + dy[i] < 1)
		return 0;
	if(map[x + dx[i]][y + dy[i]] == 2)
		return 0;
	return 1;
}
void ADD(int sx, int sy, int x, int y)
{
	v[ID(sx,sy)].push_back(ID(x,y));
}
void ADD(int a, int b)
{
	v[a].push_back(b);
}
bool flag[55][55], flag1[55][55], Add[55 * 55][55 * 55];
int tmp[55 * 55], tot;
void DFS(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		if(!Check(x, y, i))
			continue;
		int nx = x + dx[i], ny = y + dy[i];
		if (map[nx][ny] != 1 && !flag1[nx][ny])
		{
			flag1[nx][ny] = 1;
			tmp[++tot] = ID(nx, ny);
		}
		if (map[nx][ny] == 1 && !flag[nx][ny])
		{
			flag[nx][ny] = 1;
			DFS(nx, ny);
		}
	}
}
int Sx,Sy,Ex,Ey;
bool vis[55 * 55];
int dis[55 * 55];
int ans[55 * 55];
void BFS()
{
	queue<int> Q;
	Q.push(ID(Sx, Sy));
	vis[ID(Sx,Sy)] = 1;
	dis[ID(Sx,Sy)] = 0;
	ans[ID(Sx,Sy)] = 1;
	while(!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		//vis[k] = 0;
		if(k == ID(Ex, Ey))
			continue;
		for (int i = 0; i < v[k].size(); i++)
		{
			if(dis[v[k][i]] > dis[k] + 1)
			{
				dis[v[k][i]] = dis[k] + 1;
				ans[v[k][i]] = ans[k];
				if(!vis[v[k][i]])
				{
					Q.push(v[k][i]);
					vis[v[k][i]] = 1;
				}
			}
			else if(dis[v[k][i]] == dis[k] + 1)
			{
				ans[v[k][i]] += ans[k];
				if(!vis[v[k][i]])
				{
					Q.push(v[k][i]);
					vis[v[k][i]] = 1;
				}
			}
		}
	}

}
int main()
{
	scanf("%d%d", &n, &m);
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &map[i][j]);
			if(map[i][j] == 3)
				Sx = i, Sy = j;
			if(map[i][j] == 4)
				Ex = i, Ey = j;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if(map[i][j] != 2 && map[i][j] != 1)
				for (int k = 0; k < 8; k++)
					if(Check(i, j, k) && map[i + dx[k]][j + dy[k]] != 1)
						ADD(i, j, i + dx[k], j + dy[k]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if(map[i][j] == 1 && !flag[i][j])
			{
				tot = 0;
				memset(flag1, 0, sizeof(flag1));
				flag[i][j] = 1;
				DFS(i, j);
				for (int k = 1; k <= tot; k++)
					for (int l = k + 1; l <= tot; l++)
						if(!Add[tmp[k]][tmp[l]])
						{
							Add[tmp[k]][tmp[l]] = Add[tmp[l]][tmp[k]] = 1;
							ADD(tmp[k], tmp[l]);
							ADD(tmp[l], tmp[k]);
						}

			}
		}
	BFS();
	if(dis[ID(Ex, Ey)] == 0x3f3f3f3f)
		return printf("-1\n"),0;
	printf("%d\n%d\n",dis[ID(Ex,Ey)] - 1, ans[ID(Ex,Ey)]);
}