#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int N = 1000000000;
#define lowbit(_) ((_) & (-_))
struct Seg_Node
{
    Seg_Node *ch[2];
    int sum, l, r;
    Seg_Node(int L, int R)
    {
        sum = 0, l = L, r = R;
        ch[1] = ch[0] = NULL;
    }
#define sum(_) ((_) ? (_)->sum : 0)
    void Pushup()
    {
        sum = sum(ch[0]) + sum(ch[1]);
    }
} * root[50005];
int a[50005];
int n;
void Insert(Seg_Node *rt, int num)
{
    if (rt->l == rt->r)
    {
        rt->sum++;
        return;
    }
    int m = rt->l + rt->r >> 1;
    if (num <= m)
    {
        if (!rt->ch[0])
            rt->ch[0] = new Seg_Node(rt->l, m);
        Insert(rt->ch[0], num);
    }
    else
    {
        if (!rt->ch[1])
            rt->ch[1] = new Seg_Node(m + 1, rt->r);
        Insert(rt->ch[1], num);
    }
    rt->Pushup();
}
void Insert(int x, int num)
{
    for (int i = x; i <= n; i += lowbit(i))
    {
        if (root[i] == NULL)
            root[i] = new Seg_Node(0, N);
        Insert(root[i], num);
    }
}
void Delete(Seg_Node *&rt, int num)
{
    if (rt->l == rt->r)
    {
        rt->sum--;
        if (!rt->sum)
            delete rt, rt = NULL;
        return;
    }
    int m = rt->l + rt->r >> 1;
    if (num <= m)
        Delete(rt->ch[0], num);
    else
        Delete(rt->ch[1], num);
    rt->Pushup();
    if (!rt->sum)
        delete rt, rt = NULL;
}
void Delete(int x, int num)
{
    for (int i = x; i <= n; i += lowbit(i))
    {
        Delete(root[i], num);
    }
}
vector<Seg_Node *> Get(int x)
{
    vector<Seg_Node *> ans;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        ans.push_back(root[i]);
    }
    return ans;
}
vector<Seg_Node *> Get_ch(vector<Seg_Node *> x, int op)
{
    for (int i=0;i<x.size();i++)
        if (x[i])
            x[i] = x[i]->ch[op];
    return x;
}
int Query(vector<Seg_Node *> list1, vector<Seg_Node *> list2, int l, int r, int k)
{
    if (l == r)
        return l;
    int ans = 0;
    for (int i=0;i<list2.size();i++)
        if (list2[i])
            ans += sum(list2[i]->ch[0]);
    for (int i=0;i<list1.size();i++)
        if (list1[i])
            ans -= sum(list1[i]->ch[0]);
    int m = l + r >> 1;
    if (ans >= k)
        return Query(Get_ch(list1, 0), Get_ch(list2, 0), l, m, k);
    else
        return Query(Get_ch(list1, 1), Get_ch(list2, 1), m + 1, r, k - ans);
}
void DFS(Seg_Node *&rt)
{
    if (rt)
    {
        DFS(rt->ch[0]);
        DFS(rt->ch[1]);
        delete rt;
        rt=NULL;
    }
}
void remove()
{
    for (int i = 1; i <= n; i++)
    {
        DFS(root[i]);
    }
}
int main(int argc, char const *argv[])
{
    //freopen("dynrank.in","r",stdin);
    //freopen("dynrank.out","w",stdout);
    //int T;
    //scanf("%d", &T);
    //while (T--)
    //{
        int m;
        scanf("%d%d", &n, &m);
        //memset(a,0,sizeof(a));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
            Insert(i, a[i]);
        }
        //sort(a + 1, a + n + 1);
        char op[3];
        int p, b, c;
        for (int i = 1; i <= m; i++)
        {
            scanf("%s", op);
            if (op[0] == 'Q')
            {
                scanf("%d%d%d", &p, &b, &c);
                printf("%d\n", Query(Get(p - 1), Get(b), 0, N, c));
            }
            else
            {
                scanf("%d%d", &p, &b);
                Delete(p, a[p]);
                Insert(p, b);
                a[p] = b;
            }
        }
        remove();
 //   }
    return 0;
}
