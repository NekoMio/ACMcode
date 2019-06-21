#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 300005;
#define size(_) ((_) ? (_)->s : 0)
#define _Max(_) ((_) ? (_)->Max : 0)
struct Node
{
    Node *ch[2];
    int s, v, key;
    int val, Max, lazy;
    Node(int x)
    {
        s = 0, v = x;
        key = rand();
        val = lazy = Max = 1;
        ch[0] = ch[1] = NULL;
    }
    void Pushup()
    {
        s = size(ch[0]) + size(ch[1]) + 1;
        Max = max(max(_Max(ch[0]), _Max(ch[1])), val);
    }
    void Pushlazy(int x)
    {
        val += x;
        lazy += x;
        Max += x;
    }
    void Pushdown()
    {
        if (lazy)
        {
            if (ch[0]) ch[0]->Pushlazy(lazy);
            if (ch[1]) ch[1]->Pushlazy(lazy);
            lazy = 0;
        }
    }
}*root;
Node *Merge(Node *A, Node *B)
{
    if (!A) return B;
    if (!B) return A;
    if (A->key < B->key)
    {
        A->Pushdown();
        A->ch[1] = Merge(A->ch[1], B);
        A->Pushup();
        return A;
    }
    else
    {
        B->Pushdown();
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
    rt->Pushdown();
    if (size(rt->ch[0]) >= k)
    {
        o = Split(rt->ch[0], k);
        rt->ch[0] = o.second;
        rt->Pushup();
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        rt->Pushup();
        o.first = rt;
    }
    return o;
}
int Rank(Node *rt, int x)
{
    if (!rt) return 0;
    return x <= rt->v ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
}
void Insert(int x)
{
    int k = Rank(root, x);
    DNode y = Split(root, k);
    Node *n = new Node(x);
    root = Merge(y.first, Merge(n, y.second));
}
void Update(int x, int c)
{
    int k = Rank(root, x);
    DNode y = Split(root, k);
    if (y.second) y.second->Pushlazy(c);
    root = Merge(y.first, y.second);
}
void Update(int l, int r, int c)
{
    int k = Rank(root, l);
    DNode x = Split(root, k);
    int k2 = Rank(x.second, r + 1);
    DNode y = Split(x.second, k2);
    if (y.first) y.first->Pushlazy(c);
    root = Merge(x.first, Merge(y.first, y.second));
}
int Calc_Max(Node *rt)
{
    if (!rt->ch[1]) return rt->v;
    else return Calc_Max(rt->ch[1]);
}
int Query(int x)
{
    int k = Rank(root, x);
    DNode y = Split(root, k);
    int ans = _Max(y.second);
    root = Merge(y.first, y.second);
    return ans + 1;
}
set<int> t1, t2;
struct data
{
    int v, id, Mx;
    bool operator < (const data &a) const
    {
        return v < a.v;
    }
};
set<data> t3;
int n;
int a[MAXN], b[MAXN];
long long S[MAXN];
#define lowbit(_) ((_) & (-_))
void add(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i))
        S[i] += c;
}
long long Q(int x)
{
    long long ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        ans += S[i];
    return ans;
}
int st1[MAXN], st2[MAXN], top1, top2;
int main()
{
    // freopen ("columns3_2.in", "r", stdin);
    // freopen ("columns.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        b[i] = a[i] = read();
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    long long Sum = 0;
    for (int i = 1; i <= n; i++)
        Sum += Q(n) - Q(a[i]), add(a[i], 1);
    st1[++top1] = 1;
    t1.insert(1);
    for (int i = 2; i <= n; i++)
        if (a[i] > a[st1[top1]])
            st1[++top1] = i, t1.insert(i);
    st2[++top2] = n;
    t2.insert(n);
    for (int i = n - 1; i >= 1; i--)
        if (a[i] < a[st2[top2]])
            st2[++top2] = i, t2.insert(i);
    reverse(st2 + 1, st2 + top2 + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!t1.count(i) && !t2.count(i))
        {
            Update(a[i], 1);
            t3.insert((data){a[i], i, Calc_Max(root)});
        }
        else
        {
            if (t1.count(i))
                Insert(a[i]);
            if (t2.count(i))
            {
                for (auto x : t3)
                    if (x.v > a[i]) break;
                    else
                        Update(x.v, x.Mx, -1);
                auto x2 = t3.begin();
                if (x2 != t3.end()) x2++;
                for (auto x = t3.begin(); x != t3.end(); )
                {
                    if (x->v > a[i]) break;
                    else
                        t3.erase(x);
                    x = x2;
                    if (x2 != t3.end())
                        x2++;
                }
                ans = max(ans, Query(a[i]));
            }
        }
    }
    printf ("%lld\n", min(Sum, Sum - (ans - 2) * 2));
}