#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
int w[1000005];
struct edge
{
    int END, next;
}v[1000005];
int first[1000005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int dfn[1000005], low[1000005], Index;
bool flag[1000005];
int size[1000005], belong[1000005], T;
stack<int> st;
void Tarjan(int rt)
{
    dfn[rt] = low[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1; 
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (!dfn[v[i].END])
        {
            Tarjan(v[i].END);
            low[rt] = min(low[rt], low[v[i].END]);
        }
        else if (flag[v[i].END])
            low[rt] = min(low[rt], dfn[v[i].END]);
    }
    if (low[rt] == dfn[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            belong[v] = T;
            size[T]++;
            flag[v] = 0;
        }while (low[v] != dfn[v]);
    }
}
long long f[1000005][2], g[1000005][2][2];
void DP(int x)
{
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (belong[v[i].END] == belong[x]) continue;
        DP(v[i].END);
        f[x][0] += max(f[v[i].END][0], f[v[i].END][1]);
        f[x][1] += f[v[i].END][0];
    }
    f[x][1] += w[x];
}
long long DFS(int rt)
{
    int now = rt, pre;
    do
    {
        if (now == rt)
        {
            DP(now);
            g[rt][0][0] = f[rt][0];
            g[rt][1][1] = f[rt][1];
        }
        else
        {
            DP(now);
            g[now][0][0] = f[now][0] + max(g[pre][0][1], g[pre][0][0]);
            g[now][1][0] = f[now][0] + max(g[pre][1][1], g[pre][1][0]);
            g[now][0][1] = f[now][1] + g[pre][0][0];
            g[now][1][1] = f[now][1] + g[pre][1][0];
        }
        pre = now;
        for (int i = first[now]; i != -1; i = v[i].next)
        {
            if (belong[v[i].END] == belong[now])
            {
                now = v[i].END;
                break;
            }
        }
    }while (now != rt);
    return max(g[pre][0][0], max(g[pre][0][1], g[pre][1][0]));
}
int main()
{
    memset(first, -1, sizeof (first));
    int n;
    scanf ("%d", &n);
    int b;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d%d", &w[i], &b);
        add(b, i);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    long long ans = 0;
    for (int i = 1; i <= n ; i++)
    {
        if (size[belong[i]] > 1 && !flag[belong[i]])
        {
            flag[belong[i]] = 1;
            ans += DFS(i);
        }
    }
    printf ("%lld", ans);
}