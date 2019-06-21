// #pragma GCC optimize("O3")

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int full = 30;

struct Trie
{
    struct Trie_Node
    {
        int s;
        Trie_Node *ch[2];
        Trie_Node()
        {
            ch[0] = ch[1] = NULL;
            s = 0;
        }
    }*root;
    #define size(_) ((_)?(_)->s:0)
    Trie()
    {
        root = new Trie_Node();
    }
    void Insert(int x)
    {
        Trie_Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            int nxt = (x >> i) & 1;
            if (rt->ch[nxt] == NULL)
                rt->ch[nxt] = new Trie_Node();
            rt = rt->ch[nxt];
            rt->s++;
        }
    }
    int Xorkth(int x, int k)
    {
        Trie_Node *rt = root;
        int res = 0;
        for (int i = full; i >= 0; i--)
        {
            int nxt = (x >> i) & 1;
            if (k > size(rt->ch[nxt]))
            {
                k -= size(rt->ch[nxt]);
                res |= 1 << i;
                if (!rt->ch[nxt ^ 1])
                    break;
                rt = rt->ch[nxt ^ 1];
            }
            else
                rt = rt->ch[nxt];
        }
        return res;
    }
}root;

struct data
{
    int a;
    int i, k;
    bool operator < (const data &b) const
    {
        return a > b.a;
    }
    data(int b, int c, int d)
    {
        a = b, i = c, k = d;
    }
};

priority_queue<data> Q;

const int MAXN = 100005;

int a[MAXN];

int ans[MAXN * 2], cnt;

int main()
{
    int n = read(), k = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        root.Insert(a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        Q.push(data(root.Xorkth(a[i], 2), i, 2));
    }
    for (int i = 1; i <= 2 * k; i++)
    {
        data tmp = Q.top();
        Q.pop();
        if (i & 1) printf ("%d ", tmp.a);
        if (tmp.k != n)
            Q.push(data(root.Xorkth(a[tmp.i], tmp.k + 1), tmp.i, tmp.k + 1));
    }
    // while (1);
}