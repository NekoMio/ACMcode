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
const int MAXN = 1e6;
const int MOD = 1e9 + 7;
const int Inv2 = (MOD + 1) >> 1;
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
struct Hash_Table
{
	struct data
	{
		int ans, next;
		int x;
	}v[MAXN];
	int first[76545], p;
	Hash_Table()
	{
		memset (first, -1, sizeof (first));
		p = 0;
	}
	bool count(const int x)
	{
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return 1;
		return 0;
	}
	int &operator[](const int x) 
	{
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return v[i].ans;
		v[p].x = x;
		v[p].next = first[H];
		first[H] = p++;
		return v[first[H]].ans = 0;
	}
}Hash;
int prime[MAXN + 2], mu[MAXN + 2], cnt;
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
	for (int i = 1; i <= MAXN; i++)
		mu[i] += mu[i - 1];
}
int G(int n)
{
	if (n <= MAXN) return mu[n];
	if (Hash.count(n)) return Hash[n];
	int ans = 1, nxt;
	for (int i = 2; i <= n; i = nxt + 1)
	{
		nxt = n / (n / i);
		ans = (ans - 1ll * (nxt - i + 1) * G(n / i) % MOD + MOD) % MOD;
	}
	// if (ans < 0) ans += MOD;
	return Hash[n] = ans;
}
int F[MAXN + 2], Inv[MAXN + 2], Invi[MAXN + 2];
int C(int n, int m)
{
	if (n <= MAXN)
	{
		return 1ll * F[n] * Inv[m] % MOD * Inv[n - m] % MOD; 
	}
	else
	{
		int ans = 1;
		for (int i = 1; i <= m; i++)
			ans = 1ll * ans * (n - i + 1) % MOD;
		for (int i = 1; i <= m; i++)
			ans = 1ll * ans * Invi[i] % MOD;
		return ans;
	}
}
int main()
{
	int T = read();
	F[0] = 1;
	for (int i = 1; i <= MAXN; i++) F[i] = 1ll * F[i - 1] * i % MOD;
	Inv[MAXN] = pow_mod(F[MAXN], MOD - 2);
	for (int i = MAXN - 1; i >= 0; i--) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
	for (int i = 1; i <= MAXN; i++) Invi[i] = pow_mod(i, MOD - 2);
	Get_mu();
	while (T--)
	{
		int n = read(), k = read();
		long long ans = 0;
		int nxt;
		for (int i = 1; i <= n; i = nxt + 1)
		{
			nxt = n / (n / i);
			ans = (ans + 1ll * (G(nxt) - G(i - 1) + MOD) % MOD * C(n / i + k - 1, k) % MOD) % MOD;
		}
		printf ("%lld\n", ans);
	}
}

