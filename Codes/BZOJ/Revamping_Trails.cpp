#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int dis[10005][25];
bool vis[10005][25];
struct edge
{
	int END, next, v;
}v[50005 << 1];
int first[10005], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].v = c;
	first[a] = p++;
}
struct data
{
	int x, k;
	data(int a,int b)
	{
		x = a, k = b;
	}
	bool operator < (const data &a)const
	{
		return dis[x][k] > dis[a.x][a.k];
	}
};
priority_queue<data> Q;
int main()
{
	memset(first,-1,sizeof(first));
	memset(dis, 0x3f, sizeof(dis));
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	int a,b,c;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add(a, b, c);
		add(b, a, c);
	}
	dis[1][0] = 0;
	vis[1][0] = 1;
	Q.push(data(1,0));
	while(!Q.empty())
	{
		data u = Q.top();
		Q.pop();
		vis[u.x][u.k] = 0;
		for (int i = first[u.x]; i != -1; i = v[i].next)
		{
			if(dis[v[i].END][u.k] > dis[u.x][u.k] + v[i].v)
			{
				dis[v[i].END][u.k] = dis[u.x][u.k] + v[i].v;
				if(!vis[v[i].END][u.k])
				{
					Q.push(data(v[i].END,u.k));
					vis[v[i].END][u.k] = 1;
				}
			}
			if(dis[v[i].END][u.k + 1] > dis[u.x][u.k] && u.k < k)
			{
				dis[v[i].END][u.k + 1] = dis[u.x][u.k];
				if(!vis[v[i].END][u.k + 1])
				{
					Q.push(data(v[i].END, u.k + 1));
					vis[v[i].END][u.k + 1] = 1;
				}
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for (int i = 0; i <= k; i++)
		ans = min(ans, dis[n][i]);
	printf("%d",ans);
}