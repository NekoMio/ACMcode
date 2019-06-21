#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
	int END,next;
}v[2000005];
int first[1000005], p;
int vis[1000005], links[1000005];
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
bool find(int x, int k)
{
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		if(vis[v[i].END] != k)
		{
			vis[v[i].END] = k;
			if(links[v[i].END] == -1 || find(links[v[i].END],k))
			{
				links[v[i].END] = x;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	memset(first, -1, sizeof(first));
	memset(links, -1, sizeof(links));
	int n;
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a, &b);
		add(a, i);
		add(b, i);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if(find(i, i)) ans++;
		else break;
	}
	printf("%d", ans);
}