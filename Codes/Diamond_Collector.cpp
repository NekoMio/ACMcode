#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long a[50005], k;
int f[50005];
int main()
{
	int n;
	scanf("%d%lld",&n,&k);
	for (int i = 1; i <= n; i++)
		scanf("%lld", a + i);
	sort(a + 1, a + n + 1);
	for (int i = n, j = n; i > 0; i--)
	{
		while(a[i] - a[j] <= k && j > 0) j--;
		f[i] = i - j;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, f[i] + f[i - f[i]]);
		f[i] = max(f[i - 1], f[i]);
	}
	printf("%d", ans);
}
