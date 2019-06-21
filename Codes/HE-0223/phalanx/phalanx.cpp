// WildRage phalanx T3

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
using namespace std;
const int N = 3e5 + 5;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n, m, q, Max;
vector<long long> v[N];
struct Node
{
	int Sum;
	Node *ch[2];
	Node()
	{
		Sum = 0;
		ch[0] = ch[1] = NULL;
	}
	#define Size(_) ((_) ? (_)->Sum : 0)
}*root[N], *null;
Node *NewNode()
{
	Node *o = new Node();
	o->ch[0] = o->ch[1] = null;
	return o;
}
void Update(Node *&rt, int l, int r, int x)
{
	if (!rt || rt == null) rt = NewNode();
	rt->Sum++;
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid) Update(rt->ch[0], l, mid, x);
	else Update(rt->ch[1], mid + 1, r, x);
}
int Query(Node *rt, int l, int r, int k)
{
	if (l == r) return l;
	int mid = l + r >> 1, S = mid - l + 1 - Size(rt->ch[0]);
	if (k <= S) return Query(rt->ch[0], l, mid, k);
	else return Query(rt->ch[1], mid + 1, r, k - S);
}
signed main()
{
	freopen("2017phalanx.in", "r", stdin);
	freopen("2017phalanx.out", "w", stdout);
    // freopen("1.in", "r", stdin);
	null = new Node();
	null->ch[0] = null->ch[1] = null;
	n = read(), m = read(), q = read();
	for (int i = 0; i <= n + 1; i++) root[i] = null;
	Max = max(n, m) + q;
	while (q--)
	{
		int x = read(), y = read();
		long long ans = 0;
		if (y == m)
		{
			long long now = Query(root[n + 1], 1, Max, x);
			Update(root[n + 1], 1, Max, now);
			printf ("%lld\n", ans = now <= n ? 1ll * now * m : v[n + 1][now - n - 1]);
			v[n + 1].push_back(ans);
		}
		else
		{
			int now = Query(root[x], 1, Max, y);
			Update(root[x], 1, Max, now);
			printf ("%lld\n", ans = now < m ? 1ll * (x - 1) * m + now : v[x][now - m]);
			v[n + 1].push_back(ans);
			now = Query(root[n + 1], 1, Max, x);
			Update(root[n + 1], 1, Max, now);
			v[x].push_back(now <= n ? 1ll * now * m : v[n + 1][now - n - 1]);
		}
	}
	//fclose(stdin), fclose(stdout);
	return 0;
}
