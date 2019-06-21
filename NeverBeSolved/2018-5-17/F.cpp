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
const int MAXN = 5e4 + 5;
const int MOD  = 998244353;
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
int f[MAXN][250], g[MAXN][250], n, m;
int tmp1[450], tmp2[450], size[MAXN];
void DFS(int rt, int fa)
{
	size[rt] = 0;
	memset (f[rt], 0, sizeof (f[rt]));
	memset (g[rt], 0, sizeof (g[rt]));
	f[rt][0] = 1;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS(v[i].END, rt);
		memset (tmp1, 0, sizeof (tmp1));
		memset (tmp2, 0, sizeof (tmp2));
		// for (int j = 0; j <= size[rt] + size[v[i].END]; j++) tmp1[j] = tmp2[j] = 0;
		for (int j = 0; j <= size[rt]; j++)
			for (int k = 0; k <= size[v[i].END]; k++)
			{
				tmp1[j + k] = (tmp1[j + k] + 1ll * f[rt][j] * f[v[i].END][k] + 2ll * f[rt][j] * g[v[i].END][k]) % MOD;
				tmp2[j + k] = (tmp2[j + k] + 2ll * g[rt][j] * g[v[i].END][k] + 2ll * g[rt][j] * f[v[i].END][k]) % MOD;
				tmp2[j + k + 1] = (tmp2[j + k + 1] + 1ll * f[rt][j] * f[v[i].END][k]) % MOD;
			}
		size[rt] = (size[rt] + size[v[i].END]) > m ? m : (size[rt] + size[v[i].END]);
		for (int j = 0; j < m; j++)
		{
			f[rt][j] = (tmp1[j] + tmp1[j + m]) % MOD;
			g[rt][j] = (tmp2[j] + tmp2[j + m]) % MOD;
		}
	}
	size[rt] = (size[rt] + 1) > m ? m : (size[rt] + 1);
}
int main()
{
	int t = read();
	while (t--)
	{
		n = read(), m = read();
		for (int i = 1; i <= n; i++) first[i] = -1;
		p = 0;
		for (int i = 1; i < n; i++)
		{
			int a = read(), b = read();
			add(a, b);
			add(b, a);
		}
		DFS(1, 0);
		printf ("%d\n", (f[1][0] + g[1][0]) % MOD);
	}
}

