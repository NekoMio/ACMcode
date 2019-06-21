#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MAXN = 3000;
int mu[MAXN + 2], prime[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
void Get_mu()
{
	isnprime[1] = 1;
	mu[1] = 1;
	for (int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt; j++)
		{
			if (i * prime[j] > MAXN) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
}
long long f[2][(1 << 16) + 1];
int X[MAXN + 1], ID[MAXN + 1];
void Update(int x)
{
	for (int i = 1; i <= cnt; i++)
		while (x % prime[i] == 0)
			x /= prime[i], X[i]++;
}
int t[MAXN + 1], Cnt;
int Big[MAXN + 1], Num;
int trans(int x, bool &ok)
{
    int s = 0;
    for (int i = 1; i <= Cnt; i++)
    {
        while (x % t[i] == 0)
        {
            x /= t[i];
            s ^= (1 << (i - 1));
        }
    }
	if (x != 1) ok = 0;
	else ok = 1;
    return s;
}
long long DP[(1 << 16) + 1][100];
int tmp[MAXN + 1], C[MAXN + 1], transNum;
signed main()
{
	// freopen("1.out", "w", stdout);
	Get_mu();
	int n;
	scanf ("%lld", &n);
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		Update(i);
	for (int i = 1; i <= cnt; i++) ID[prime[i]] = i;
	for (int i = 1; i <= cnt; i++)
	{
		if (prime[i] * prime[i] <= n && (X[i] & 1))
			t[++Cnt] = prime[i];
		if (prime[i] * prime[i] > n && (X[i] & 1) && (X[i] != 1))
			Big[++Num] = prime[i];
 	}
	int now = 0;
	int N = (1 << Cnt) - 1;
	for (int i = 1; i <= n; i++)
	{
		now ^= 1;
		bool ok = 1;
		int t = trans(i, ok);
		memset (f[now], 0, sizeof (f[now][0]) * N + 4);
		for (int j = 0; j <= N; j++)
		{
			if (((j ^ N) & t) == t && mu[i] != 0 && ok)
				f[now][j ^ t] += f[now ^ 1][j];
			f[now][j] += f[now ^ 1][j];
		}
		// for (int j = 0; j <= N; j++)
		// 	printf ("%lld ", f[now][j]);
		// printf ("\n");
	}
	for (int i = 0; i <= N; i++)
		DP[i][0] = f[now][i];
	for (int i = 0; i <= N; i++)
	{
		int Tmp = 1;
		for (int j = 1; j <= Cnt; j++)
			if (i & (1 << (j - 1)))
				Tmp *= t[j];
		if (Tmp * Tmp <= n)
			tmp[++transNum] = i, C[transNum] = Tmp;
	}
	for (int j = 1; j <= Num; j++)
	{
		for (int k = 1; k <= transNum; k++)
		{
			if (Big[j] * C[k] <= n)
			{
				for (int i = 0; i <= N; i++)
				{
					if (((i ^ N) & tmp[k]) == tmp[k])
					{
						DP[i ^ tmp[k]][j] += DP[i][j - 1];
					}
				}
			}
		}
	}
	printf ("%lld\n", DP[N][Num]);
	// while (1);
}
