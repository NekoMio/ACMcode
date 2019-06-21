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
struct Treap
{
    struct Node
    {
        Node *ch[2];
        int key, v, s;
        long long Sum = 0;
        Node(int x)
        {
            key = rand(), v = x, s = 1;
            Sum = v;
            ch[0] = ch[1] = NULL;
        }
        #define Size(_) ((_) ? (_)->s : 0)
        #define Su(_) ((_) ? (_)->Sum : 0)
        void Pushup()
        {
            s = Size(ch[0]) + Size(ch[1]) + 1;
            Sum = Su(ch[0]) + Su(ch[1]) + v;
        }
    }*root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A) return B;
        if (!B) return A;
        if (A->key > B->key)
        {
            A->ch[1] = Merge(A->ch[1], B);
            A->Pushup();
            return A;
        }
        else
        {
            B->ch[0] = Merge(A, B->ch[0]);
            B->Pushup();
            return B;
        }
    }
    typedef pair<Node*, Node*> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt) return DNode(NULL, NULL);
        DNode o;
        if (Size(rt->ch[0]) >= k)
        {
            o = Split(rt->ch[0], k);
            rt->ch[0] = o.second;
            rt->Pushup();
            o.second = rt;
        }
        else
        {
            o = Split(rt->ch[1], k - Size(rt->ch[0]) - 1);
            rt->ch[1] = o.first;
            rt->Pushup();
            o.first = rt;
        }
        return o;
    }
    int rank(Node *rt, int x)
    {
        if (!rt) return 0;
        return x <= rt->v ? rank(rt->ch[0], x) : rank(rt->ch[1], x) + Size(rt->ch[0]) + 1;
    }
    int rank(int x)
    {
        return rank(root, x);
    }
    void insert(int x)
    {
        int k = rank(root, x);
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(y.first, Merge(n, y.second));
    }
    int size()
    {
        return Size(root);
    }
    void DFSadd(Node *rt)
    {
        if (!rt) return;
        insert(rt->v);
        DFSadd(rt->ch[0]);
        DFSadd(rt->ch[1]);
    }
    void join(Treap &x)
    {
        DFSadd(x.root);
    }
}root[MAXN];
struct edge
{
	int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
int d[MAXN];
void add(int a, int b, int c)
{
	v[p].END = b;
	v[p].v = c;
	v[p].next = first[a];
	first[a] = p++;
}
int fa[MAXN];
int dep[MAXN];
void DFS(int rt, int f)
{
	fa[rt] = f;
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == f) continue;
        dep[v[i].END] = dep[rt] + v[i].v;
		DFS(v[i].END, rt);
	}
}
bool Judge(int x, int mid)
{
    int k = root[x].rank(mid);
    Treap::DNode y = root[x].Split(root[x].root, k);
    bool ans = 0;
    if (d[x] + Su(y.first) <= 1ll * Size(y.first) * mid) ans = 1;
    root[x].root = root[x].Merge(y.first, y.second);
    return ans;
}
int ans = 0;
void Solve(int x)
{
	for (int i = first[x]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa[x]) continue;
		Solve(v[i].END);
        if (root[x].size() < root[v[i].END].size()) swap(root[x], root[v[i].END]);
        root[x].join(root[v[i].END]);
	}
	if (d[x] != 0)
	{
		int l = 0, r = 3e8, tmp = 0;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (Judge(x, mid)) tmp = mid, r = mid - 1;
			else l = mid + 1;
		}
        // printf ("%d\n", tmp);
		ans = max(ans, tmp - dep[x]);
        // printf ("%d\n", ans);
		root[x].insert(tmp);
	}
	else
	{
		root[x].insert(dep[x]);
	}
}
int main()
{
    // freopen ("1.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
	memset (first, -1, sizeof (first));
	int n = read();
	for (int i = 1; i <= n; i++)
        d[i] = read();
	for (int i = 1; i < n; i++)
	{
		int a = read(), b = read(), c = read();
		add(a, b, c);
		add(b, a, c);
	}
	DFS(1, 0);
	Solve(1);
	printf ("%d\n", ans);
}