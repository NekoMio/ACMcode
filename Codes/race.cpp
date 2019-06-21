#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int fix = 0, full = 20;
class Trie
{

  public:
    class Node
    {
      public:
        int size;
        Node *ch[2];
        Node()
        {
            ch[0] = ch[1] = NULL;
            size = 0;
        }
#define _size(_) ((_) ? (_)->size : 0)
    } * root;
    Trie()
    {
        root = new Node();
    }
    int size()
    {
        return _size(root);
    }
    void Insert(int x, int add)
    {
        x += fix;
        Node *rt = root;
        rt->size += add;
        for (int i = full; i >= 0; i--)
        {
            bool next = x >> i & 1;
            if (!rt->ch[next])
                rt->ch[next] = new Node;
            rt = rt->ch[next];
            rt->size += add;
        }
    }
    int rank(int x)
    {
        x += fix;
        int res = 0;
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            bool next = x >> i & 1;
            if (next)
                res += _size(rt->ch[0]);
            if (!rt->ch[next])
                break;
            rt = rt->ch[next];
        }
        return res;
    }
    int kth(int k)
    {
        int res = 0;
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            if (k > _size(rt->ch[0]))
            {
                k -= _size(rt->ch[0]);
                res |= 1 << i;
                if (!rt->ch[1])
                    break;
                rt = rt->ch[1];
            }
            else

                rt = rt->ch[0];
        }
        return res - fix;
    }
} root;
int n, m;
struct data
{
    int END, next, v;
} v[2000005];
int first[1000005], p;
void add(int a, int b, int c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
int L, R, maxn, Max;
void dfs(int x, int fa, int sum)
{
    if (sum > Max)
    {
        Max = sum;
        maxn = x;
    }
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            dfs(v[i].END, x, sum + v[i].v);
        }
    }
}
int len[1000005];
void dfs1(int x, int fa, int sum)
{
    len[x] = max(len[x], sum);
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].END != fa)
        {
            dfs1(v[i].END, x, sum + v[i].v);
        }
    }
}
int main()
{
    memset(first, -1, sizeof(first));
    int Fi, Di;
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d%d", &Fi, &Di);
        add(i, Fi, Di);
        add(Fi, i, Di);
    }
    dfs(1, 0, 0);
    L = maxn;
    dfs(L, 0, 0);
    R = maxn;
    dfs1(L, 0, 0);
    dfs1(R, 0, 0);
    int l = 1, r = 1;
    int ans = 0;
    int t = 0;
    while (r <= n)
    {
        root.Insert(len[r], 1);
        t++;
        while (root.kth(t) - root.kth(1) > m)
        {
            root.Insert(len[l], -1);
            t--;
            l++;
        }
        r++;
        ans = max(ans, t);
    }
    printf("%d\n", ans);
}