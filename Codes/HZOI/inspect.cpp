#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[2005][2005];
int n, m;
bool Judge(int mid)
{
	for (int i = mid; i <= n; i++)
	{
		for (int j = mid; j <= m; j++)
		{
			if(a[i][j] - a[i][j - mid] - a[i - mid][j] + a[i - mid][j - mid] == mid * mid)
				return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d",&a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] += (a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1]);
	int l = 0, r = min(n, m) + 1;
	int ans = 0;
	while(l < r)
	{
		int mid = l + r >> 1;
		if(Judge(mid))
			ans = mid, l = mid + 1;
		else
			r = mid;
	}
	printf("%d\n", ans);
}