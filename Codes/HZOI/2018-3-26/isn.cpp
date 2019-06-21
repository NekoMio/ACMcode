#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MOD = 1e9 + 7;
const int MAXN = 2005;
int n;
#define lowbit(_) ((_)&(-_)) 
struct BIT
{
	long long Sum[MAXN];
	void add(int x, int c)
	{
		x++;
		for (int i = x; i <= n; i += lowbit(i))
			Sum[i] = (Sum[i] + c) % MOD;
	}
	int Query(int x)
	{
		x++;
		int ans = 0;
		for (int i = x; i >= 1; i -= lowbit(i))
			ans = (ans + Sum[i]) % MOD;
		return ans;
	}
}T[MAXN];
int DP[MAXN][MAXN];
int f[MAXN], a[MAXN], b[MAXN];
long long F[MAXN];
int main()
{
	// freopen ("2.in", "r", stdin);
	// freopen ("2.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; i++)
		b[i] = a[i] = read();
	F[0] = 1;
	for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % MOD;
	sort(b + 1, b + n + 1);
	int cnt = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
	DP[0][0] = 1;
	T[0].add(0, 1);
	for (int i = 1; i <= n; i++)
		for (int j = n; j >= 1; j--)
		{
			DP[i][j] = (DP[i][j] + T[j - 1].Query(a[i])) % MOD;
			f[j] = (f[j] + DP[i][j]) % MOD;
			T[j].add(a[i], DP[i][j]);
		}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (ans + 1ll * f[i] * F[n - i] % MOD - 1ll * f[i + 1] * F[n - i - 1] % MOD * (i + 1) % MOD + MOD) % MOD;
	printf ("%lld\n", ans);
}