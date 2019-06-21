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
const int MAXN = (2e2 + 5) * 4;
// const int MAXN = (6e4 + 5) * 4;
const int P = 1000003;
// const int P = 998244353;
const int L = (1 << 10) + 1;
const int LM = (1 << 10) + 1;
// const int L = (1 << 18) + 1;
// const int LM = (1 << 16) + 1;
int X[MAXN], A[MAXN];
long long pow_mod(long long a, int b, int p)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return ans;
}
int sta[MAXN];
int N;
int Calc(int x)
{
    N = 1;
    while (N < (x << 1)) N <<= 1;
    return N;
}
struct FFT
{
	int Inv, rev[MAXN];
	int MOD;
	void Init(int x)
	{
		N = 1;
		while (N < (x << 1)) N <<= 1;
		Inv = pow_mod(N, MOD - 2, MOD);
		for (int i = 1; i < N; i++)
		    if (i & 1)
		        rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
		    else
		        rev[i] = (rev[i >> 1] >> 1);
	}
	void Init2(int x)
	{
		N = 1;
		while (N < x) N <<= 1;
		Inv = pow_mod(N, MOD - 2, MOD);
		for (int i = 1; i < N; i++)
		    if (i & 1)
		        rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
		    else
		        rev[i] = (rev[i >> 1] >> 1);
	}
	void FFt(int *a, int op)
	{
		int w, wn, t;
		for (int i = 0; i < N; i++)
			if (i < rev[i])
				swap(a[i], a[rev[i]]);
		for (int k = 2; k <= N; k <<= 1)
		{
			wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k, MOD);
			for (int j = 0; j < N; j += k)
			{
				w = 1;
				for (int i = 0; i < (k >> 1); i++, w = 1ll * w * wn % MOD)
				{
					t = 1ll * a[i + j + (k >> 1)] * w % MOD;
					a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
					a[i + j] = (a[i + j] + t) % MOD;
				}
			}
		}
		if (op == -1)
			for (int i = 0; i < N; i++)
				a[i] = 1ll * a[i] * Inv % MOD;
	}
}GF[2];
int tmp[2][MAXN];
long long add(long long a, long long b, long long P)
{
	a %= P, b %= P;
	long long ans = 0;
	while (b)
	{
		if (b & 1) ans = (ans + a) % P;
		b >>= 1;
		a = (a + a) % P;
	}
	return ans;
}
long long CRT(int *a, int *b, int n)
{
    long long N = 1, Ni, now, ans = 0;
    for (int i = 0; i <= n; i++) N *= a[i];
    // printf ("\n");
    // printf ("%lld\n", N);
    for (int i = 0; i <= n; i++)
    {
        Ni = N / a[i];
        now = pow_mod(Ni, a[i] - 2, a[i]);
        // printf ("%lld\n", now);
        ans = (ans + add(b[i] * now % N, Ni, N)) % N;
        // printf ("%lld\n", b[i] * now);
        // printf ("%lld\n", add(b[i] * now % N, Ni, N));
    }
    return ans % P;
}
int Z[5], T[5];
void Get_Inv(int *a, int b[2][MAXN], int n)
{
	if (n == 1) return b[0][0] = pow_mod(a[0], P - 2, P), b[1][0] = pow_mod(a[0], P - 2, P), void();
	Get_Inv(a, b, (n + 1) >> 1);
	GF[0].Init(n), GF[1].Init(n);
	for (int i = 0; i < n; i++) tmp[0][i] = tmp[1][i] = a[i];
	for (int i = n; i < N; i++) tmp[0][i] = tmp[1][i] = 0;
	// for (int i = 0; i < n; i++) printf ("%d ", tmp[0][i]);
	// printf("\n");
	GF[0].FFt(tmp[0], 1);
	// printf ("---------------");
	// for (int i = 0; i < N; i++) printf ("%d ", tmp[0][i]);
	// printf ("\n");
	GF[1].FFt(tmp[1], 1);
	GF[0].FFt(b[0], 1);
	GF[1].FFt(b[1], 1);
	for (int i = 0; i < N; i++) 
	    b[0][i] = 1ll * b[0][i] * ((2 - 1ll * b[0][i] * tmp[0][i] % GF[0].MOD + GF[0].MOD) % GF[0].MOD) % GF[0].MOD;
	for (int i = 0; i < N; i++) 
	    b[1][i] = 1ll * b[1][i] * ((2 - 1ll * b[1][i] * tmp[1][i] % GF[1].MOD + GF[1].MOD) % GF[1].MOD) % GF[1].MOD;
	GF[0].FFt(b[0], -1);
	GF[1].FFt(b[1], -1);
	for (int i = 0; i < n; i++)
	{
		Z[0] = b[0][i], Z[1] = b[1][i];
		// printf ("%d\n", Z[0]);
		b[0][i] = b[1][i] = CRT(T, Z, 1);
	}
	for (int i = n; i < N; i++) b[0][i] = b[1][i] = 0;
}
int Get_mod(int *a, int ra, int *b, int rb, int *c)
{
	while (ra && !a[ra - 1]) --ra;
	while (rb && !b[rb - 1]) --rb;
	if (ra < rb)
	{
	    memcpy (c, a, ra << 2);
	    memset (c + ra, 0, (rb - ra) << 2);
	    return rb;
	}
	static int tmp1[2][MAXN], tmp2[2][MAXN];
	int rc = ra - rb + 1;
	int l = Calc(rc);
	for (int i = 0; i < l; i++) tmp1[0][i] = 0;
	reverse_copy(b, b + rb, tmp1[0]);
	for (int i = 0; i < l; i++) tmp2[0][i] = 0;
	for (int i = 0; i < l; i++) tmp2[1][i] = 0;
	// for (int i = 0; i < rb; i++) printf ("1: %d, tmp1: %d\n", rb, tmp1[i]);    
	Get_Inv(tmp1[0], tmp2, rc);
	// for (int i = 0; i < rc; i++) printf ("%d\n", tmp2[0][i]);
	for (int i = rc; i < l; i++) tmp2[0][i] = 0;
	for (int i = rc; i < l; i++) tmp2[1][i] = 0;
	reverse_copy(a, a + ra, tmp1[0]);
	reverse_copy(a, a + ra, tmp1[1]);
	for (int i = rc; i < l; i++) tmp1[0][i] = 0;
	for (int i = rc; i < l; i++) tmp1[1][i] = 0;
	GF[0].Init(rc), GF[1].Init(rc);
	GF[0].FFt(tmp1[0], 1);
	GF[1].FFt(tmp1[1], 1);
	GF[0].FFt(tmp2[0], 1);
	GF[1].FFt(tmp2[1], 1);
	for (int i = 0; i < N; i++) tmp1[0][i] = 1ll * tmp1[0][i] * tmp2[0][i] % GF[0].MOD;
	for (int i = 0; i < N; i++) tmp1[1][i] = 1ll * tmp1[1][i] * tmp2[1][i] % GF[1].MOD;
	GF[0].FFt(tmp1[0], -1);
	GF[1].FFt(tmp1[1], -1);
	for (int i = 0; i < rc; i++)
	{
		Z[0] = tmp1[0][i], Z[1] = tmp1[1][i];
		tmp1[0][i] = CRT(T, Z, 1);
	}
	// for (int i = 0; i < rb; i++) printf ("2: %d, tmp1: %d\n", rb, tmp1[i]);    
	reverse(tmp1[0], tmp1[0] + rc);
	copy(tmp1[0], tmp1[0] + rc, tmp1[1]);
	// for (int i = 0; i < rb; i++) printf ("3: %d, tmp1: %d\n", rb, tmp1[i]);    
	GF[0].Init(ra), GF[1].Init(ra);
	for (int i = 0; i < rb; i++) tmp2[0][i] = b[i];
	for (int i = 0; i < rb; i++) tmp2[1][i] = b[i];
	for (int i = rb; i < N; i++) tmp2[0][i] = tmp2[1][i] = 0;
	for (int i = rc; i < N; i++) tmp1[0][i] = tmp1[1][i] = 0;
	GF[0].FFt(tmp1[0], 1);
	GF[1].FFt(tmp1[1], 1);
	GF[0].FFt(tmp2[0], 1);
	GF[1].FFt(tmp2[1], 1);
	for (int i = 0; i < N; i++) tmp1[0][i] = 1ll * tmp1[0][i] * tmp2[0][i] % GF[0].MOD;
	for (int i = 0; i < N; i++) tmp1[1][i] = 1ll * tmp1[1][i] * tmp2[1][i] % GF[1].MOD;
	GF[0].FFt(tmp1[0], -1);
	GF[1].FFt(tmp1[1], -1);
	for (int i = 0; i < rb; i++)
	{
		Z[0] = tmp1[0][i], Z[1] = tmp1[1][i];
		tmp1[0][i] = CRT(T, Z, 1);
	}
	// for (int i = 0; i < rb; i++) printf ("4: %d, tmp1: %d\n", rb, tmp1[i]);
	for (int i = 0; i < rb; i++) c[i] = (a[i] - tmp1[0][i] + P) % P;
	for (int i = rb; i < N; i++) c[i] = 0;
	// for (int i = 0; i < rb; i++) printf ("C: %d, %d\n", rb, c[i]);
	while (rb && !c[rb - 1]) --rb;
	return rb;
}
int *p[2][L];
int mem[2][L << 2], *head[2] = {mem[0], mem[1]};
inline int Solve1(int id, int l, int r)
{
	int ra = r - l + 2;
	if (ra <= 2)
	{
	    int *f0 = p[0][id] = head[0]; head[0] += ra;
	    int *f1 = p[1][id] = head[1]; head[1] += ra;
	    memset (f0, 0, ra << 2), 0[f0] = 1;
	    memset (f1, 0, ra << 2), 0[f1] = 1;
	    for (int i = l; i <= r; i++)
	        for (int v = (P - sta[i]) % P, j = i - l; j != -1; j--)
	            f1[j + 1] = f0[j + 1] = (f0[j + 1] + f0[j]) % P, f1[j] = f0[j] = 1ll * f0[j] * v % P;
	    return ra;
	}
	int mid = (l + r) >> 1;
	int r1 = Solve1(id << 1, l, mid), *f01 = p[0][id << 1], *f11 = p[1][id << 1];
	int r2 = Solve1(id << 1 | 1, mid + 1, r), *f02 = p[0][id << 1 | 1], *f12 = p[1][id << 1 | 1];
	GF[0].Init2(ra), GF[1].Init2(ra);
	static int tmp1[2][LM], tmp2[2][LM];
	memcpy(tmp1[0], f01, r1 << 2), memset (tmp1[0] + r1, 0, (N - r1) << 2), GF[0].FFt(tmp1[0], 1);
	memcpy(tmp1[1], f11, r1 << 2), memset (tmp1[1] + r1, 0, (N - r1) << 2), GF[1].FFt(tmp1[1], 1);
	memcpy(tmp2[0], f02, r2 << 2), memset (tmp2[0] + r2, 0, (N - r2) << 2), GF[0].FFt(tmp2[0], 1);
	memcpy(tmp2[1], f12, r2 << 2), memset (tmp2[1] + r2, 0, (N - r2) << 2), GF[1].FFt(tmp2[1], 1);
	int *f0 = p[0][id] = head[0]; head[0] += ra;
	int *f1 = p[1][id] = head[1]; head[1] += ra;
	for (int i = 0; i < N; i++) f0[i] = 1ll * tmp1[0][i] * tmp2[0][i] % GF[0].MOD;
	for (int i = 0; i < N; i++) f1[i] = 1ll * tmp1[1][i] * tmp2[1][i] % GF[1].MOD;
	GF[0].FFt(f0, -1);
	GF[1].FFt(f1, -1);
	for (int i = 0; i < N; i++)
	{
		#ifdef Mine
		// printf ("%d %d\n", f0[i], f1[i]);
		#endif
		Z[0] = f0[i], Z[1] = f1[i];
		f0[i] = f1[i] = CRT(T, Z, 1);
		#ifdef Mine
			//printf ("%d\n", f0[i]);
		#endif
	}
	return ra; 
}
int val[LM];
void Solve2(int id, int *a, int l, int r, int deg)
{
	int ra = r - l + 2;
	if (deg <= 2)
	{
	    int F;
	    for (int i = l; i <= r; i++)
	    {
	        F = 0;
	        int u = sta[i], v = 1;
	        for (int j = 0; j <= deg; j++)
	        {
	            F = (F + 1ll * v * a[j]) % P;
	            v = 1ll * v * u % P;
	        }
	        val[i] = F;
	    }
	    return;
	}
	int mid = (l + r) >> 1;
	int r1 = Get_mod(a, deg, p[0][id], ra, a + deg); a += deg;
	ra = r1;
	Solve2(id << 1, a, l, mid, ra), Solve2(id << 1 | 1, a, mid + 1, r, ra);
}
int main()
{
	int n = read(), b = read(), c = read(), d = read(), e = read();
	for (int i = 0; i < n; i += 1)
		A[i] = read();
	for (int i = 0; i < n; i += 1)
		X[i] = (1ll * b * pow_mod(c, 4 * i, P) % P + 1ll * d * pow_mod(c, 2 * i, P) % P + e) % P;
	for (int i = 1; i <= n; i++) sta[i] = X[i - 1];
	sort(sta + 1, sta + n + 1);
	int lenth = unique(sta + 1, sta + n + 1) - sta - 1;
	for (int i = 0; i < n; i += 1)
		X[i] = lower_bound(sta + 1, sta + lenth + 1, X[i]) - sta;
	GF[0].MOD = 998244353;
	GF[1].MOD = 1004535809;
	T[0] = 998244353;
	T[1] = 1004535809;
	//A[0] = 1, A[1] = 415, A[2] = 10, A[3] = 1000, A[4] = 5464, A[5] = 14351, A[6] = 4545, A[7] = 10054, A[8] = 1154;
	//X[0] = 1564, X[1] = 75, X[2] = 1222, X[3] = 4555;
	//int len = Get_mod(A, 9, X, 4, val);
	//for (int i = 0; i < len; i++)
		//printf ("%d\n", val[i]);
	Solve1(1, 1, lenth);
	Solve2(1, A, 1, lenth, n + 1);
	#ifdef Mine
	// for (int i = 0; i <= 10000; i++)
		// printf ("%d %d\n", mem[0][i], mem[1][i]);
	#endif
	for (int i = 0; i < n; i += 1)
	{
		printf ("%d\n", val[X[i]]);
		//printf ("%lld %lld\n", ((1ll * GF[0].val[X[i]] * pow_mod(GF[1].MOD, GF[0].MOD - 2, GF[0].MOD)) % P), ((1ll * GF[1].val[X[i]] * pow_mod(GF[0].MOD, GF[1].MOD - 2, GF[1].MOD)) % P) % P);
	}
	// Z[0] = 54168304, Z[1] = 490293876;
	// printf ("%lld\n", CRT(T, Z, 1));
}
