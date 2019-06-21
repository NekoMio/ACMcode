#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
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
}v[200005];
int first[100005], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}
int D[100005];
int f[100005], size[100005];
int n, k, a;
long long ans = 0;
void dfs(int rt, int fa)
{
	f[rt] = D[rt];
	size[rt] = D[rt];
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		dfs(v[i].END, rt);
		size[rt] += size[v[i].END];
		f[rt] += f[v[i].END];
		ans += f[v[i].END];
	}
	f[rt] = min(f[rt], k - size[rt]);
}
int main()
{
	freopen("beauty.in", "r", stdin);
	freopen("beauty.out", "w", stdout);
	n = read(), k = read() << 1, a = read();
	for (int i = 1; i <= k; i++)
		D[read()] = 1;
	int b;
	memset (first, -1, sizeof (first));
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	printf ("%lld", ans);
	fclose(stdin), fclose(stdout);
	return 0;
}
