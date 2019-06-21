#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
using namespace std;
inline void gmin(int &a, int b) { if (a > b) a = b; }
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char s[100005];
struct Node
{
    Node *ch[2];
    int Min, lazy;
    Node ()
    {
        Min = lazy = 0x3f3f3f3f;
        ch[0] = ch[1] = NULL;
    }
    void Pushlazy(int x)
    {
        gmin(Min, x);
        gmin(lazy, x);
    }
    void Pushdown()
    {
        if (lazy < 0x3f3f3f3f)
        {
            ch[0]->Pushlazy(lazy);
            ch[1]->Pushlazy(lazy);
            lazy = 0x3f3f3f3f;
        }
    }
    void Pushup()
    {
        Min = min(ch[0]->Min, ch[1]->Min);
    }
}*root[2];
void Build(Node *rt, int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    rt->ch[0] = new Node(), rt->ch[1] = new Node();
    Build(rt->ch[0], l, mid);
    Build(rt->ch[1], mid + 1, r);
    rt->Pushup();
}
void Set(Node *rt, int L, int R, int l, int r, int x)
{
    if (L <= l && R >= r)
    {
        rt->Pushlazy(x);
        return;
    }
    rt->Pushdown();
    int mid = l + r >> 1;
    if (L <= mid) Set(rt->ch[0], L, R, l, mid, x);
    if (R > mid) Set(rt->ch[1], L, R, mid + 1, r, x);
    rt->Pushup();
}
void DFS(Node *rt, int l, int r, int *f)
{
    if (l == r)
    {
        f[l] = rt->Min;
        return;
    }
    rt->Pushdown();
    int mid = l + r >> 1;
    DFS(rt->ch[0], l, mid, f);
    DFS(rt->ch[1], mid + 1, r, f);
}
struct data
{
    char s;
    int id;
    data(char _s, int b) : s(_s), id(b) {}
    bool operator == (const data &a) const
    {
        return s == a.s && id == a.id;
    }
};
list<data> lst;
// list<char> ls;
int ans[1000005][15];
int f[100005], g[100005];
int main()
{
    // freopen ("program.in", "r", stdin);
    // freopen ("program.out", "w", stdout);
    int n = read(), q = read();
    scanf ("%s", s + 1);
    // for (int i = 1; i <= n; i++) ls.push_back(s[i]);
    lst.clear();
    for (int i = 1; i <= n; i++)
        lst.push_back(data(s[i], i));
    lst.push_front(data('>', 0));
    list<data>::iterator now = lst.begin(), next, last;
    int lastid = 0;
    int op = 1;
    // memset (ans, 0, sizeof (ans));
    int cnt = 0, Max = 0;
    root[0] = new Node(), root[1] = new Node();
    Build(root[0], 1, n);
    Build(root[1], 1, n);
    now++;
    while (1)
    {
        ++cnt;
        // fprintf (stderr, "%d\n", now->id);
        // cout << *now << endl;
        // Max = max(Max, now->id);
        if (op == 1)
        {
            Set(root[0], lastid + 1, now->id, 1, n, cnt);
        }
        else
        {
            Set(root[1], now->id + 1, lastid, 1, n, cnt);
        }
        // if (op == -1)
        //     if (!g[now->id]) 
        //         g[now->id] = cnt;
        
        if (now->s >= '0' && now->s <= '9')
        {
            ans[cnt][now->s - '0']++;
            (now->s)--;
            next = now;
            // if (next == lst.begin() && op == -1) break;
            // else
            // {
                if (op == -1) next--;
                else next++;
            // }
            lastid = now->id;
            // if (op == -1)
            //     if (!g[now->id]) 
            //         g[now->id] = cnt;
            if (now->s == '0' - 1)
            {
                lst.erase(now);
                now = lst.end();
            }
        }
        else if (now->s == '<' || now->s == '>')
        {
            op = (now->s == '<' ? -1 : 1);
            if (lastid)
                if (s[lastid] == '<' || s[lastid] == '>')
                    lst.erase(last);
            next = now;
            // if (next == lst.begin() && op == -1) break;
            // else
            // {
                if (op == -1) next--;
                else next++;
            // }
            lastid = now->id;
            // if (op == -1)
            //     if (!g[now->id]) 
            //         g[now->id] = cnt;
        }
        last = now;
        now = next;
        if (now == lst.end()) break;
        // now += op;
        // if (c[now] == 0) break;
    }
    for (int i = 1; i <= cnt; i++)
        for (int j = 0; j <= 9; j++)
            ans[i][j] += ans[i - 1][j];
    DFS(root[0], 1, n, f);
    DFS(root[1], 1, n, g);
    f[n + 1] = cnt + 1;
    // for (int i = 1; i <= n; i++)
    //     printf ("%d %d\n", f[i], g[i]);
    while (q--)
    {
        int l = read(), r = read();
        for (int i = 0; i <= 9; i++)
            printf ("%d ", ans[min(f[r + 1] - 1, g[l] - 1)][i] - ans[f[l] - 1][i]);
        printf ("\n");
    }
}