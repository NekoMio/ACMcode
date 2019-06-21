#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct book
{
	int x, y;
	bool operator < (const book &b)const
	{
		return x == b.x ? y > b.y : x > b.x;
	}	
}a[305];
int f[305];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		f[i] = 1;
		for (int j = 1; j < i; j++)
		{
			if(a[i].y > a[j].y && f[i] < f[j] + 1)
				f[i] = f[j] + 1;
		}
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
}