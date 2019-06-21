#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int full = 17;
int n;
int Hash[100005];
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
    } * root[200005], *null;
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
            if (k <= rt1->ch[1]->s - rt2->ch[1]->s)
            {
                //k -= (rt1->ch[0]->s - rt2->ch[0]->s);
                res |= (1 << i);
                rt1 = rt1->ch[1], rt2 = rt2->ch[1];
            }
            else
            {
                k -= (rt1->ch[1]->s - rt2->ch[1]->s);
                rt1 = rt1->ch[0], rt2 = rt2->ch[0];
            }
        }
        return Hash[res];
    }
} root;
int a[100005], cnt;
struct edge
{
    int S, E, val;
    bool operator<(const edge &a) const
    {
        return val < a.val;
    }
} EDGE[500005];
//并查集
int father[200005];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
//end;
struct Edge
{
    int END, next;
} v[200005];
int first[200005], p;
void add(int s, int e)
{
    v[p].END = e;
    v[p].next = first[s];
    first[s] = p++;
}
int val[200005];
int f[200005][20];
int l[200005], r[200005], num;
void dfs(int x)
{
    //printf("%d|-|-|-|-|-|-|-|-|\n",x);
    for (int i = 1; (1 << i) <= n; i++)
        f[x][i] = f[f[x][i - 1]][i - 1];
    l[x] = ++num;
    if (x <= n)
        root.Insert(a[x], num);
    else
        root.root[num] = root.root[num - 1];
    for (int i = first[x]; i != -1; i = v[i].next)
        dfs(v[i].END);
    r[x] = num;
}
int Query(int x, int a, int k)
{
    for (int i = 18; i >= 0; i--)
    {
        if (f[x][i] && val[f[x][i]] <= a)
        {
            x = f[x][i];
        }
    }
    //printf("%d\n",x);
    //printf("==========Query============\n");
    return root.kth(k, l[x], r[x]);
}
int main(int argc, char const *argv[])
{
    //freopen("Peaks.in","r",stdin);
    //freopen("Peaks.out","w",stdout);
    memset(first, -1, sizeof(first));
    int m, Q;
    scanf("%d%d%d", &n, &m, &Q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    //full =
    sort(Hash + 1, Hash + n + 1);
    int All = unique(Hash, Hash + n + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(Hash + 1, Hash + All + 1, a[i]) - Hash;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &EDGE[i].S, &EDGE[i].E, &EDGE[i].val);
    }
    //printf("1=========================\n");
    for (int i = 1; i <= 2 * n; i++)
    {
        father[i] = i;
    }
    sort(EDGE + 1, EDGE + m + 1);
    cnt = n;
    //printf("2=========================\n");
    for (int i = 1; i <= m; i++)
    {
        int s = find(EDGE[i].S), e = find(EDGE[i].E);
        if (s != e)
        {
            val[++cnt] = EDGE[i].val;
            father[s] = father[e] = cnt;
            add(cnt, s), add(cnt, e);
            f[s][0] = f[e][0] = cnt;
            if (cnt - n == n - 1)
                break;
        }
    }
    //for (int i = 0; i <= cnt; i++)
    // {
    //    root.root[i] = root.NewNode();
    // }
    //printf("3=========================\n");
    for (int i = 1; i <= cnt; i++)
        if (!l[i])
            dfs(find(i));
    //printf("+++++++++++++++++++++++++++++++\n");
    int value, rt, K, ans = 0;
    while (Q--)
    {
        scanf("%d%d%d", &rt, &value, &K);
        rt ^= ans, value ^= ans, K ^= ans;
        ans = Query(rt, value, K);
        printf("%d\n", ans ? ans : -1);
    }
    //while(1);
    return 0;
}
