#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-')f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
const int MAXN = 4000005;
char s[MAXN];
int a[MAXN][2];
struct edge
{
    int END, next;
} v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    if (a < 2 || b < 2) return;
    //printf ("%d %d\n", a, b);
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[MAXN], belong[MAXN], low[MAXN], Index, T, Ind;
bool vis[MAXN];
stack<int> st;
void Tarjan(int rt)
{
    vis[rt] = 1;
    st.push(rt);
    dfn[rt] = low[rt] = ++Ind;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            Tarjan(v[i].END);
            low[rt] = min(low[rt], low[v[i].END]);
        }
        else if (vis[v[i].END])
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    if (dfn[rt] == low[rt])
    {
        T++;
        int x = 0;
        while (x != rt)
        {
            x = st.top(), st.pop();
            belong[x] = T;
            vis[x] = 0;
        }
    }
}
struct data
{
    int a, b;
    data(int _a, int _b) : a(_a), b(_b) {}
};
struct Node
{
    Node *ch[2];
    int id;
    vector<data> v;
    Node()
    {
        ch[0] = ch[1] = NULL;
        id = ++Index;
    }
}*root = new Node(), *Q[MAXN];
void Insert(int n, int p, int pos)
{
    Node *rt = root;
    for (int i = 1; i <= n; i++)
    {
        int nxt = s[i] == '?' ? p : (s[i] - '0');
        if (rt->ch[nxt] == NULL)
        {
            rt->ch[nxt] = new Node();
            Q[rt->ch[nxt]->id] = rt->ch[nxt];
        }
        rt = rt->ch[nxt];
    }
    rt->v.push_back(data(pos, p));
}
int father[MAXN];
void DFS(Node *rt, Node *fa)
{
    int now = fa->id;
    for (int i = 0; i < rt->v.size(); i++)
    {
        a[rt->v[i].a][rt->v[i].b] = ++Index;
        father[a[rt->v[i].a][rt->v[i].b]] = now;
        add(a[rt->v[i].a][rt->v[i].b] << 1, now << 1);
        add(now << 1 | 1, a[rt->v[i].a][rt->v[i].b] << 1 | 1);
        now = a[rt->v[i].a][rt->v[i].b];
    }
    add(rt->id << 1, now << 1);
    add(now << 1 | 1, rt->id << 1 | 1);
    if (rt->ch[0]) DFS(rt->ch[0], rt);
    if (rt->ch[1]) DFS(rt->ch[1], rt);
}
int Id[MAXN];
int n;
bool Qus[MAXN];
void Build()
{
    if (root->ch[0]) DFS(root->ch[0], root);
    if (root->ch[1]) DFS(root->ch[1], root);       
    for (int i = 1; i <= n; i++)
    {
        Id[i] = ++Index;
        
        add(Id[i] << 1 | 1, a[i][1] << 1 | 1);
        add(a[i][1] << 1, Id[i] << 1);
        add(Id[i] << 1 | 1, father[a[i][1]] << 1);
        add(father[a[i][1]] << 1 | 1, Id[i] << 1);   
        add(Id[i] << 1, a[i][0] << 1 | 1);
        add(a[i][0] << 1, Id[i] << 1 | 1);
        add(Id[i] << 1, father[a[i][0]] << 1);
        add(father[a[i][0]] << 1 | 1, Id[i] << 1 | 1);
        if (!Qus[i]) 
            add(Id[i] << 1, Id[i] << 1 | 1);
    }
}
int main()
{
    int __size__=128<<20;
    char *__p__=(char*)malloc(__size__)+__size__;  
    __asm__("movl %0, %%esp\n"::"r"(__p__));
    memset (first, -1, sizeof (first));
    // root->id = 0;
    // Index = 0;
    n = read();
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", s + 1);
        int len = strlen(s + 1);
        for (int j = 1; j <= len; j++)
            if (s[j] == '?')
                Qus[i] = 1;
        Insert(len, 1, i);
        if (Qus[i])
            Insert(len, 0, i);
    }
    Build();
    for (int i = 2; i <= (Index << 1 | 1); i++)
        if (!dfn[i])
            Tarjan(i);
    bool flag = 0;
    for (int i = 1; i <= n; i++)
        if (belong[Id[i] << 1] == belong[Id[i] << 1 | 1])
            flag = 1;
    if (flag) printf ("NO\n");
    else printf ("YES\n");
    // while (1);
}