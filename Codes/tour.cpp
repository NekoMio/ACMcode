#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int END, next, Id;
}v[200005];
int first[100005], p;
int size[100005], n, m;
void add(int a, int b, int id)
{
	v[p].END = b;
	v[p].next = first[a];
	v[p].Id = id;
	first[a] = p++;
}
bool vis[100005], flag[100005], mark[100005];
int num = 0;
void dfs(int x)
{
	vis[x] = 1;
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		mark[v[i].Id] = 1;
		if(!vis[v[i].END])
			dfs(v[i].END);
	}
}
bool IsOK()
{
	for (int i = 1; i <= n; i++)
		if(flag[i])
		{
			dfs(i);
			break;
		}
	for (int i = 0; i < p; i++)
		if (!mark[v[i].Id])
			return 0;
	return 1;
}
int self;
int main()
{
	memset(first, -1, sizeof(first));
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &a, &b);
		flag[a] = flag[b] = 1;
		add(a, b, i);
		if(a != b)
		{
			size[a]++;
			add(b, a, i);
			size[b]++;
		}
		else
			self++;
	}
	if (!IsOK())
	{
		printf("0\n");
		return 0;
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += ((long long)size[i] * (size[i] - 1) / 2);
	ans += ((long long)self * (m - self));
	ans += ((long long)self * (self - 1) / 2);
	printf("%lld\n",ans);
}