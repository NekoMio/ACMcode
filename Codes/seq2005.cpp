/*
 * @Author: WildRage 
 * @Date: 2017-07-15 15:07:46 
 * @Last Modified by:   WildRage 
 * @Last Modified time: 2017-07-15 15:07:46 
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
struct Node
{
    int v, key, size, rev;
    int Max, l, r, sum, change;
    Node *ch[2];
    Node(int x)
    {
        v = x;
        key = rand();
        size = 1;
        rev = 0;
        change = -INF;
        Max = x;
        l = x;
        r = x;
        sum = x;
        ch[0] = ch[1] = NULL;
    }
#define size(_) ((_) ? (_)->size : (0))
#define sum(_) ((_) ? (_)->sum : (0))
#define l(_) ((_) ? (_)->l : (-INF))
#define r(_) ((_) ? (_)->r : (-INF))
#define Max(_) ((_) ? (_)->Max : (-INF))
#define change(_) ((_) ? (_)->change : (-INF))
    void Pushup()
    {
        size = 1 + size(ch[1]) + size(ch[0]);
        l = max(l(ch[0]), max(sum(ch[0]) + v, sum(ch[0]) + v + l(ch[1])));
        r = max(r(ch[1]), max(sum(ch[1]) + v, sum(ch[1]) + v + r(ch[0])));
        Max = max(Max(ch[0]), max(Max(ch[1]), max(r(ch[0]) + v, max(l(ch[1]) + v, max(r(ch[0]) + l(ch[1]) + v, v)))));
        sum = sum(ch[0]) + sum(ch[1]) + v;
    }
    void reverse()
    {
        if (!this)
            return;
        swap(ch[0], ch[1]);
        swap(l, r);
        rev ^= 1;
    }
    void Update()
    {
        if (!this)
            return;
        if (ch[1])
            ch[1]->change = change;
        if (ch[0])
            ch[0]->change = change;
        sum = size * change;
        v=change;
        l=r=Max=max(change,size*change);
        //change = -INF;
    }
    void Pushdown()
    {
        if (!this)
            return;
        if (rev)
        {
            ch[0]->reverse();
            ch[1]->reverse();
            rev = 0;
        }
        if (change != -INF)
        {
            ch[0]->Update();
            ch[1]->Update();
            change=-INF;
        }
    }
} * root;
typedef pair<Node *, Node *> DNode;
Node *Merge(Node *A, Node *B)
{
    if (!A)
        return B;
    if (!B)
        return A;
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
DNode Split(Node *rt, int k)
{
    if (!rt)
        return DNode(NULL, NULL);
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
Node *st[4000005];
Node *build(int m)
{
    //memset(st, 0, sizeof(st));
    Node *x, *last;
    int p = 0;
    int a;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &a);
        x = new Node(a);
        last = NULL;
        while (p && st[p]->key > x->key)
        {
            st[p]->Pushup();
            last = st[p];
            st[p--] = NULL;
        }
        if (p)
            st[p]->ch[1] = x;
        x->ch[0] = last;
        st[++p] = x;
    }
    while (p)
        st[p--]->Pushup();
    return st[1];
}
Node *kth(int k)
{
    DNode x = Split(root, k - 1);
    DNode y = Split(x.second, 1);
    Node *ans = y.first;
    root = Merge(Merge(x.first, ans), y.second);
    return ans;
}
int Rank(Node *rt, int x)
{
    if (!rt)
        return 0;
    return x <= rt->v ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
}
void Insert(int x)
{
    int k = Rank(root, x);
    DNode y = Split(root, k);
    Node *n = new Node(x);
    root = Merge(Merge(y.first, n), y.second);
}
void remove(int x)
{
    int k = Rank(root, x);
    DNode a = Split(root, k);
    DNode b = Split(a.second, 1);
    root = Merge(a.first, b.second);
}
void flip(int i, int m)
{
    DNode x = Split(root, i - 1);
    DNode y = Split(x.second, m);
    y.first->reverse();
    root = Merge(x.first, Merge(y.first, y.second));
}
void dfs(Node *rt)
{
    if (rt)
    {
        rt->Pushdown();
        dfs(rt->ch[0]);
        printf("%d ", rt->v);
        dfs(rt->ch[1]);
    }
}
void Insert(int i, int tot)
{
    Node *x = build(tot);
    DNode y = Split(root, i);
    root = Merge(y.first, Merge(x, y.second));
}
void rmdfs(Node *rt)
{
    if (rt)
    {
        rmdfs(rt->ch[0]);
        rmdfs(rt->ch[1]);
    }
    delete rt;
}
void remove(int i, int tot)
{
    DNode x = Split(root, i - 1);
    DNode y = Split(x.second, tot);
    rmdfs(y.first);
    root = Merge(x.first, y.second);
}
void Update(int i, int tot, int c)
{
    DNode x = Split(root, i - 1);
    DNode y = Split(x.second, tot);
    y.first->change = c;
    y.first->Update();
    //Node *m = build(tot, c);
    //rmdfs(y.first);
    root = Merge(x.first, Merge(y.first, y.second));
}
int get_sum(int i, int tot)
{
    DNode x = Split(root, i - 1);
    DNode y = Split(x.second, tot);
    int ans = sum(y.first);
    root = Merge(x.first, Merge(y.first, y.second));
    return ans;
}
int Max_Sum()
{
    return Max(root);
}
int main()
{
    freopen("seq2005.in", "r", stdin);
    freopen("seq2005.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    root = build(n);
    //dfs(root);
    //printf("----------------------\n");
    int l, r, c;
    char s[16];
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", s);
        switch (s[0])
        {
        case 'G':
            scanf("%d%d", &l, &r);
            printf("%d\n", get_sum(l, r));
            break;
        case 'D':
            scanf("%d%d", &l, &r);
            remove(l, r);
            break;
        case 'I':
            scanf("%d%d", &l, &r);
            Insert(l, r);
            break;
        case 'R':
            scanf("%d%d", &l, &r);
            flip(l, r);
            break;
        case 'M':
            if (s[2] == 'K')
            {
                scanf("%d%d%d", &l, &r, &c);
                Update(l, r, c);
            }
            else
            {
                printf("%d\n", Max_Sum());
            }
        }
        //printf("--------------------------------\n");
        //dfs(root);
        //printf("\n-----------DONE-----------------\n");
    }
    //while (1)
    ;
}