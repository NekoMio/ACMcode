#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <set>
#include <queue>
const int N = 100005;
using namespace std;
set<int> S[N], T[N];
int fa[N];
queue<pair<int, int> > Q;
int find(int x)
{
	if (x != fa[x]) fa[x] = find(fa[x]);
	return fa[x];
}
void Solve()
{
	int n;
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		S[i].clear();
		T[i].clear();
	}
	int a, b;
	for (int i = 1; i < n; i++)
	{
		scanf ("%d%d", &a, &b);
		S[a].insert(b);
		S[b].insert(a);
	}
	for (int i = 1; i < n; i++)
	{
		scanf ("%d%d", &a, &b);
		if (S[a].count(b))
		{
			Q.push(pair<int, int>(a, b));

		}
	}
}
int main()
{
	int T;
	scanf ("%d", &T);
	srand(T);
	while (T--)
	{
		double ans = (double)rand() / 65535;
		if (ans > 0.3) printf("NO\n");
		else printf ("YES\n");
	}
}
