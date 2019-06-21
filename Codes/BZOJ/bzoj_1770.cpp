#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
long long A[36], full, bin[37];
int Min = 0x3f, n, m;
map<long long, int> Mp;
void dfs1(int x, long long now, int k)
{
	if(x == m + 1)
	{
		if(now == full)
			Min = min(k, Min);
		int t = Mp[now];
		if(!t || t > k)
			Mp[now] = k;
		return;
	}
	dfs1(x + 1, now, k);
	dfs1(x + 1, now^A[x], k + 1);
}
void dfs2(int x, long long now, int k)
{
	if(x == n + 1)
	{
		if(now == full)
			Min = min(k, Min);
		int t = Mp[full - now];
		if(!t)
			return;
		Min = min(t + k, Min);
		return;
	}
	dfs2(x + 1, now, k);
	dfs2(x + 1, now^A[x], k + 1);
}
int main()
{
	// freopen("lights.in","r",stdin);
	// freopen("lights.out","w",stdout);
	int c;
	scanf("%d%d", &n, &c);
	bin[1] = 1;
	for (int i = 2; i < 37; i++)
		bin[i] = bin[i - 1] << 1;
	int a, b;
	for (int i = 1; i <= c; i++)
	{
		scanf("%d%d", &a, &b);
		A[a] += bin[b];
		A[b] += bin[a];
	}
	for (int i = 1; i <= n; i++)
		A[i] += bin[i];
	full = bin[n + 1] - 1;
	m = n >> 1;
	dfs1(1, 0, 0);
	dfs2(m + 1, 0, 0);
	printf("%d", Min);
}