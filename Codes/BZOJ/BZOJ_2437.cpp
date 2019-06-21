#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
struct edge
{
    int next, END;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int n, m;
int id[105][105], a[105][105];
int vis[10050], cx[10050];
bool nok[10050];
bool dfs(int x, int T)
{
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END] != T && !nok[v[i].END])
        {
            vis[v[i].END] = T;
            if (!cx[v[i].END] || dfs(cx[v[i].END], T))
            {
                cx[x] = v[i].END;
                cx[v[i].END] = x;
                return 1;
            }
        }
    }
    return 0;
}
int ans[10050];
int main()
{
    memset (first, -1, sizeof (first));
    n = read(), m = read();
    char s[50];
    int x, y;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%s", s + 1);
        for (int j = 1; j <= m; j++)
        {
            if (s[j] == 'O')
                a[i][j] = 0;
            else if (s[j] == 'X')
                a[i][j] = 1;
            else
                a[i][j] = 1, x = i, y = j;
        }
    }
    int Index = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (((i + j) & 1) ^ ((x + y) & 1) ^ (a[i][j] == 1))
                id[i][j] = ++Index;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (id[i][j])
            {
                if (i > 1 && id[i - 1][j])
                {
                    add(id[i][j], id[i - 1][j]);
                    add(id[i - 1][j], id[i][j]);
                }
                if (i < n && id[i + 1][j])
                {
                    add(id[i][j], id[i + 1][j]);
                    add(id[i + 1][j], id[i][j]);
                }
                if (j > 1 && id[i][j - 1])
                {
                    add(id[i][j], id[i][j - 1]);
                    add(id[i][j - 1], id[i][j]);
                }
                if (j < m && id[i][j + 1])
                {
                    add(id[i][j], id[i][j + 1]);
                    add(id[i][j + 1], id[i][j]);
                }
            }
        }
    }
    int ID = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (id[i][j])
            {
                if (!cx[id[i][j]])
                {
                    // memset (vis, 0, sizeof (vis));
                    dfs(id[i][j], ++ID);
                }
            }
        }
    }
    // for (int i = 1; i <= Index; i++) printf ("%d\n", cx[i]);
    int k = read();
    for (int t = 1; t <= k; t++)
    {
        int now = id[x][y];
        nok[now] = 1;
        bool f1 = 0, f2 = 0;
        if (cx[now])
        {
            int tmp = cx[now];
            cx[now] = cx[tmp] = 0;
            f1 = !dfs(tmp, ++ID);
        }
        else f1 = 0;
        x = read(), y = read();
        now = id[x][y];
        nok[now] = 1;
        if (cx[now])
        {
            int tmp = cx[now];
            cx[now] = cx[tmp] = 0;
            f2 = !dfs(tmp, ++ID);
        }
        else f2 = 0;
        if (f1 && f2)
            ans[++ans[0]] = t;
        x = read(), y = read();
    }
    printf ("%d\n", ans[0]);
    for (int i = 1; i <= ans[0]; i++)
        printf ("%d\n", ans[i]);
}