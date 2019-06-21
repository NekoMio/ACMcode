#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[50005], n;
class Treap
{
    class Node
    {
      public:
        int size, v, key;
        Node *ch[2];
        Node(int x)
        {
            key = rand();
            v = x;
            size = 1;
            ch[0] = ch[1] = NULL;
        }
#define size(_) ((_) ? (_)->size : 0)
        void Pushup()
        {
            size = size(ch[0]) + size(ch[1]) + 1;
        }
    } * root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
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
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
        DNode o;
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
  public:
    Treap()
    {
        root = NULL;
    }
    int kth(int k)
    {
        DNode x = Split(root, k - 1);
        DNode y = Split(x.second, 1);
        Node *ans = y.first;
        root = Merge(x.first, Merge(y.first, y.second));
        return ans->v;
    }
    int rank(int x)
    {
        return rank(root, x);
    }
    int rank(Node *rt, int x)
    {
        if (!rt)
            return 0;
        return x <= rt->v ? rank(rt->ch[0], x) : rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
    }
    void Insert(int x)
    {
        int k = rank(root, x);
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(Merge(y.first, n), y.second);
    }
    void remove(int x)
    {
        int k = rank(root, x);
        DNode a = Split(root, k);
        DNode b = Split(a.second, 1);
        root = Merge(a.first, b.second);
    }
} root[50005 << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void build(int l, int r, int rt)
{
    for (int i = l; i <= r; i++)
        root[rt].Insert(a[i]);
}
void buildtree(int l, int r, int rt)
{
    build(l, r, rt);
    if (l == r)
        return;
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
}
void updata(int k, int x, int y, int l, int r, int rt)
{
    root[rt].remove(y);
    root[rt].Insert(x);
    if (l == r)
        return;
    int m = l + r >> 1;
    if (k <= m)
        updata(k, x, y, lch);
    else
        updata(k, x, y, rch);
}
int rank(int L, int R, int x, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return root[rt].rank(x);
    int m = l + r >> 1;
    if (R <= m)
        return rank(L, R, x, lch);
    if (L > m)
        return rank(L, R, x, rch);
    return rank(L, R, x, lch) + rank(L, R, x, rch);
}
int kth(int L, int R, int k)
{
    int l = -1e10, r = 1e10;
    while (l <= r)
    {
        int m = l + r >> 1;
        int num = rank(L, R, m, 1, n, 1) + 1;
        if (num <= k)
            l = m + 1;
        else
            r = m - 1;
    }
    return r;
}
int main()
{
    //freopen("dynrank.in", "r", stdin);
    //freopen("dynrank.out", "w", stdout);
    //int T;
    //scanf("%d", &T);
    //while (T--)
    //{
    //    memset(root,0,sizeof(root));
        int m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        buildtree(1, n, 1);
        char s[5];
        int i, j, k, t;
        while (m--)
        {
            scanf("%s", s);
            if (s[0] == 'Q')
            {
                scanf("%d%d%d", &i, &j, &k);
                printf("%d\n", kth(i, j, k));
            }
            else
            {
                scanf("%d%d", &i, &t);
                updata(i, t, a[i], 1, n, 1);
                a[i] = t;
            }
        }
    //}
}