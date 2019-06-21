#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[200005][2];
int n;
int get(int now, int pos)
{
 	if (a[pos][now] >= a[pos - 1][now] && a[pos][now] <= a[pos + 1][now]) return a[pos][now];
    if (a[pos][now] <= a[pos - 1][now] && a[pos][now] >= a[pos + 1][now]) return a[pos][now];
    if (a[pos - 1][now] >= a[pos][now] && a[pos - 1][now] <= a[pos + 1][now]) return a[pos - 1][now];
    if (a[pos - 1][now] <= a[pos][now] && a[pos - 1][now] >= a[pos + 1][now]) return a[pos - 1][now];
    if (a[pos + 1][now] >= a[pos - 1][now] && a[pos + 1][now] <= a[pos][now]) return a[pos + 1][now];
    if (a[pos + 1][now] <= a[pos - 1][now] && a[pos + 1][now] >= a[pos][now]) return a[pos + 1][now];
}
int main()
{
 	scanf ("%d", &n);
	int alle = 1;
 	for (int i = 1; i <= 2 * n - 1; i++)
	{
		scanf ("%d", &a[i][0]);
		if (a[i][0] != i) alle = 0;
	}
	if (alle) return printf ("%d", n), 0;
	if (n <= 1000)
	{
		int now = 0;
		for (int i = 1; i < n; i++)
		{
			now ^= 1;
			for (int j = i + 1; j <= 2 * n - i - 1; j++)
			{
				a[j][now] = get(now^1, j); 		 	
			}
		}
		printf ("%d", a[n][now]);
	}
	else
	{
		printf ("%d", get(0, n));
	}
}
