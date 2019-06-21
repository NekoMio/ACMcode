#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 100005;
const int MOD = 1e9 + 7;
struct edge
{
	int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int size[MAXN];
int dis[MAXN], n;
void DFS1(int rt, int fa)
{
	size[rt] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS1(v[i].END, rt);
		size[rt] += size[v[i].END];
		dis[rt] = (dis[rt] + dis[v[i].END] + size[v[i].END]) % MOD;
	}
}
void DFS2(int rt, int fa, int t)
{
	dis[rt] = (dis[rt] + t) % MOD;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS2(v[i].END, rt, ((n - 2 * size[v[i].END] + dis[rt] - dis[v[i].END]) % MOD + MOD) % MOD);
	}
}
char s[MAXN];
int pow_mod(long long a, int b)
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
int X, Y;
struct data
{
	int a, b, c;
	data(int _a = 0, int _b = 0, int _c = 0): a(_a), b(_b), c(_c) {}
	data operator + (int x)
	{
		return data(a, b, (c + x) % MOD);
	}
	data operator - (int x)
	{
		return data(a, b, (c - x + MOD) % MOD);
	}
	data operator + (const data &x)
	{
		return data((a + x.a) % MOD, (b + x.b) % MOD, (c + x.c) % MOD);
	}
	data operator - (const data &x)
	{
		return data((a - x.a + MOD) % MOD, (b - x.b + MOD) % MOD, (c - x.c + MOD) % MOD);
	}
	data operator * (int x)
	{
		return data(1ll * a * x % MOD, 1ll * b * x % MOD, 1ll * c * x % MOD);
	}
	int Calc()
	{
		return (1ll * a * X % MOD + 1ll * b * Y % MOD + c) % MOD;
	}
}val[MAXN][2], F[2];
int main()
{
	memset (first, -1, sizeof (first));
	n = read();
	scanf ("%s", s + 1);
	for (int i = 2; i <= n; i++)
	{
		int x = read();
		add(i, x);
		add(x, i);
	}
	DFS1(1, 0);
	// fprintf (stderr, "-------------------\n");
	DFS2(1, 0, 0);
	val[1][0].a = 1, val[1][1].b = 1;
	for (int i = 1; i < n - 1; i++)
	{
		if (i == 1)
			val[i + 1][1] = (val[i][1] * n - val[i - 1][1] * (i - 1) - val[i - 1][0]) * pow_mod(n - i, MOD - 2);
		else
			val[i + 1][1] = (val[i][1] * n - 1 - val[i - 1][1] * (i - 1) - val[i - 1][0]) * pow_mod(n - i, MOD - 2);
		val[i + 1][0] = (val[i][0] * n - 1 - val[i - 1][0] * i - val[i + 1][1]) * pow_mod(n - i - 1, MOD - 2);
		// cout << val[i + 1][1].a << " " << val[i + 1][1].b << " " << val[i + 1][1].c << endl;
		// cout << val[i + 1][0].a << " " << val[i + 1][0].b << " " << val[i + 1][0].c << endl;
	}
	int Invn = pow_mod(n, MOD - 2);
	F[0] = val[n - 1][1] - Invn * (n - 1 != 1) - val[n - 2][1] * (n - 2) * Invn - val[n - 2][0] * Invn;
	F[1] = val[n - 1][0] - val[n - 2][0] * (n - 1) * Invn;
	// cout << F[0].a << " " << F[0].b << " " << F[0].c << endl;
	// cout << F[1].a << " " << F[1].b << " " << F[1].c << endl; 
	X = 1ll * ((MOD - F[0].c + 1ll * F[0].b * F[1].c % MOD * pow_mod(F[1].b, MOD - 2) % MOD) % MOD + MOD) % MOD * pow_mod((F[0].a - 1ll * F[0].b * F[1].a % MOD * pow_mod(F[1].b, MOD - 2) % MOD + MOD) % MOD, MOD - 2) % MOD;
	Y = 1ll * (((-F[0].c - 1ll * F[0].a * X % MOD) % MOD + MOD) % MOD) * pow_mod(F[0].b, MOD - 2) % MOD;
	// cout << X << " " << Y << endl;
	int Cnt = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == '1') Cnt++;
	int T0 = val[Cnt][0].Calc(), T1 = val[Cnt][1].Calc();
	
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == '1')
			ans = (ans + 1ll * (T1 + Invn) * dis[i] % MOD * Invn % MOD) % MOD;
		else
			ans = (ans + 1ll * (T0 + Invn) * dis[i] % MOD * Invn % MOD) % MOD;
	printf ("%d\n", ans);
}
