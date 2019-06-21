#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
char a[30], b[30], c[30];
bool mark[30];
int map[300], n, ans;
void dfs(int pos, int y)
{
	ans++;
	//printf("%d\n", ans);
	if(pos == 0)
	{
		for (int i = 'A'; i < 'A' + n; i++)
			printf("%d ",map[i]);
		exit(0);
	}
	if(map[a[pos]] != -1 && map[b[pos]] != -1 && map[c[pos]] != -1)
	{
		if((map[a[pos]] + map[b[pos]] + y) % n != map[c[pos]])
			return;
		else
			dfs(pos - 1, (map[a[pos]] + map[b[pos]] + y) / n);
	}
	else if (map[a[pos]] != -1 && map[b[pos]] != -1)
	{
		if(mark[(map[a[pos]] + map[b[pos]] + y) % n])
			return;
		else
		{
			map[c[pos]] = (map[a[pos]] + map[b[pos]] + y) % n;
			mark[(map[a[pos]] + map[b[pos]] + y) % n] = 1;
			dfs(pos - 1, (map[a[pos]] + map[b[pos]] + y) / n);
			mark[(map[a[pos]] + map[b[pos]] + y) % n] = 0;
			map[c[pos]] = -1;
		}
	}
	else if (map[a[pos]] != -1 && map[c[pos]] != -1)
	{
		int now = map[c[pos]] + n - y - map[a[pos]];
		if(mark[now % n])
			return;
		map[b[pos]] = now % n;
		mark[now % n] = 1;
		dfs(pos - 1, (now % n) == now ? 1 : 0);
		map[b[pos]] = -1;
		mark[now % n] = 0;
	}
	else if (map[b[pos]] != -1 && map[c[pos]] != -1)
	{
		int now = map[c[pos]] + n - y - map[b[pos]];
		if(mark[now % n])
			return;
		map[a[pos]] = now % n;
		mark[now % n] = 1;
		dfs(pos - 1, (now % n) == now ? 1 : 0);
		map[a[pos]] = -1;
		mark[now % n] = 0;
	}
	else if(map[a[pos]] != -1)
	{
		for (int i = 0; i < n; i++)
			if(!mark[i] && !mark[(map[a[pos]] + i + y) % n])
			{
				map[b[pos]] = i;
				map[c[pos]] = (map[a[pos]] + i + y) % n;
				mark[i] = 1;
				mark[(map[a[pos]] + i + y) % n] = 1;
				dfs(pos - 1, (map[a[pos]] + i + y) / n);
				map[b[pos]] = -1;
				map[c[pos]] = -1;
				mark[i] = 0;
				mark[(map[a[pos]] + i + y) % n] = 0;
			}
	}
	else if(map[b[pos]] != -1)
	{
		for (int i = 0; i < n; i++)
			if(!mark[i] && !mark[(map[b[pos]] + i + y) % n])
			{
				map[a[pos]] = i;
				map[c[pos]] = (map[b[pos]] + i + y) % n;
				mark[i] = 1;
				mark[(map[b[pos]] + i + y) % n] = 1;
				dfs(pos - 1, (map[b[pos]] + i + y) / n);
				map[a[pos]] = -1;
				map[c[pos]] = -1;
				mark[i] = 0;
				mark[(map[b[pos]] + i + y) % n] = 0;
			}
	}
	else if(map[c[pos]] != -1)
	{
		for (int i = 0; i < n; i++)
		{
			if(!mark[i] && !mark[(map[c[pos]] + n - i - y) % n])
			{
				map[a[pos]] = i;
				map[b[pos]] = (map[c[pos]] + n - i - y) % n;
				mark[i] = 1;
				mark[(map[c[pos]] + n - i - y) % n] = 1;
				dfs(pos - 1, ((map[c[pos]] + n - i - y) % n == (map[c[pos]] + n - i - y)));
				map[a[pos]] = -1;
				map[b[pos]] = -1;
				mark[i] = 0;
				mark[(map[c[pos]] + n - i - y) % n] = 0;
			}
		}
	}
	else
	{
		// printf("\\\\\n");
		for (int i = n - 1; i >= 0; i--)
		{
			if(mark[i]) continue;
			mark[i] = 1;
			map[a[pos]] = i;
			// printf("------__\n");
			for (int j = n - 1; j >= 0; j--)
			{
				if(!mark[j] && !mark[(i + j + y) % n])
				{
					// printf("===\n");
					mark[j] = mark[(i + j + y) % n] = 1;
					map[b[pos]] = j;
					map[c[pos]] = (i + j + y) % n;
					dfs(pos - 1, (i + j + y) / n);
					mark[j] = mark[(i + j + y) % n] = 0;
					map[b[pos]] = -1;
					map[c[pos]] = -1;
				}
				else if (mark[j] && mark[(i + j + y) % n] && (j == map[b[pos]]) && ((i + j + y) % n == map[c[pos]]))
				{
					dfs(pos - 1, (i + j + y) / n);
				}
				else if (mark[j] && (j == map[b[pos]]) && !mark[(i + j + y) % n])
				{
					// printf("----\n");
					mark[(i + j + y) % n] = 1;
					map[c[pos]] = (i + j + y) % n;
					dfs(pos - 1, (i + j + y) / n);
					map[c[pos]] = -1;
					mark[(i + j + y) % n] = 0;
				}
			}
			map[a[pos]] = -1;
			mark[i] = 0;
		}
	}
}
int main()
{
	// freopen("alpha.in","r",stdin);
	// freopen("alpha.out","w",stdout);
	scanf("%d", &n);
	scanf("%s%s%s", a + 1, b + 1, c + 1);
	for (int i = 'A'; i < 'A' + n; i++)
		map[i] = -1;
	dfs(n, 0);
}