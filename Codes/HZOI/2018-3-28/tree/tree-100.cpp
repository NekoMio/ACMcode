#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
// #define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 70005;
char op[10];
struct data
{
	int a, b;
}e[MAXN << 1];
struct edge
{
	int END, next, id;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].id = c;
	v[p].next = first[a];
	first[a] = p++;
}
int Dep[MAXN];
int st[MAXN << 1], L[MAXN], R[MAXN], Index, top, ID[MAXN];
void DFS(int rt, int fa)
{
	L[rt] = ++Index;
	ID[rt] = ++top;
	st[top] = rt;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		Dep[v[i].END] = Dep[rt] + 1;
		DFS(v[i].END, rt);
		st[++top] = rt;
	}
	R[rt] = Index;
}
int n;
struct BIT
{
	#define lowbit(_) ((_)&(-_))
	long long Sum[MAXN];
	void Update(int x, long long c)
	{
		for (int i = x; i <= n; i += lowbit(i))
			Sum[i] += c;
	}
	long long Query(int x)
	{
		long long ans = 0;
		for (int i = x; i >= 1; i -= lowbit(i))
			ans += Sum[i];
		return ans;
	}
}BT[300], SBT;
int block = 300;
int w[300][MAXN];
long long Sum[300], val[MAXN];
int in[MAXN], Lc[MAXN], Rc[MAXN];
int Min[MAXN << 1][20], id[MAXN << 1][20], Log[MAXN << 1];
int size[MAXN];
void DFS_BUILD(int x, int rt, int fa)
{
	if (rt >= Lc[x] && rt <= Rc[x])
		size[rt] = 1;
	else size[rt] = 0;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		DFS_BUILD(x, v[i].END, rt);
		w[x][v[i].id] = size[v[i].END];
		size[rt] += size[v[i].END];
	}
}
inline long long dis(int x)
{
	return SBT.Query(L[x]);
}
int lca(int a, int b)
{
	if (ID[a] > ID[b]) swap(a, b);
	int k = Log[ID[b] - ID[a] + 1];
	return Min[ID[a]][k] < Min[ID[b] - (1 << k) + 1][k] ? id[ID[a]][k] : id[ID[b] - (1 << k) + 1][k];
}
long long Query(int l, int r, int x)
{
	long long ans = 0;
	if (in[l] == in[r])
	{
		long long t = dis(x);
		for (int i = l; i <= r; i++)
			ans += dis(i) + t - 2 * dis(lca(i, x));
		return ans;
	}
	long long t = dis(x);
	for (int i = l; i <= Rc[in[l]]; i++)
		ans += dis(i) + t - 2 * dis(lca(i, x));
	for (int i = in[l] + 1; i <= in[r] - 1; i++)
		ans += Sum[i] + t * block - 2 * BT[i].Query(L[x]);
	for (int i = Lc[in[r]]; i <= r; i++)
		ans += dis(i) + t - 2 * dis(lca(i, x));
	return ans;
}
signed main()
{
	// freopen("tree_example_4.in", "r", stdin);
	// freopen("tree_example_4.out", "w", stdout);
	memset (first, -1, sizeof (first));
	int m, type;
	n = read(), m = read(), type = read();
	for (int i = 1; i <= n - 1; i++)
	{
		e[i].a = read(), e[i].b = read();
		val[i] = read();
		add(e[i].a, e[i].b, i);
		add(e[i].b, e[i].a, i);
	}
	DFS(1, 0);
	memset (Min, 0x3f, sizeof (Min));
	for (int i = 1; i <= top; i++) Min[i][0] = Dep[st[i]], id[i][0] = st[i];
	for (int i = 1; i <= 18; i++)
		for (int j = 1; j + (1 << (i - 1)) - 1 <= top; j++)
			if (Min[j][i - 1] < Min[j + (1 << (i - 1))][i - 1]) Min[j][i] = Min[j][i - 1], id[j][i] = id[j][i - 1];
			else Min[j][i] = Min[j + (1 << (i - 1))][i - 1], id[j][i] = id[j + (1 << (i - 1))][i - 1];
	Log[0] = -1;
	for (int i = 1; i <= top; i++) Log[i] = Log[i >> 1] + 1;
	for (int i = 1; i <= n; i++) in[i] = (i - 1) / block + 1;
	for (int i = 1; i <= n - 1; i++)
		if (Dep[e[i].a] > Dep[e[i].b])
			SBT.Update(L[e[i].a], val[i]), SBT.Update(R[e[i].a] + 1, -val[i]);
		else
			SBT.Update(L[e[i].b], val[i]), SBT.Update(R[e[i].b] + 1, -val[i]);
	int Cnt = in[n];
	for (int i = 1; i <= Cnt; i++) Lc[i] = block * (i - 1) + 1, Rc[i] = min(block * i, n);
	for (int i = 1; i <= Cnt; i++)
	{
		DFS_BUILD(i, 1, 0);
		for (int j = 1; j <= n - 1; j++)
			Sum[i] += 1ll * w[i][j] * val[j];
		for (int j = 1; j <= n - 1; j++)
		{
			if (!w[i][j]) continue;
			if (Dep[e[j].a] > Dep[e[j].b])
				BT[i].Update(L[e[j].a], 1ll * w[i][j] * val[j]), BT[i].Update(R[e[j].a] + 1, -1ll * w[i][j] * val[j]);
			else
				BT[i].Update(L[e[j].b], 1ll * w[i][j] * val[j]), BT[i].Update(R[e[j].b] + 1, -1ll * w[i][j] * val[j]);
		}
	}
	long long lastans = 0;
	while (m--)
	{
		scanf ("%s", op);
		lastans *= type;
		if (op[0] == 'm')
		{
			int x = read() ^ lastans, vt = read() ^ lastans;
			for (int i = 1; i <= Cnt; i++)
				if (w[i][x])
				{
					Sum[i] -= 1ll * w[i][x] * val[x];
					Sum[i] += 1ll * w[i][x] * vt;
					if (Dep[e[x].a] > Dep[e[x].b])
					{
						BT[i].Update(L[e[x].a], -1ll * w[i][x] * val[x]), BT[i].Update(R[e[x].a] + 1, 1ll * w[i][x] * val[x]);
						BT[i].Update(L[e[x].a], 1ll * w[i][x] * vt), BT[i].Update(R[e[x].a] + 1, -1ll * w[i][x] * vt);
					}
					else
					{
						BT[i].Update(L[e[x].b], -1ll * w[i][x] * val[x]), BT[i].Update(R[e[x].b] + 1, 1ll * w[i][x] * val[x]);
						BT[i].Update(L[e[x].b], 1ll * w[i][x] * vt), BT[i].Update(R[e[x].b] + 1, -1ll * w[i][x] * vt);
					}
				}
			if (Dep[e[x].a] > Dep[e[x].b])
			{
				SBT.Update(L[e[x].a], -val[x]), SBT.Update(R[e[x].a] + 1, val[x]);
				SBT.Update(L[e[x].a], vt), SBT.Update(R[e[x].a] + 1, -vt);
			}
			else
			{
				SBT.Update(L[e[x].b], -val[x]), SBT.Update(R[e[x].b] + 1, val[x]);
				SBT.Update(L[e[x].b], vt), SBT.Update(R[e[x].b] + 1, -vt);
			}
			val[x] = vt;
		}
		else
		{
			int l = read() ^ lastans, r = read() ^ lastans, x = read() ^ lastans;
			printf ("%lld\n", lastans = Query(l, r, x));
			lastans %= n;
		}
	}
}