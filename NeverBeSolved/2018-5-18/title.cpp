#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const long long INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e7 + 5;
int a[MAXN], b[MAXN], pos[MAXN];
long long Sum[2500][250], val[2500][250], f[2500][250];
unsigned int SA, SB, SC;
int n, k, m, p, A, B, N;
unsigned int rng61()
{
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t = SA;
	SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC;
}
void gen()
{
	scanf ("%d%d%d%d%u%u%u%d%d", &n, &k, &m, &p, &SA, &SB, &SC, &A, &B);
	for (int i = 1; i <= p; i++) scanf("%d%d", &a[i], &b[i]);
	for (int i = p + 1; i <= n; i++)
	{
		a[i] = rng61() % A + 1;
		b[i] = rng61() % B + 1;
	}
}
int main()
{
	int T = read();
	while (T--)
	{
		gen();
		memset (Sum, 0, sizeof (Sum));
		int N = (1 << (k + 1));
		for (int i = 1; i <= n; i++)
		{
			if (i >= N) pos[i] = pos[i / N];
			else pos[i] = i;
			Sum[pos[i]][a[i] % m] += b[i];
		}
		for (int i = 1; i < N; i++)
			for (int j = 0; j < m; j++)
			{
				val[i][j] = 0;
				for (int k = 0; k < m; k++)
					val[i][j] = val[i][j] + Sum[i][k] * ((j - k + m) % m);
			}
		for (int i = min(N - 1, n); i >= 1; i--)
		{
			if (i >= (1 << k))
			{
				for (int j = 0; j < m; j++) f[i][j] = val[i][j];
				continue;
			}
			else
			{
				for (int j = 0; j < m; j++) f[i][j] = INF;
				for (int j = 0; j < m; j++)
					for (int l = 0; l < m; l++)
						f[i][(j + l) % m] = min(f[i][(j + l) % m], f[i << 1][j] + f[i << 1 | 1][j] + val[i][l]);
			}
		}
		printf ("%lld\n", f[1][0]);
	}
}
