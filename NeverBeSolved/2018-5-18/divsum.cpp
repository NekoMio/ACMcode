// #pragma GCC optimize("O3")
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
const int MAXN = 100000;
const int MOD = 1e9 + 7;
int prime[MAXN + 2], d[MAXN + 2], cnt, F[MAXN + 2];
int t[42][42][42];
bool isnprime[MAXN + 2];
void Get_mu()
{
	for (int i = 1; i <= MAXN; i++) d[i] = 1;
	for (int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i])
		{
			prime[cnt++] = i;
			for (int j = 1; j <= MAXN / i; j++)
			{
				isnprime[i * j] = 1;
				d[i * j] = (d[i * j] + d[j]) % MOD;
			}
		}
	}
	for (int i = 1; i <= MAXN; i++)
		F[i] = (F[i - 1] + d[i]) % MOD;
	reverse(prime, prime + cnt);
	for (int i = 1; i <= 40; i++)
		for (int j = 1; j <= 40; j++)
			for (int k = 1; k <= 40; k++)
				t[i][j][k] = ((1ll * t[i - 1][j][k] + t[i][j - 1][k] + t[i][j][k - 1] - t[i - 1][j - 1][k] - t[i - 1][j][k - 1] - t[i][j - 1][k - 1] + t[i - 1][j - 1][k - 1] + d[i * j * k]) % MOD + MOD) % MOD;
}
int DFS(int dep, int A, int B, int C)
{
	if (!prime[dep]) return 1ll * F[A] % MOD * F[B] % MOD * F[C] % MOD;
	if (prime[dep] > max(max(A, B), C) && max(max(A, B), C) <= 40) return t[A][B][C];
	if (A == 0 || B == 0 || C == 0) return 0;
	int ans = DFS(dep + 1, A, B, C);
	if (A >= prime[dep] && B >= prime[dep])
		ans = ((ans - DFS(dep + 1, A / prime[dep], B / prime[dep], C)) % MOD + MOD) % MOD;
	if (B >= prime[dep] && C >= prime[dep])
		ans = ((ans - DFS(dep + 1, A, B / prime[dep], C / prime[dep])) % MOD + MOD) % MOD;
	if (A >= prime[dep] && C >= prime[dep])
		ans = ((ans - DFS(dep + 1, A / prime[dep], B, C / prime[dep])) % MOD + MOD) % MOD;
	if (A >= prime[dep] && B >= prime[dep] && C >= prime[dep])
		ans = (ans + (DFS(dep + 1, A / prime[dep], B / prime[dep], C / prime[dep]) << 1) % MOD) % MOD;
	return ans;
}
int main()
{
	int T = read();
	Get_mu();
	while (T--)
	{
		int A = read(), B = read(), C = read();
		int t = 0;
		while (prime[t] > A && prime[t] > B && prime[t] > C) t++;
		printf ("%d\n", DFS(t, A, B, C));
	}
}
