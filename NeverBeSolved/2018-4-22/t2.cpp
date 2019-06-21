#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int MOD;
struct Hash_Table
{
	struct data
	{
		long long ans;
		long long x, y;
		int next;
	}v[100005];
	int first[76545], p;
	Hash_Table()
	{
		memset (first, -1, sizeof (first));
		p = 0;
	}
	void clear()
	{
		memset (first, -1, sizeof (first));
		p = 0;
	}
	long long &operator[](const long long &x)
	{
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return v[i].ans;
		v[p].x = x;
		v[p].next = first[H];
		first[H] = p++;
		return v[p - 1].ans = 0;
	}
	long long &operator()(const long long &x, const long long &y)
	{
		int H = (x % 9991) * (y % 10007) % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x && v[i].y == y)
				return v[i].ans;
		v[p].x = x;
		v[p].y = y;
		v[p].next = first[H];
		first[H] = p++;
		return v[p - 1].ans = 0;
	}
	bool count(const long long &x, const long long &y)
	{
		// printf ("%lld %lld\n", x, y);
		int H = (x % 9991) * (y % 10007) % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x && v[i].y == y)
				return 1;
		return 0;
	}
	bool count(const long long &x)
	{
		// printf ("%lld %lld\n", x, y);
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return 1;
		return 0;
	}
}Hash, mp, mpp;
struct Matrix
{
	long long a[3][3];
	int n;
	Matrix(int _n = 0)
	{
		n = _n;
		memset(a, 0, sizeof (a));
	}
	Matrix operator * (const Matrix &b)
	{
		Matrix ans(n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					ans.a[i][k] = (ans.a[i][k] + a[i][j] * b.a[j][k] % MOD) % MOD;
		return ans;
	}
	Matrix operator ^ (long long b)
	{
		Matrix ans(n), a = *this;
		for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
		while (b)
		{
			if (b & 1) ans = ans * a;
			b >>= 1;
			a = a * a;
		}
		return ans;
	}
	void print()
	{
		printf ("%lld %lld\n%lld %lld\n\n", a[1][1], a[1][2], a[2][1], a[2][2]);
	}
	void reset(int M = MOD)
	{
		a[1][1] = 3;
        a[1][2] = M - 1;
        a[2][1] = 1;
        a[2][2] = 0;
	}
	void set()
	{
		a[1][1] = a[2][2] = 1;
		a[2][1] = a[1][2] = 0;
		n = 2;
	}
}A(2), B(2);
int a, b;
bool isprime(long long x)
{
	for (long long i = 2; i * i <= x; i++)
		if (x % i == 0)
			return 0;
	return 1;
}
long long Cal(long long p)
{
	if (p % 10 == 1 || p % 10 == 9) return p - 1;
	if (mpp.count(p)) return mpp[p];
	MOD = p;
	A.reset(p);
	B.set();
	Hash.clear();
	int m = floor(sqrt(p));
	for (int i = 0; i < m; i++)
	{
		if (!Hash.count(B.a[1][1] * 1000000000 + B.a[1][2], B.a[2][1] * 1000000000 + B.a[2][2]))
			Hash(B.a[1][1] * 1000000000 + B.a[1][2], B.a[2][1] * 1000000000 + B.a[2][2]) = i;
		B = B * A;
	}
	Matrix S = A ^ m, d;
	d.set();
	for (int i = 1; ; i++)
	{
		d = d * S;
		if (Hash.count(d.a[1][1] * 1000000000 + d.a[1][2], d.a[2][1] * 1000000000 + d.a[2][2]))
		{
			return mpp[p] = 1ll * i * m - Hash(d.a[1][1] * 1000000000 + d.a[1][2], d.a[2][1] * 1000000000 + d.a[2][2]);
		}
	}
	return -1;
}
long long lcm(long long a, long long b)
{
	return a / __gcd(a, b) * b;
}
long long Calc(long long p)
{
	if (mp.count(p)) return mp[p];
	long long &ans = mp[p];
	ans = 1;
	for (int i = 2; i * i <= p; i++)
	{
		if (p % i == 0)
		{
			long long t = Cal(i);
			p /= i;
			while (p % i == 0) t = t * i, p = p / i;
			ans = lcm(ans, t);
		}
	}
	if (p != 1)
		ans = lcm(ans, Cal(p));
	return ans;
}
long long Solve(int n, int k, long long p, int t = 0)
{
	if (k == 1)
	{
		if (n == 0) return a;
		MOD = p;
		A.reset(p);
		A = A ^ (n - 1);
		return (b * A.a[1][1] % p + a * A.a[1][2] % p) % p;
	}
	else
	{
		long long z;
		if (t)
			z = Solve(n, k - 1, p, 1);
		else
		{
			long long T = Calc(p);
			if (T == p) z = Solve(n, k - 1, T, 1);
			else z = Solve(n, k - 1, T, 0);	
		}
		if (z == 0) return a;
		MOD = p;
		A.reset(p);
		A = A ^ (z - 1);
		return (b * A.a[1][1] % p + a * A.a[1][2] % p) % p;
	}
}
int main()
{
	int t = read();
	while (t--)
	{
		a = read(), b = read();
		int n = read(), k = read(), p = read();
		MOD = p;
		printf ("%lld\n", Solve(n, k, p));
	}
}
