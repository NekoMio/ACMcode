#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 1e5 + 5;
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
int F[MAXN][101][2][2];
int g[101][2][2], n, k;
int size[MAXN];
void DP(int rt, int fa)
{
	F[rt][1][0][1] = F[rt][0][0][0] = size[rt] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DP(v[i].END, rt);
		for (int j = 0; j <= k; j++) g[j][0][0] = g[j][1][0] = g[j][0][1] = g[j][1][1] = 0;
		for (int j = 0; j <= k && j <= size[rt]; j++)
			for (int l = 0; l + j <= k && l <= size[v[i].END]; l++)
			{
				g[j + l][1][1] = (g[j + l][1][1] + 1ll * F[rt][j][1][1] * F[v[i].END][l][0][0] % MOD) % MOD;
				g[j + l][1][1] = (g[j + l][1][1] + 1ll * F[rt][j][1][1] * F[v[i].END][l][0][1] % MOD) % MOD;
				g[j + l][1][1] = (g[j + l][1][1] + 1ll * F[rt][j][1][1] * F[v[i].END][l][1][0] % MOD) % MOD;
				g[j + l][1][1] = (g[j + l][1][1] + 1ll * F[rt][j][1][1] * F[v[i].END][l][1][1] % MOD) % MOD;
				g[j + l][1][1] = (g[j + l][1][1] + 1ll * F[rt][j][0][1] * F[v[i].END][l][0][1] % MOD) % MOD;
				g[j + l][1][1] = (g[j + l][1][1] + 1ll * F[rt][j][0][1] * F[v[i].END][l][1][1] % MOD) % MOD;
				g[j + l][1][0] = (g[j + l][1][0] + 1ll * F[rt][j][1][0] * F[v[i].END][l][1][0] % MOD) % MOD;
				g[j + l][1][0] = (g[j + l][1][0] + 1ll * F[rt][j][1][0] * F[v[i].END][l][1][1] % MOD) % MOD;
				g[j + l][1][0] = (g[j + l][1][0] + 1ll * F[rt][j][0][0] * F[v[i].END][l][1][1] % MOD) % MOD;
				g[j + l][0][1] = (g[j + l][0][1] + 1ll * F[rt][j][0][1] * F[v[i].END][l][1][0] % MOD) % MOD;
				g[j + l][0][1] = (g[j + l][0][1] + 1ll * F[rt][j][0][1] * F[v[i].END][l][0][0] % MOD) % MOD;
				g[j + l][0][0] = (g[j + l][0][0] + 1ll * F[rt][j][0][0] * F[v[i].END][l][1][0] % MOD) % MOD;
			}
		for (int j = 0; j <= k; j++)
			F[rt][j][0][0] = g[j][0][0],
			F[rt][j][0][1] = g[j][0][1],
			F[rt][j][1][0] = g[j][1][0],
			F[rt][j][1][1] = g[j][1][1];
		size[rt] += size[v[i].END];
	}
}
int main()
{
	memset (first, -1, sizeof (first));
	n = read(), k = read();
	for (int i = 1; i <= n - 1; i++)
	{
		int a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	DP(1, 0);
	printf ("%d", (F[1][k][1][1] + F[1][k][1][0]) % MOD);
}
