#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct data
{
	int a, b;
	bool operator < (const data &c) const 
	{
		return b - a == c.b - c.a ? a < c.a : b - a > c.b - c.a;
	}
}v[100005];
long long f[100005];
int a[15];
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d%d", &v[i].a, &v[i].b);
		}
		sort(v + 1, v + n + 1);
		long long ans = 0, y = 0;
		for (int i = 1; i <= n; i++)
			if(y >= v[i].b)
				y -= v[i].a;
			else
				ans += v[i].b - y, y = v[i].b - v[i].a;
		printf("%lld\n", ans);
	}
}