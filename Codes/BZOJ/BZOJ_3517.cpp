#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1005][1005];
int SumX[1005], SumY[1005];
int main()
{
 	int n;
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf ("%1d", &a[i][j]);
			SumX[i] ^= a[i][j];
			SumY[j] ^= a[i][j];
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			ans += SumX[i] ^ SumY[j] ^ a[i][j];
	printf ("%d", min(ans, n * n - ans));
}
