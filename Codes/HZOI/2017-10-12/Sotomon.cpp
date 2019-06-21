#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
struct Hash_Table
{
    struct list
    {
        int next, v;
        int x, y;
    }v[100055];
    int first[76545], p;
    void add(int x, int y, int a, int b)
    {
        v[p].next = first[a];
        v[p].v = b;
        v[p].x = x, v[p].y = y;
        first[a] = p++;
    }
    Hash_Table()
    {
        memset(first, -1, sizeof (first));
        p = 0;
    }
    void insert(int x, int y, int i)
    {
        int H = (x % 7307) * (y % 9091) % 76543;
        add(x, y, H, i);
    }
    int count(int x, int y)
    {
        int H = (x % 7307) * (y % 9091) % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x && v[i].y == y)
                return v[i].v;
        return -1;
    }
}Hash;
//9091 7307
struct data
{
    int type, ID;
    int nextX, nextY;
}v[100050];
struct read
{
    int x, y, type;
}a[100050];
int X[1000005], Y[1000005], p;
void add(int x, int y, int type, int i)
{
    v[p].type = type;
    v[p].nextX = X[x];
    v[p].nextY = Y[y];
    v[p].ID = i;
    X[x] = p;
    Y[y] = p++;
    Hash.insert(x, y, i);
}
int dfn[100005], low[100005], Index, size[100005], T;
bool flag[100050];
stack<int> st;
int dx[8] = {0,0,1,1,1,-1,-1,-1},
    dy[8] = {1,-1,1,-1,0,0,1,-1};
int belong[100005];
void Tarjan(int rt)
{
    dfn[rt] = low[rt] = ++Index;
    st.push(rt);
    flag[rt] = 1;
    if (a[rt].type == 1)
    {
        for (int i = X[a[rt].x]; i != -1; i = v[i].nextX)
        {
            if (!dfn[v[i].ID])
            {
                Tarjan(v[i].ID);
                low[rt] = min(low[rt], low[v[i].ID]);
            }
            else if (flag[v[i].ID])
                low[rt] = min(low[rt], dfn[v[i].ID]);
        }
    }
    else if (a[rt].type == 2)
    {
        for (int i = Y[a[rt].y]; i != -1; i = v[i].nextY)
        {
            if (!dfn[v[i].ID])
            {
                Tarjan(v[i].ID);
                low[rt] = min(low[rt], low[v[i].ID]);
            }
            else if (flag[v[i].ID])
                low[rt] = min(low[rt], dfn[v[i].ID]);
        }
    }
    else
    {
        for (int i = 0; i <= 7; i++)
        {
            int nxt = Hash.count(a[rt].x + dx[i], a[rt].y + dy[i]);
            if (nxt != -1)
            {
                if (!dfn[nxt])
                {
                    Tarjan(nxt);
                    low[rt] = min(low[rt], low[nxt]);
                }
                else if (flag[nxt])
                    low[rt] = min(low[rt], dfn[nxt]);
            }
        }
    }
    if(dfn[rt] == low[rt])
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
        }while(dfn[v] != low[v]);
    }
}
struct edge
{
    int END, next;
}V[1000005];
int first[100005];
void addedge(int a, int b)
{
    V[p].END = b;
    V[p].next = first[a];
    first[a] = p++;
}
int rudu[100005], cudu[100005], ans;
int f[100005];
void DFS(int rt)
{
    f[rt] = size[rt];
    int tmp = 0;
    for (int i = first[rt]; i != -1; i = V[i].next)
    {
        if (!f[V[i].END])
            DFS(V[i].END);
        tmp = max(tmp, f[V[i].END]);
    }
    f[rt] += tmp;
}
int main()
{
    memset(X, -1, sizeof (X));
    memset(Y, -1, sizeof (Y));
    memset(first, -1, sizeof (first));
    int n, r, c;
    scanf ("%d%d%d", &n, &r, &c);
    int x, y, t;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d%d%d", &x, &y, &t);
        a[i].x = x, a[i].y = y, a[i].type = t;
        add(x, y, t, i);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    p = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].type == 1)
        {
            for (int j = X[a[i].x]; j != -1; j = v[j].nextX)
            {
                if (belong[v[j].ID] != belong[i])
                {
                    rudu[v[j].ID]++, cudu[i]++;
                    addedge(belong[i], belong[v[j].ID]);
                }
            }
        }
        else if (a[i].type == 2)
        {
            for (int j = Y[a[i].y]; j != -1; j = v[j].nextY)
            {
                if (belong[v[j].ID] != belong[i])
                {
                    rudu[v[j].ID]++, cudu[i]++;
                    addedge(belong[i], belong[v[j].ID]);
                }
            }
        }
        else
        {
            for (int j = 0; j <= 7; j++)
            {
                int nxt = Hash.count(a[i].x + dx[j], a[i].y + dy[j]);
                if (nxt != -1)
                {
                    if (belong[nxt] != belong[i])
                    {
                        rudu[nxt]++, cudu[i]++;
                        addedge(belong[i], belong[nxt]);
                    }
                }
            }
        }
    }
    ans = 0;
    for (int i = 1; i <= T; i++)
    {
        DFS(i);
        ans = max(ans, f[i]);
    }
    printf ("%d", ans);
}