#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
#define int long long
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e7;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int tot;
int pr[50], num[50];
inline int mul(int x,int y,int z)
{
	return (x*y-(int)(((long double)x*y+0.5)/(long double)z)*z+z)%z;
}
int pow_mod(long long a, int b, int MOD)
{
	a = a % MOD;
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, a, MOD);
		b >>= 1;
		a = mul(a, a, MOD);
	}
	return ans;
}
bool Miller_Rabin(int x)
{
	if (x == 1) return 0;
	for (int j = 0; j <= 9; j++)
		if (x % prime[j] == 0 && x != prime[j])
			return 0;
	int y = x - 1;
	int k = 0;
	for (; !(y & 1); y >>= 1) k++;
	for (int i = 0; i <= 10; i++)
	{
		int z = rand() % (x - 1) + 1;
		int c = pow_mod(z, y, x), d;
		for (int j = 0; j < k; j++, c = d)
			if ((d = mul(c, c, x)) == 1 && c != 1 && c != x - 1)
				return 0;
		if (d != 1) return 0;
	}
	return 1;
}
int Pollard_Rho(int x, int y)
{
	int i = 1, k = 2, c = rand() % (x - 1) + 1;
	int d = c;
	while (1)
	{
		i++;
		c = (mul(c, c, x) + y) % x;
		int g = __gcd((d - c + x) % x, x);
		if (g != 1 && g != x) return g;
		if (c == d) return x;
		if (i == k) d = c, k <<= 1;
	}
}
int tmp[50];
void Divide(int x, int c)
{
	if (x == 1) return;
	if (Miller_Rabin(x)) return tmp[++tot] = x, void();
	int z = x, tp = c;
	while (z >= x) z = Pollard_Rho(z, c--);
	Divide(z, tp), Divide(x / z, tp);
}
int DFS(int x, int k, int len, int val, int p)
{
	if (x == tot + 1)
	{
		if (len & 1) return len % p * pow_mod(k, (len + 1) / 2, p) % p * val % p;
		else return (len / 2) % p * pow_mod(k, len / 2, p) % p * val % p;
	}
	int nxt = ((1 - pr[x]) % p * val % p + p) % p;
	int ans = 0;
	if (pr[x] != 2)
		ans = (ans + DFS(x + 1, k, len, nxt, p)) % p;
	for (int i = 1; i < num[x]; i++)
		ans = (ans + DFS(x + 1, k, len *= pr[x], nxt, p)) % p;
	return (ans + DFS(x + 1, k, len *= pr[x], val, p)) % p;
}
int Query(int n, int k, int p)
{
	tot = 0;
	memset (num, 0, sizeof (num));
	Divide(n, 100000);
	sort(tmp + 1, tmp + tot + 1);
	int m = 0;
	for (int i = 1; i <= tot; i++)
	{
		if (tmp[i] != tmp[i - 1])
			pr[++m] = tmp[i];	
		num[m]++;
	}
	tot = m;
	return DFS(1, k, 1, 1, p);
}
signed main()
{
	int T = read();
	while (T--)
	{
		int n = read(), k = read(), p = read();
		printf ("%lld\n", Query(n, k, p));
	}
}
