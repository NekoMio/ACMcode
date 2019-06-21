#include <cstdio>
#include <cstring>
using namespace std;
const int full = 21, fix = 1000001;
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
    } * root[100005],*null;
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
        x += fix;
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
        return res - fix;
    }
} root;
int main()
{
    freopen("kth.in","r",stdin);
    freopen("kth.out","w",stdout);
    int n, m, a;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        root.Insert(a, i);
    }
    int b, k;
    while (m--)
    {
        scanf("%d%d%d", &a, &b, &k);
        printf("%d\n", root.kth(k, a, b));
    }
}