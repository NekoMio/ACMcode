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
const int MAXN = 100005;
struct data
{
	int a, b, c, id;
	bool operator < (const data &d) const 
	{
		return c < d.c;
	}
}a[MAXN], tmp[MAXN];
bool cmp1(const data &x, const data &y)
{
	return x.id < y.id;
}
int n, m, Q;
struct Node
{
	Node *ch[2];
	int ID[100], f[101], cnt;
	Node()
	{
		ch[0] = ch[1] = NULL;
		cnt = 0;
		for (int i = 1; i <= n; i++) f[i] = i;
	}
	int find(int x)
	{
		if (x != f[x]) f[x] = find(f[x]);
		return f[x];
	}
	void Merge(int x)
	{
		if (find(a[x].a) != find(a[x].b))
		{
			f[find(a[x].a)] = find(a[x].b);
			ID[++cnt] = a[x].id;
		}
	}
}*root;
void Update(int x, int c, int l, int r, Node *rt)
{
	rt->Merge(c);
	if (l == r) return;
	int mid = l + r >> 1;
	if (x <= mid)
	{
		if (rt->ch[0] == NULL) rt->ch[0] = new Node();
		Update(x, c, l, mid, rt->ch[0]);
	}
	else
	{
		if (rt->ch[1] == NULL) rt->ch[1] = new Node();
		Update(x, c, mid + 1, r, rt->ch[1]);
	}
}
Node *q[100];
int cnt = 0;
void Query(int L, int R, int l, int r, Node *rt)
{
	if (L <= l && R >= r)
		return q[++cnt] = rt, void();
	int mid = l + r >> 1;
	if (L <= mid) Query(L, R, l, mid, rt->ch[0]);
	if (R > mid) Query(L, R, mid + 1, r, rt->ch[1]);
}
int T[10000];
bool cmp(const int &x, const int &y)
{
	return a[x].c < a[y].c;
}
int f[101];
int find(int x)
{
	if (x != f[x]) f[x] = find(f[x]);
	return f[x];
}
int Solve(int l, int r)
{
	cnt = 0;
	Query(l, r, 1, m, root);
	int h = 0;
	for (int i = 1; i <= cnt; i++)
		for (int j = 1; j <= q[i]->cnt; j++)
			T[++h] = q[i]->ID[j];
	sort(T + 1, T + h + 1, cmp);
	for (int i = 1; i <= n; i++) f[i] = i;
	int ans = 0;
	for (int i = 1; i <= h; i++)
	{
		if (find(a[T[i]].a) != find(a[T[i]].b))
		{
			ans += a[T[i]].c;
			f[find(a[T[i]].a)] = find(a[T[i]].b);
		}
	}
	return ans;
}
int main()
{
	n = read(), m = read(), Q = read();
	for (int i = 1; i <= m; i++)
		a[i].a = read(), a[i].b = read(), a[i].c = read(), a[i].id = i;
	sort(a + 1, a + m + 1);
	root = new Node();
	for (int i = 1; i <= m; i++)
		Update(a[i].id, i, 1, m, root);
	sort(a + 1, a + m + 1, cmp1);
	for (int i = 1; i <= Q; i++)
	{
		int x = read(), y = read();
		printf ("%d\n", Solve(x, y));
	}
}