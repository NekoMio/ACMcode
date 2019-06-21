#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MOD = 998244353;
const int MAXN = 2000005;
char s[705];
int mp[705][705], n, m;
int OK[705][705];
bool vis[705][705];
int dx[4] = {1,-1,0,0},
    dy[4] = {0,0,1,-1};
struct Point
{
    int x, y;
    Point(int _x = 0, int _y = 0): x(_x), y(_y) {}
}S, E;
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
int rev[MAXN];
int Inv, N;
void FFT(int *a, int op)
{
	int w, wn, t;
	for (int i = 1; i < N; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
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
int a[MAXN], b[MAXN], c[MAXN], lena, lenb, lenc;
void SetOK(int t)
{
	int y = t % m, x = t / m + 1;
	if (y == 0) y = m, x--;
	OK[x][y] = 1;
}
bool Judge(int x)
{
	int x1 = x / m + 1;
	if (x % m == 0) x1--;
	int t = E.y - S.y + 1;
	int x2 = (x - t + 1) / m + 1;
	if ((x - t + 1) % m == 0) x2--;
	return x2 == x1;
}
int main()
{
	n = read(), m = read();
	S.x = 0x3f3f, S.y = 0x3f3f;
	int Size = 0;
	for (int i = 1; i <= n; i++)
    {
        scanf ("%s", s + 1);
        for (int j = 1; j <= m; j++)
        {
            if (s[j] == '#')
                mp[i][j] = 1;
            else if (s[j] == 'o')
			{
				mp[i][j] = -1;
				Size++;
				S.x = min(S.x, i), S.y = min(S.y, j);
				E.x = max(E.x, i), E.y = max(E.y, j);
			}
        }
    }
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[++lena] = (mp[i][j] == 0 || mp[i][j] == -1);
	for (int i = S.x; i <= E.x; i++)
		for (int j = (i == S.x ? S.y : 1); j <= (i == E.x ? E.y : m); j++)
			c[++lenc] = b[++lenb] = (mp[i][j] == -1);
	reverse(b + 1, b + lenb + 1);
	int M = n * m;
	N = 1;
	// for (int i = 1; i <= lena; i++) printf ("%d ", a[i]);
	// printf ("\n");
	// for (int i = 1; i <= lenb; i++) printf ("%d ", b[i]);
	// printf ("\n");
	while (N <= M) N <<= 1;
	for (int i = 1; i <= N; i++)
		if (i & 1)
			rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
		else
			rev[i] = (rev[i >> 1] >> 1);
	Inv = pow_mod(N, MOD - 2);
	FFT(a, 1), FFT(b, 1);
	for (int i = 0; i < N; i++) a[i] = 1ll * a[i] * b[i] % MOD;
	FFT(a, -1);
	// for (int i = 0; i < N; i++) printf ("%d ", a[i]);
	// printf ("\n");
	for (int i = lenb; i < N; i++)
		if (a[i] == Size && Judge(i - 1))
			SetOK(i - lenb);
	// for (int i = 1; i <= n; i++)
	// {
		// for (int j = 1; j <= m; j++)
			// printf ("%d ", OK[i][j]);
		// printf ("\n");
	// }
	queue<Point> Q;
	Q.push(S);
	vis[S.x][S.y] = 1;
	while (!Q.empty())
	{
		Point x = Q.front(); Q.pop();
		for (int i = 0; i <= 3; i++)
		{
			if (!OK[x.x + dx[i]][x.y + dy[i]] || vis[x.x + dx[i]][x.y + dy[i]]) continue;
			vis[x.x + dx[i]][x.y + dy[i]] = 1;
			Q.push(Point(x.x + dx[i], x.y + dy[i]));
		}
	}
	// for (int i = 1; i <= n; i++)
	// {
		// for (int j = 1; j <= m; j++)
			// printf ("%d ", vis[i][j] ? 1 : 0);
		// printf ("\n");
	// }
	lena = 0;
	memset (a, 0, sizeof (a));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[++lena] = vis[i][j];
	for (int i = lena + 1; i < N; i++) a[i] = 0;
	FFT(a, 1), FFT(c, 1);
	for (int i = 0; i < N; i++) a[i] = 1ll * a[i] * c[i] % MOD;
	FFT(a, -1);
	// for (int i = 0; i < N; i++) printf ("%d ", a[i]);
	int ans = 0;
	for (int i = 0; i < N; i++) if (a[i]) ans++;
	printf ("%d\n", ans);
	// while (1);
}