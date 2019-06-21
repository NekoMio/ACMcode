#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
const int MOD = 998244353;
int s, k, n;
int base = 31;
int c[50], top;
int ans = 0;
set<unsigned int> st;
unsigned int Hash(int a)
{
	unsigned int ans = 0;
	for (int i = 1, j = a; i <= n; i++, j++)
		ans = ans * base + c[j] + base;
	return ans;
}

long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}
void dfs(int x, int dep)
{
	if (dep == 0)
	{
		if (x != s && !st.count(Hash(1)))
		{
			ans++;
			for (int i = 1; i <= n; i++)
				c[i + n] = c[i];
			for (int i = 1; i <= n; i++)
				st.insert(Hash(i));
		}
		return;
	}
	for (int i = 1; i <= k; i++)
	{
		if (i != x)
		{
			c[++top] = i;
			dfs(i, dep - 1);
			top--;
		}
	}
}
int main()
{
	freopen("necklace.in", "r", stdin);
	freopen("necklace.out", "w", stdout);
	int n, k;
	scanf ("%d%d", &n, &k);
	if (n <= 6 && k <= 8)
	{
		for (int i = 1; i <= k; i++)
		{
			c[++top] = 1;
			dfs(i, n - 1);
			top--;
		}
		printf ("%d\n", ans % MOD);
		return 0;
	}
	else if (n & 1)
	{
		printf ("%d\n", k * pow_mod(k - 1, n - 1) % MOD * pow_mod(n, MOD - 2) % MOD);	
	}
	else if (n == 2)
	{
		ans = 0;
		for (int i = 1; i <= k; i++)
			ans = (ans + i - 1) % MOD;
		printf ("%d\n", ans);
		return 0;
	}
}