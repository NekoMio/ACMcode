#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;
struct edge
{
    int START, END, next, v;
} E[200005], ZHENG[200005], FAN[200005];
int first[100005], p, FZHENG[100005], FZ, FFAN[100005], FF;
void add(int a, int b, int c, int d)
{
    if (c == 0)
    {
        E[p].START = a;
        E[p].END = b;
        E[p].next = first[a];
        first[a] = p++;
    }
    else if (c == 1)
    {
        ZHENG[FZ].START = a;
        ZHENG[FZ].END = b;
        ZHENG[FZ].v = d;
        ZHENG[FZ].next = FZHENG[a];
        FZHENG[a] = FZ++;
    }
    else
    {
        FAN[FF].START = a;
        FAN[FF].END = b;
        FAN[FF].v = d;
        FAN[FF].next = FFAN[a];
        FFAN[a] = FF++;
    }
}
stack<int> st;
int belong[100005];
int low[100005], dfn[100005], Index = 0, T = 0;
bool flag[100005];
int value[100005];
void Tarjan(int rt)
{
    low[rt] = dfn[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    for (int i = first[rt]; i != -1; i = E[i].next)
    {
        if (!dfn[E[i].END])
        {
            Tarjan(E[i].END);
            low[rt] = min(low[rt], low[E[i].END]);
        }
        else if (flag[E[i].END])
        {
            low[rt] = min(low[rt], dfn[E[i].END]);
        }
    }
    if (dfn[rt] == low[rt])
    {
        T++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            flag[v] = 0;
            value[T]++;
            belong[v] = T;
        } while (dfn[v] != low[v]);
    }
}
int father[100005];
int find(int x)
{
    if (father[x] != x)
        father[x] = find(father[x]);
    return father[x];
}
int disZ[100005];
void Spfa1(int x)
{
    queue<int> Q;
    bool flag[100005] = {0};
    flag[x] = 1;
    disZ[x] = 1;
    Q.push(x);
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        flag[k] = 0;
        for (int i = FZHENG[k]; i != -1; i = ZHENG[i].next)
        {
            if (disZ[ZHENG[i].END] < disZ[k] + ZHENG[i].v)
            {
                disZ[ZHENG[i].END] = disZ[k] + ZHENG[i].v;
                if (!flag[ZHENG[i].END])
                {
                    Q.push(ZHENG[i].END);
                    flag[ZHENG[i].END] = 1;
                }
            }
        }
    }
}
int disF[100005];
void Spfa2(int x)
{
    queue<int> Q;
    bool flag[100005] = {0};
    flag[x] = 1;
    disF[x] = 1;
    Q.push(x);
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        flag[k] = 0;
        for (int i = FFAN[k]; i != -1; i = FAN[i].next)
        {
            if (disF[FAN[i].END] < disF[k] + FAN[i].v)
            {
                disF[FAN[i].END] = disF[k] + FAN[i].v;
                if (!flag[FAN[i].END])
                {
                    Q.push(FAN[i].END);
                    flag[FAN[i].END] = 1;
                }
            }
        }
    }
}
int main()
{
    // freopen("cown.in", "r", stdin);
    // freopen("cown.out", "w", stdout);
    memset(first, -1, sizeof(first));
    memset(FFAN, -1, sizeof(FFAN));
    memset(FZHENG, -1, sizeof(FZHENG));
    memset(dfn, 0, sizeof(dfn));
    //memset(disZ, 0x80, sizeof(disZ));
    //memset(disF, 0x80, sizeof(disF));
    int n, m, s, e;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s, &e);
        add(s, e, 0, 0);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = first[i]; j != -1; j = E[j].next)
            if (belong[i] != belong[E[j].END])
            {
                add(belong[i], belong[E[j].END], 1, value[belong[E[j].END]]);
                add(belong[E[j].END], belong[i], 2, value[belong[i]]);
                //    father[belong[E[j].END]] = belong[i];
            }
    Spfa1(belong[1]);
    Spfa2(belong[1]);
    int Max = 0;
    for (int i = 0; i < FZ; i++)
    {
        int S=disF[ZHENG[i].START] + disZ[ZHENG[i].END]+value[belong[1]]-2;
        if(disF[ZHENG[i].START]==0||disZ[ZHENG[i].END]==0)continue;
        Max = max(Max,S);
    }
    printf("%d", Max);
}
