#pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 2000;
const int MOD = 64123;
int d[MAXN];
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
int f[MAXN][MAXN], g[MAXN], tmp[MAXN];
int size[MAXN], K;
int Ans = 0;
void DFS(int rt, int fa, int c)
{
	if (d[rt] >= c) f[rt][1] = 1, f[rt][0] = 0;
	else f[rt][1] = 0, f[rt][0] = 1;
	if (d[rt] >= c) size[rt] = 1;
	else size[rt] = 0;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS(v[i].END, rt, c);
		for (int j = min(K, size[rt] + size[v[i].END]); j >= 0; j--)
			tmp[j] = f[rt][j];
		for (int j = min(K, size[rt]); j >= 0; j--)
			if (tmp[j])
				for (int k = min(K, size[v[i].END]); k >= 0; k--)
					if (f[v[i].END][k]) 
						f[rt][min(K, j + k)] = (f[rt][min(K, j + k)] + 1ll * tmp[j] * f[v[i].END][k]) % MOD;
		size[rt] += size[v[i].END];
	}
	Ans = (Ans + f[rt][K]) % MOD;
	// for (int i = K; i <= size[rt]; i++)
		// g[c] = (g[c] + f[rt][i]) % MOD;
	// f[rt][0]++;
}
int Sum[MAXN];
int main()
{
	// freopen ("data13.in", "r", stdin);
	// freopen ("data.out", "w", stdout);
	memset (first, -1, sizeof (first));
	int n = read(); K = read(); int W = read();
	for (int i = 1; i <= n; i++)
		d[i] = read(), Sum[d[i]]++;
	for (int i = 1; i <= n - 1; i++)
	{
		int a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	for (int i = W; i >= 1; i--) Sum[i] += Sum[i + 1];
	for (int i = W; i >= 1; i--)
	if (Sum[i] >= K)
	{
		// if (Sum[i] == Sum[i + 1])
		// {
		// 	// g[i] = g[i + 1];
		// 	continue;
		// }
		memset (f, 0, sizeof (f));
		DFS(1, 0, i);
		// Ans = (Ans + 1ll * (g[i] - g[i + 1]) * i) % MOD;
	}
	printf ("%d\n", (Ans + MOD) % MOD);
}
