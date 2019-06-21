#include <cstdio>
#include <cstring>
#include <algorithm>

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
using namespace std;
const int MAXN = 5005;

#define int long long

struct edge
{
	int END, next;
}v[MAXN];
int first[MAXN], p;
int c[MAXN], d[MAXN];
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}

int f[MAXN][MAXN][2];
int size[MAXN], tmp[MAXN][2];

void DP(int x)
{
	f[x][0][0] = 0;
	f[x][1][0] = c[x];
	f[x][1][1] = c[x] - d[x];
	size[x] = 1;
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		DP(v[i].END);
		for (int j = 0; j <= size[x] + size[v[i].END]; j++) tmp[j][1] = tmp[j][0] = 0x3f3f3f3f;
		for (int j = 0; j <= size[x]; j++)
		{
			for (int k = 0; k <= size[v[i].END]; k++)
			{
				tmp[j + k][0] = min(tmp[j + k][0], f[x][j][0] + f[v[i].END][k][0]);
				tmp[j + k][1] = min(tmp[j + k][1], f[x][j][1] + min(f[v[i].END][k][0], f[v[i].END][k][1]));
			}
		}
		for (int j = 0; j <= size[x] + size[v[i].END]; j++) f[x][j][0] = tmp[j][0], f[x][j][1] = tmp[j][1];
		size[x] += size[v[i].END];
	}
}
signed main()
{
	// freopen ("supermarket.in", "r", stdin);
	// freopen ("supermarket.out", "w", stdout);
	int n = read(), b = read();
	memset (first, -1, sizeof (first));
	memset (f, 0x3f, sizeof (f));
	c[1] = read(), d[1] = read();
	for (int i = 2; i <= n; i++)
		c[i] = read(), d[i] = read(), add(read(), i);
	DP(1);
	for (int i = n; i >= 0; i--)
		if (min(f[1][i][0], f[1][i][1]) <= b) 
		{
			printf ("%lld\n", i);
			break;
		}
}
