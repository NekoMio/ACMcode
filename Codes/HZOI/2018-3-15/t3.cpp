// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 1e9 + 7;
const int MAXN = 3e6 + 5;
const int MAXM = 3e5 + 5;
const int base = 31;
long long H[MAXN], L[MAXN];
char s[MAXN], c[MAXM], s_rev[MAXN];
unsigned long long Hash_s[MAXN], Hash_s_rev[MAXN], Hash_c[MAXN], BASE[MAXN];
int id[250];
void Hash(char *x, unsigned long long *Hash, int n)
{
    for (int i = 1; i <= n; i++)
        Hash[i] = Hash[i - 1] * base + id[x[i]] + 1;
}
unsigned long long Calc(unsigned long long *x, int l, int r)
{
    return x[r] - x[l - 1] * BASE[r - l + 1];
}
struct Hash_Table
{
    struct edge
    {
        unsigned long long x;
        int s, next;
    }v[MAXN];
    int first[76545], p;
    Hash_Table()
    {
        memset(first, -1, sizeof (first));
        p = 0;
    }
    int &operator[](const unsigned long long &x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return v[i].s;
        v[p].x = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].s = 0;
    }
    bool count(const unsigned long long &x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return 1;
        return 0;
    }
}mp;
// map<unsigned long long, int> mp;
struct Tree
{
    struct Node
    {
        Node *ch[4];
        int s;
        Node()
        {
            memset (ch, 0, sizeof (ch));
            s = 0;
        }
    }*root = new Node();
    void Insert(char *x, int n)
    {
        Node *rt = root;
        for (int i = 1; i <= n; i++)
        {
            if (rt->ch[id[x[i]]] == NULL) rt->ch[id[x[i]]] = new Node();
            rt = rt->ch[id[x[i]]];
            rt->s++;
        }
    }
    void dfs(Node *rt, int Sum, unsigned long long x)
    {
        rt->s = (rt->s + Sum) % MOD;
        // printf ("%d\n", x);
        mp[x] = rt->s;
        for (int i = 0; i <= 3; i++)
            if (rt->ch[i])
                dfs(rt->ch[i], rt->s, x * base + i + 1);
    }
    void DFS()
    {
        dfs(root, 0, 0);
    }
    int Query(char *x, int pos, int n)
    {
        int l = 0, r = (n - pos + 1);
        int ans = 0;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (mp.count(Calc(Hash_s, pos, pos + mid))) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        return mp[Calc(Hash_s, pos, pos + ans)];
    }
    int Query2(char *x, int pos, int n)
    {
        int l = 0, r = (n - pos + 1);
        int ans = 0;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (mp.count(Calc(Hash_s_rev, pos, pos + mid))) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        return mp[Calc(Hash_s_rev, pos, pos + ans)];
    }
}rt;
int main()
{
    scanf ("%s", s + 1);
    int n = strlen(s + 1);
    id['A'] = 0, id['T'] = 1, id['C'] = 2, id['G'] = 3;
    BASE[0] = 1;
    for (int i = 1; i <= MAXN - 5; i++) BASE[i] = BASE[i - 1] * base;
    Hash(s, Hash_s, n);
    reverse_copy(s + 1, s + n + 1, s_rev + 1);
    Hash(s_rev, Hash_s_rev, n);
    int m = read();
    for (int i = 1; i <= m; i++)
    {
        scanf ("%s", c + 1);
        rt.Insert(c, strlen(c + 1));
    }
    rt.DFS();
    // printf ("%d\n", mp[10]);
    for (int i = 1; i <= n; i++)
        H[i] = rt.Query(s, i, n);
    for (int i = 1; i <= n; i++)
        L[i] = rt.Query2(s, i, n);
    reverse(L + 1, L + n + 1);
    long long ans = 0;
    for (int i = 1; i < n; i++)
        ans = (ans + L[i] * H[i + 1] % MOD) % MOD;
    printf ("%lld\n", ans);
}