#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct edge
{
	int END, next;
}E[200005], v[200005];
int first[100005], head[100005], p, h, dis[100005];
bool vis[100005], ok[100005];
void add(int a,int b,int op)
{
	if(op)
	{
		v[p].END = b;
		v[p].next = first[a];
		first[a] = p++;
	}
	else
	{
		E[h].END = b;
		E[h].next = head[a];
		head[a] = h++;
	}
}
void dfs(int x)
{
	vis[x] = 1;
	for (int i = head[x]; i != -1; i = E[i].next)
	{
		if(!vis[E[i].END])
			dfs(E[i].END);
	}
}
int main()
{
	// freopen("roadb.in","r",stdin);
	// freopen("roadb.out","w",stdout);
	memset(head,-1,sizeof(head));
	memset(first,-1,sizeof(first));
	int n, m;
	scanf("%d%d", &n, &m);
	int s, e;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &s, &e);
		add(e, s, 0);
		add(s, e, 1);
	}
	scanf("%d%d",&s, &e);
	dfs(e);
	for (int i = 1; i <= n; i++)
	{
		ok[i] = 1;
		for (int j = first[i]; j != -1; j = v[j].next)
			if(!vis[v[j].END])
			{
				ok[i] = 0;
				break;
			}
	}
	if(!ok[s])
	{
		printf("-1\n");
		return 0;
	}
	memset(vis,0,sizeof(vis));
	queue<int> Q;
	Q.push(s);
	vis[s] = 1;
	memset(dis,0x3f,sizeof(dis));
	dis[s] = 0;
	while(!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		vis[k] = 0;
		for (int i = first[k]; i != -1; i = v[i].next)
			if (ok[v[i].END] && dis[v[i].END] > dis[k] + 1)
			{
				dis[v[i].END] = dis[k] + 1;
				if(!vis[v[i].END])
				{
					Q.push(v[i].END);
					vis[v[i].END] = 1;
				}
			}
	}
	if(dis[e] > 100000000)
		dis[e] = -1;
	printf("%d\n", dis[e]);
}