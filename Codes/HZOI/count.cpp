#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int END, next;
}v[2000005];
int first[1000005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int size[1000005], cnt[1000005];
void dfs(int x, int fa)
{
	size[x] = 1;
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		if(v[i].END == fa)continue;
		dfs(v[i].END, x);
		size[x] += size[v[i].END];
	}
	cnt[size[x]]++;
}
int n;
bool Judge(int x)
{
	int ans = 0;
	for (int i = 1; i * x <= n; i++)
	{
		ans += cnt[i * x];
	}
	if(ans == n / x)
		return 1;
	else
		return 0;
}
int main()
{
	memset(first, -1, sizeof(first));
	int a, b;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if(n % i)
			continue;
		ans += Judge(i);
	}
	printf("%d\n", ans);
}