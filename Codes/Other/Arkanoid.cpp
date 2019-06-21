#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[55][55];
int sum[55][55];
int f[55][55][505];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n - i + 1; j++)
		{
			scanf("%d", &a[i][j]);
			sum[j][i] = sum[j][i - 1] + a[i][j];
		}
	int ans = 0;
	for (int i = n; i >= 1; i--)
	{
		for (int j = 0; j <= n - i + 1; j++)
		{
			for (int k = max(0, j - 1); k <= n - i; k++)
			{
				for (int s = j * (j + 1) / 2; s <= m; s++)
				{
					f[i][j][s] = max(f[i][j][s], f[i + 1][k][s - j] + sum[i][j]);
				}
			}
			ans = max(f[i][j][m], ans);
		}
	}
	printf("%d",ans);
}