#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int Sum[100005];
int a[100005], n, m;
int Bound(int l, int r, int x)
{
	int ans = 0;
	while(l < r)
	{
		int mid = l + r >> 1;
		if(Sum[mid] <= x)
			ans = mid, l = mid + 1;
		else
			r = mid;
	}
	return ans;
}
bool Judge(int mid)
{
	for (int i = 1; Sum[i] < mid; i++)
	{
		int t = m;
		int now = i;
		while(t--)
		{
			now = Bound(1, 2 * n, Sum[now] + mid);
			if(now - i >= n)
				return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		r += a[i];
	}
	for (int i = n + 1; i <= n + n; i++)
		a[i] = a[i - n];
	for (int i = 1; i <= 2 * n; i++)
		Sum[i] = Sum[i - 1] + a[i];
	int ans = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if(Judge(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else
			l = mid + 1;
	}
	printf("%d", ans);
}