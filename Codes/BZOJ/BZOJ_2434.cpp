#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1e5 + 5;
char s[MAXN];
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
struct Query_data
{
    int to, next;
}Query[MAXN];
int head[MAXN], P;
int l[MAXN], r[MAXN];
int ID;
int Sum[MAXN << 1];
#define lowbit(_) ((_) & (-_))
void Update(int x, int c)
{
    for (int i = x; i <= ID; i += lowbit(i))
        Sum[i] += c;
}
int query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
int ans[MAXN];
struct ACM
{
    struct Node
    {
        Node *fa, *fail, *ch[26];
        int id;
        Node()
        {
            memset (ch, 0, sizeof (ch));
            fa = fail = NULL;
        }
    }*root, *pos[MAXN];
    int id, Index;
    ACM()
    {
        id = Index = 0;
        root = new Node();
        root->id = ++Index;
    }
    void build(int n)
    {
        Node *now = root;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == 'P') pos[++id] = now;
            else if (s[i] == 'B') now = now->fa;
            else
            {
                if (now->ch[s[i] - 'a'] == NULL)
                {
                    now->ch[s[i] - 'a'] = new Node();
                    now->ch[s[i] - 'a']->id = ++Index;
                    now->ch[s[i] - 'a']->fa = now;
                }
                now = now->ch[s[i] - 'a'];
            }
        }
    }
    void getfail()
    {
        queue<Node*> Q;
        Q.push(root);
        while (!Q.empty())
        {
            Node *now = Q.front();
            Q.pop();
            for (int i = 0; i < 26; i++)
            {
                if (now->ch[i])
                {
                    Node *k = now->fail;
                    while (k && !k->ch[i]) k = k->fail;
                    if (!k) now->ch[i]->fail = root;
                    else now->ch[i]->fail = k->ch[i];
                    Q.push(now->ch[i]);
                }
            }
        }
    }
    void dfsbuild(Node *rt)
    {
        if (rt->fail) add(rt->fail->id, rt->id);
        for (int i = 0; i <= 25; i++)
            if (rt->ch[i])
                dfsbuild(rt->ch[i]);
    }
    void Solve(int n)
    {
        Node *now = root;
        int id = 0;
        Update(l[1], 1);
        for (int i = 0; i < n; i++)
        {
            if (s[i] == 'P')
            {
                id++;
                for (int x = head[id]; x; x = Query[x].next)
                {
                    Node *t = pos[Query[x].to];
                    ans[x] = query(r[t->id]) - query(l[t->id] - 1);
                }
            }
            else if (s[i] == 'B') Update(l[now->id], -1), now = now->fa;
            else now = now->ch[s[i] - 'a'], Update(l[now->id], 1);
        }
    }
}acm;
void dfs(int rt)
{
    l[rt] = ++ID;
    for (int i = first[rt]; i != -1; i = v[i].next)
        dfs(v[i].END);
    r[rt] = ++ID;
}
int main()
{
    // freopen("noi2011_type.in", "r", stdin);
    // freopen("noi2011_type.out", "w", stdout);
    memset (first, -1, sizeof (first));
    // memset (head, -1, sizeof (head));
    scanf ("%s", s);
    int n = strlen(s);
    acm.build(n);
    acm.getfail();
    acm.dfsbuild(acm.root);
    int m = read();
    for (int i = 1; i <= m; i++)
    {
        int x = read(), y = read();
        Query[i].next = head[y];
        head[y] = i;
        Query[i].to = x;
    }
    dfs(1);
    acm.Solve(n);
    for (int i = 1; i <= m; i++)
        printf ("%d\n", ans[i]);
}
