#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int next, END;
}v[110005];
int first[110005], p;
int du[110005], belong[110005], cnt[110005];
bool vis[110005], flag[110005];
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
void dfs(int x, int Be)
{
	vis[x] = 1;
	belong[x] = Be;
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		if(!vis[v[i].END])
			dfs(v[i].END, Be);
	}
}
int Index;
int main()
{
	memset(first, -1, sizeof(first));
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &a, &b);
		if (a == 0) a = ++n;
		if (b == 0) b = ++n;
		add(a, b), add(b, a);
		du[a]++, du[b]++;
	}
	for (int i = 1; i <= n; i++)
		if(du[i] && !vis[i])
			dfs(i, ++Index);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (du[i] > 2)
		{
			ans++;
			du[i] = (du[i] & 1 ? 1 : 2);
			flag[belong[i]] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if(du[i] == 1)
		{
			cnt[belong[i]]++;
			if(cnt[belong[i]] == 4)
				ans++, cnt[belong[i]] = 2;
		}
	}
	if (Index != 1)
	{
		for (int i = 1; i <= Index; i++)
			if(!flag[i] && !cnt[i])
				ans++;
		ans += Index;
	}
	else
		ans += (cnt[1] != 0);
	printf("%d", ans);
}