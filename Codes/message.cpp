#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
struct edge
{
    int END, next, v;
} E[100005], v[100005];
int Head[50005], q, first[50005], p;
void add(int a, int b, int c, int op)
{
    if (op == 1)
    {
        E[q].END = b;
        E[q].next = Head[a];
        E[q].v = c;
        Head[a] = q++;
    }
    else
    {
        v[p].END = b;
        v[p].next = first[a];
        v[p].v = c;
        first[a] = p++;
    }
}
int dfn[50005], low[50005], Index, T, belong[50005];
stack<int> st;
bool instack[50005];
void Tarjan(int rt)
{
    dfn[rt] = low[rt] = ++Index;
    st.push(rt);
    instack[rt] = 1;
    for (int i = Head[rt]; i != -1; i = E[i].next)
    {
        if (!dfn[E[i].END])
        {
            Tarjan(E[i].END);
            low[rt] = min(low[rt], low[E[i].END]);
        }
        else if (instack[E[i].END])
            low[rt] = min(low[rt], dfn[E[i].END]);
    }
    if (dfn[rt] == low[rt])
    {
        T++;
        int a;
        do
        {
            a = st.top();
            st.pop();
            instack[a] = 0;
            belong[a] = T;
        } while (dfn[a] != low[a]);
    }
}
struct data
{
    int END, v;
    bool operator<(const data &a) const
    {
        return v > a.v;
    }
};
priority_queue<data> Q;
int dis[50005];
int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        memset(Head, -1, sizeof(Head));
        memset(first, -1, sizeof(first));
        memset(belong, 0, sizeof(belong));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(instack, 0, sizeof(instack));
        memset(dis, 0x3f, sizeof(dis));
        while (!st.empty())
            st.pop();
        q = p = Index = T = 0;
        if (n == 0 && m == 0)
            break;
        int a, b, c;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c, 1);
        }
        for (int i = 0; i < n; i++)
            if (!dfn[i])
                Tarjan(i);
        for (int i = 0; i < n; i++)
            for (int j = Head[i]; j != -1; j = E[j].next)
                if (belong[i] != belong[E[j].END])
                    add(belong[i], belong[E[j].END], E[j].v, 0);
        int S = belong[0];
        dis[S] = 0;
        Q.push((data){S, 0});
        while (!Q.empty())
        {
            data k = Q.top();
            Q.pop();
            for (int i = first[k.END]; i != -1; i = v[i].next)
                if (dis[v[i].END] > v[i].v)
                {
                    Q.push((data){v[i].END, v[i].v});
                    dis[v[i].END] = v[i].v;
                }
        }
        long long ans = 0;
        for (int i = 1; i <= T; i++)
            ans += dis[i];
        printf("%lld\n", ans);
    }
}