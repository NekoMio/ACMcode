#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int full = 11;
struct Trie
{
    struct Node
    {
        int s;
        Node *ch[2];
        Node()
        {
            s = 0;
            ch[0] = ch[1] = NULL;
        }
#define size(_) ((_)?(_)->s:0)
    }*root;
    Trie()
    {
        root = new Node();
    }
    void Insert(int x, int add)
    {
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            int next = (x >> i) & 1;
            if (rt->ch[next] == NULL)
                rt->ch[next] = new Node();
            rt = rt->ch[next];
            rt->s += add;
        }
    }
    int kth(int k)
    {
        Node *rt = root;
        int ret = 0;
        for (int i = full; i >= 0; i--)
        {
            if (k > size(rt->ch[0]))
            {
                k -= size(rt->ch[0]);
                ret |= 1 << i;
                if (!rt->ch[1]) break;
                rt = rt->ch[1];
            }
            else
                rt = rt->ch[0];
        }
        return ret;
    }
}root;
const int MAXN = 2005;
struct data
{
    int v, id, c;
    bool operator < (const data &a) const
    {
        return v == a.v ? id < a.id : v < a.v;
    }
}a[MAXN], Hash[MAXN];
int pos[MAXN];
int st[(MAXN << 1) + 200][12];
int Query(int l, int r)
{
    int d = r - l + 1;
    int k = 0;
    while ((1 << k) <= d) k++;
    k--;
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int main()
{
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i].v), a[i].id = i, Hash[i] = a[i];
    sort(Hash + 1, Hash + n + 1);
    for (int i = 1; i <= n; i++)
        a[i].c = lower_bound(Hash + 1, Hash + n + 1, a[i]) - Hash, pos[a[i].c] = a[i].id;
    int mid = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
            root.Insert(a[j].c, 1);
        for (int j = 1; j <= i; j++)
        {
            if (((i - j + 1) & 1))
            {
                mid = root.kth((i - j + 1) / 2 + 1);
                st[pos[mid]][0] = max(st[pos[mid]][0], (i - j + 1));
            }
            root.Insert(a[j].c, -1);
        }
    }
    for (int i = 1; i <= 11; i++)
        for (int j = 1; j <= n; j++)
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    int Q;
    scanf ("%d", &Q);
    int l, r;
    while (Q--)
    {
        scanf ("%d%d", &l, &r);
        printf("%d\n", Query(l, r));
    }
}
