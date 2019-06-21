#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
struct data
{
    int a, pos;
    bool operator<(const data &b) const
    {
        return a == b.a ? pos < b.pos : a < b.a;
    }
} a[2005];
int comp(const data &a, const data &b)
{
    return a.pos < b.pos;
}
int full = 13;
struct Trie
{
    struct Trie_Node
    {
        Trie_Node *ch[2];
        int s;
        Trie_Node()
        {
            ch[0] = ch[1] = NULL;
            s = 0;
        }
    } * root[2005], *null;
    Trie()
    {
        null = new Trie_Node();
        null->ch[0] = null->ch[1] = null;
        root[0] = new Trie_Node();
        root[0]->ch[1] = root[0]->ch[0] = null;
    }
    Trie_Node *NewNode()
    {
        Trie_Node *rt = new Trie_Node();
        rt->ch[0] = rt->ch[1] = null;
        return rt;
    }
    void copy(Trie_Node *&a, Trie_Node *b)
    {
        if (b == null)
            a = null;
        else
            a = NewNode(), *a = *b;
    }
    void Insert(int x, int cnt)
    {
        copy(root[cnt], root[cnt - 1]);
        Trie_Node *rt1 = root[cnt], *rt2 = root[cnt - 1];
        for (int i = full; i >= 0; i--)
        {
            int k = (x >> i) & 1;
            copy(rt1->ch[k], rt2->ch[k]);
            if (rt1->ch[k] == null)
                rt1->ch[k] = NewNode();
            rt1 = rt1->ch[k], rt2 = rt2->ch[k];
            rt1->s++;
        }
    }
    int kth(int k, int l, int r)
    {
        int res = 0;
        Trie_Node *rt1 = root[r], *rt2 = root[l - 1];
        for (int i = full; i >= 0; i--)
        {
            if (k > rt1->ch[0]->s - rt2->ch[0]->s)
            {
                k -= (rt1->ch[0]->s - rt2->ch[0]->s);
                res |= (1 << i);
                rt1 = rt1->ch[1], rt2 = rt2->ch[1];
            }
            else
            {
                rt1 = rt1->ch[0], rt2 = rt2->ch[0];
            }
        }
        return res;
    }
} root;
int pos[2005];
int Maxn[2005 << 2];
int Max[2005 << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void Update(int rt)
{
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
}
void buildtree(int l, int r, int rt)
{
    if (l == r)
    {
        Max[rt] = Maxn[l];
        return;
    }
    int m = l + r >> 1;
    buildtree(lch);
    buildtree(rch);
    Update(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
        return Max[rt];
    int m = l + r >> 1;
    int MAX = 0;
    if (L <= m)
        MAX = max(MAX, Query(L, R, lch));
    if (R > m)
        MAX = max(MAX, Query(L, R, rch));
    return MAX;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i].a);
        a[i].pos = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        a[i].a = i;
        pos[a[i].a] = a[i].pos;
    }
    sort(a + 1, a + n + 1, comp);
    for (int i = 1; i <= n; i++)
        root.Insert(a[i].a, i);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if ((i - j + 1) & 1)
            {
                int k = pos[root.kth((i - j + 1) / 2 + 1, j, i)];
                Maxn[k] = max(Maxn[k], (i - j + 1));
            }
        }
    }
    buildtree(1, n, 1);
    int Q, l, r;
    scanf("%d", &Q);
    while (Q--)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", Query(l, r, 1, n, 1));
    }
}
