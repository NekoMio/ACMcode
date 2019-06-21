#include <stdio.h>
#include <string.h>
#include <algorithm>


using namespace std;

const int full = 24;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

struct Trie
{
    struct Trie_Node
    {
        int s;
        Trie_Node *ch[2];
        Trie_Node()
        {
            s = 0;
            ch[0] = ch[1] = NULL;
        }
    }*root[600005], *null;
    #define size(_) ((_) ? (_)->s:0)
    Trie_Node *NewNode()
    {
        Trie_Node *o = new Trie_Node();
        o->ch[0] = o->ch[1] = null;
        return o;
    }
    Trie()
    {
        null = new Trie_Node();
        null->ch[0] = null->ch[1] = null;
        root[0] = NewNode();
    }
    void copy(Trie_Node *&rt1, Trie_Node *rt2)
    {
        if (rt2 == null)
            rt1 = null;
        else
            rt1 = NewNode(), *rt1 = *rt2;
    }
    void Insert(int x, int pos)
    {
        copy(root[pos], root[pos - 1]);
        Trie_Node *rt1 = root[pos], *rt2 = root[pos - 1];
        for (int i = full; i >= 0; i--)
        {
            int nxt = (x >> i) & 1;
            copy(rt1->ch[nxt], rt2->ch[nxt]);
            if (rt1->ch[nxt] == null)
                rt1->ch[nxt] = NewNode();
            rt1 = rt1->ch[nxt], rt2 = rt2->ch[nxt];
            rt1->s++;
        }
    }
    int Query(int x, int l, int r)
    {
        int res = 0;
        Trie_Node *rt1 = root[l - 1], *rt2 = root[r];
        for (int i = full; i >= 0; i--)
        {
            int nxt = (x >> i) & 1;
            if (rt2->ch[nxt ^ 1]->s - rt1->ch[nxt ^ 1]->s)
            {
                res |= (1 << i);
                rt1 = rt1->ch[nxt ^ 1];
                rt2 = rt2->ch[nxt ^ 1];
            }
            else
                rt1 = rt1->ch[nxt], rt2 = rt2->ch[nxt];
        }
        return res;
    }
}root;

int a[600005];

int main()
{
    int n, m;
    n = read() + 1, m = read();
    a[1] = 0;
    root.Insert(a[1], 1);
    for (int i = 2; i <= n; i++)
    {
        a[i] = read() ^ a[i - 1];
        root.Insert(a[i], i);
    }
    char c[10];
    int l, r, x;
    while (m--)
    {
        scanf ("%s", c);
        if (c[0] == 'A')
        {
            n++;
            a[n] = read() ^ a[n - 1];
            root.Insert(a[n], n);
        }
        else
        {
            l = read(), r = read(), x = read() ^ a[n];
            printf ("%d\n", root.Query(x, l, r));
        }
    }
}