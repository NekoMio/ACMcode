#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline void gmin(int &a, int b) { if (a > b) a = b; }
inline void gmax(int &a, int b) { if (a < b) a = b; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const int MAXN = 1000005;
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
int N, Inv;
int rev[MAXN];
void Init(int n)
{
	N = 1;
	while (N < n) N <<= 1;
	Inv = pow_mod(N, MOD - 2);
	for (int i = 1; i < N; i++)
		if (i & 1)
			rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
		else
			rev[i] = (rev[i >> 1] >> 1);
}
void FFT(int *a, int op)
{
	for (int i = 1; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	int wn, w, t;
	for (int k = 2; k <= N; k <<= 1)
	{
		wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
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
int A[MAXN], B[MAXN], C[MAXN], n, m;
char mp[505];
#define In(_) ((_) / NC + 1)
int main()
{
	int NR = read(), NC = read();
	for (int i = 1; i <= NR; i++)
	{
		scanf ("%s", mp + 1);
		for (int j = 1; j <= NC; j++)
			A[(i - 1) * NC + j - 1] = (mp[j] == 'G' ? 1 : -1);
	}
	n = NR * NC;
	int b = read();
	while (b--)
	{
		int r = read(), c = read();
		memset (B, 0, sizeof (B));
		memset (C, 0, sizeof (C));
		for (int i = 1; i < r; i++)
		{
			scanf ("%s", mp + 1);
			for (int j = 1; j <= c; j++)
				B[(i - 1) * NC + j - 1] = (mp[j] == 'G' ? 1 : -1);
			for (int j = c + 1; j <= NC; j++)
				B[(i - 1) * NC + j - 1] = 0;
		}
		int t = r * c;
		scanf ("%s", mp + 1);
		for (int i = 1; i <= c; i++)
			B[(r - 1) * NC + i - 1] = (mp[i] == 'G' ? 1 : -1);
		m = (r - 1) * NC + c;
		reverse(B, B + m);
		Init(n + m);
		FFT(A, 1), FFT(B, 1);
		for (int i = 0; i < N; i++) C[i] = 1ll * A[i] * B[i] % MOD;
		FFT(C, -1), FFT(A, -1);
		int ans = 0, x, y;
		for (int i = m - 1; i < n; i++)
			if (In(i) == In(i - c + 1))
			{
				int tmp = ((C[i] + t) % MOD) / 2;
				if (tmp > ans)
				{
					ans = tmp;
					x = In(i - m + 1);
					y = (i - m + 1) % NC + 1;
				}
			}
		printf ("%d %d\n", x, y);
	}
}
