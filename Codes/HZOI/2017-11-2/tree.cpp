#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[100005 << 1];
int first[100005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long dis1[100005], dis2[100005];
int du[100005];
void dfs(int rt, int fa)
{
	dis1[rt] = du[rt];
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
    	if (v[i].END == fa) continue;
    	dfs(v[i].END, rt);
    	(dis1[rt] += dis1[v[i].END]) %= MOD;
	}
}
void dfs1(int rt, int fa)
{
	if (rt != 1) dis2[rt] = (dis2[fa] + dis1[fa] - dis1[rt] + MOD) % MOD;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs1(v[i].END, rt);
	}
}
long long dep1[100005], dep2[100005], dep[100005];
int f[(100005 << 1) + 50][17];
void dfs2(int rt, int fa, int Dep)
{
	f[rt][0] = fa;
	for (int i = 1; i <= 16; i++)
		f[rt][i] = f[f[rt][i - 1]][i - 1];
	dep[rt] = Dep;
	dep1[rt] = (dep1[fa] + dis1[rt]) % MOD;
	dep2[rt] = (dep2[fa] + dis2[rt]) % MOD;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs2(v[i].END, rt, Dep + 1);
	}
}
int LCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	int d = dep[a] - dep[b];
	for (int i = 16; i >= 0; i--)
		if (d & (1 << i))
			d -= (1 << i), a = f[a][i];
	if (a == b) return a;
	for (int i = 16; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int main()
{
//    freopen("tree.in", "r", stdin);
//    freopen("tree.out", "w", stdout);
	memset(first, -1, sizeof (first));
    int n = read(), Q = read();
    for (int i = 1; i < n; i++)
    {
        int a = read(), b = read();
        add(a, b);du[a]++;
        add(b, a);du[b]++;
    }
    dfs(1, 0);
    dfs1(1, 0);
    dfs2(1, 0, 0);
    int a, b;
    while (Q--)
    {
    	a = read(), b = read();
    	int lca = LCA(a, b);
    	printf ("%lld\n", ((dep1[a] - dep1[lca] + dep2[b] - dep2[lca]) % MOD + MOD) % MOD);
    }
//    fclose(stdin), fclose(stdout);
    return 0;
}
