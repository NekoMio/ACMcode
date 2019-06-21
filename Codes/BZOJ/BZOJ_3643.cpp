#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;
int prime[500005];
bool isnprime[500005];
int tot, Max;
long long ans;
void Get_prime()
{
	isnprime[1] = 1;
	for (int i = 2; i <= 500000; i++)
	{
		if(!isnprime[i])
			prime[++tot] = i;
		for (int j = 1; j <= tot; j++)
		{
			if(i * prime[j] > 500000) break;
			isnprime[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
}
bool IsPrime(int x)
{
	int m = sqrt(x);
	for (int i = 1; prime[i] <= m; i++)
		if(x % prime[i] == 0)
			return 0;
	return 1;
}
void dfs(int k, int now, long long sum)
{
	if(sum >= ans)
		return;
	if(now == 1)
	{
		ans = min(ans, sum);
		return;
	}
	if(now > Max && IsPrime(now + 1))
	{
		ans = min(ans, sum * (now + 1));
	}
	for (int i = k; prime[i] - 1 <= Max; i++)
	{
		if(prime[i] - 1 > now)
				break;
		if(now % (prime[i] - 1) == 0)
		{
			int x = now / (prime[i] - 1);
			long long y = sum * prime[i];
			dfs(i + 1, x, y);
			while(x % prime[i] == 0)
			{
				x /= prime[i];
				y *= prime[i];
				dfs(i + 1, x, y);
			}
		}
	}
}
int main()
{
	Get_prime();
	int n;
	scanf("%d", &n);
	Max = sqrt(n);
	ans = INT_MAX;
	dfs(1, n, 1);
	if(ans < INT_MAX)
		printf("%d", ans);
	else
		printf("-1");
	//while(1);
}