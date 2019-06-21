#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
struct edge
{
    int END, next, S;
}v[1000005];
int first[1000005], p, n;
void add(int a, int b)
{
    v[p].S = a;
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int low[1000005], dfn[1000005], Index, belong[1000005], T, size[1000005], Ans;
bool flag[1000005];
stack<int> st;
int f[1000005];
void dfs(int x)
{
    if (f[x]) return;
    f[x] = size[x];
    int now = 0;
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        dfs(v[i].END);
        now = max(f[v[i].END], now);
    }
    f[x] += now;
}
void Tarjan(int rt)
{
    low[rt] = dfn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for(int i = first[rt]; i != -1; i = v[i].next)
    {
        if(!dfn[v[i].END])
        {
            Tarjan(v[i].END);
            low[rt] = min(low[rt],low[v[i].END]);
        }
        else if(flag[v[i].END])
        {
            low[rt] = min(low[rt],dfn[v[i].END]);
        }
    }
    if(dfn[rt]==low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            belong[v] = T;
            size[T]++;
        }while(dfn[v]!=low[v]);
    }
}
// int father[1000005];
// int find(int x)
// {
//     if (father[x] != x) father[x] = find(father[x]);
//     return father[x];
// }
int main()
{
    memset (first, -1, sizeof (first));
    int n, m;
    scanf ("%d%d", &n, &m);
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%d%d", &a, &b);
        add(a, b);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    int tot = p;
    memset(first, -1, sizeof (first));
    p = 0;
    // for (int i = 1; i <= T; i++) father[i] = i;
    for (int i = 0; i < tot; i++)
    {
        if (belong[v[i].S] != belong[v[i].END])
        {
            // father[find(belong[v[i].S])] = find(belong[v[i].END]);
            add (belong[v[i].S], belong[v[i].END]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= T; i++) 
        dfs(i), ans = max(f[i], ans);
    printf ("%d", ans);
    // while (1);
}