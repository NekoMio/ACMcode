#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bitset<700> vis; 
const int MAXN = 100005;
const int N = 700;
int MOD;

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

int cnt[N], r[N], c[N];
int s[N], t[N], ct1, ct2;
int a[N][N];
void dfs(int rt)
{
	if (vis.test(rt)) return;
	vis.set(rt);
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		dfs(v[i].END);
		cnt[rt] += cnt[v[i].END];
		if (cnt[rt] > MOD) cnt[rt] -= MOD;
	}
}
int gauss()
{
	int n = ct2;
	int cnt = 0, ret = 1;
	for (int i = 1; i <= n; i++)
	{
		int t = -1;
		for (int j = i; j <= n; j++)
			if (a[j][i]) {t = j; break;} 
		if (t == -1) return 0;
		if (t != i) ++cnt;
		for (int j = 1; j <= n; j++)
			swap(a[i][j], a[t][j]);
		int Inv = pow_mod(a[i][i], MOD - 2);
		for (int j = i + 1; j <= n; j++)
			if (a[j][i]) 
			{
				int t = 1ll * a[j][i] * Inv % MOD;
				for (int k = i; k <= n; k++)
				{
					a[j][k] = (a[j][k] - 1ll * t * a[i][k] % MOD) % MOD;
					while (a[j][k] < 0) a[j][k] += MOD;
				}
			}
	}
	for (int i = 1; i <= n; i++) ret = 1ll * ret * a[i][i] % MOD;
	return cnt & 1 ? (MOD - ret) % MOD : ret;
}


int main()
{
	int n = read(), m = read();
	memset(first, -1, sizeof (first));
	MOD = read();
	int d, b;
	for (int i = 1; i <= m; i++)
	{
		d = read(), b = read();
		add(d, b);
		r[b]++, c[d]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if(r[i] == 0)
		{
			s[++ct1] = i;
		}
		if (c[i] == 0)
		{
			t[++ct2] = i;
		}
	}
	for (int i = 1; i <= ct2; i++)
	{
		vis.reset();
		memset(cnt, 0, sizeof (cnt));
		cnt[t[i]] = 1, vis.set(t[i]);
		for (int j = 1; j <= ct1; j++)
		{
			dfs(s[j]);
			a[j][i] = cnt[s[j]];
		}
	}
	printf ("%d\n", gauss());
}
