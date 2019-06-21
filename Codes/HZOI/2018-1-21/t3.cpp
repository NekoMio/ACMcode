#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
static inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
static inline int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
const int MAXN = 2e6;
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
	bool count(const long long x)
	{
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return 1;
		return 0;
	}
	int &operator[](const long long x) 
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
}Hash, Hashf;
int prime[MAXN + 3], mu[MAXN + 3], cnt, Sum[MAXN + 3], Sumf[MAXN + 3], SumF[MAXN + 3];
int pr[505];
bool isnprime[MAXN + 3];
int n, m, k, ans;
void Get_mu()
{
	isnprime[1] = 1;
	mu[1] = 1;
	for (int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt; j++)
		{
			if (prime[j] * i > MAXN) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 2; i <= k; i++)
		if (k % i == 0)
			pr[++pr[0]] = i;
	for (int i = 1; i <= MAXN; i++)
		Sum[i] = Sum[i - 1] + mu[i];
	for (int i = 1; i <= MAXN; i++)
		Sumf[i] = Sumf[i - 1] + (gcd(i, k) == 1) * mu[i];
	for (int i = 1; i <= k; i++)
	 	SumF[i] = SumF[i - 1] + (gcd(i, k) == 1);
}
int g(long long x)
{
	if (x <= MAXN) return Sum[x];
	if (Hash.count(x)) return Hash[x];
	int ans = 1;
	long long nxt = 1;
	for (long long i = 2; i <= x; i = nxt + 1)
	{
		nxt = x / (x / i);
		ans -= (nxt - i + 1) * g(x / i);
	}
	return Hash[x] = ans;
}
int f(long long x)
{
	if (x <= MAXN) return Sumf[x];
	int ans = g(x);
	for (int i = 1; i <= pr[0]; i++)
	{
		ans -= mu[pr[i]] * f(x / pr[i]);
	}
	return ans;
}
int F(int x)
{
	return (x / k) * SumF[k] + SumF[x % k];
}
signed main()
{
    n = read(), m = read(), k = read(), ans = 0;
    Get_mu();
    int nxt = 1;
	int ans = 0;
    for (int i = 1; i <= min(n, m); i = nxt + 1)
    {
		nxt = min(n / (n / i), m / (m / i));
        ans += (f(nxt) - f(i - 1)) * (n / i) * F(m / i);
    }
    printf ("%lld\n", ans);
}
