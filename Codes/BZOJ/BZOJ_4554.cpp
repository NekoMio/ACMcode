#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 55;
char mp[MAXN][MAXN];
int a[MAXN][MAXN], b[MAXN][MAXN];
int xp, yp;
struct edge
{
    int END, next;
}v[MAXN * 100];
int first[MAXN * 100], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int tim;
int Link[MAXN * 100];
int vis[MAXN * 100];
bool find(int x)
{
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END] != tim)
        {
            vis[v[i].END] = tim;
            if (Link[v[i].END] == -1 || find(Link[v[i].END]))
            {
                Link[v[i].END] = x;
                return 1;
            } 
        }
    }
    return 0;
}
int main()
{
    memset (first, -1, sizeof (first));
    memset (Link, -1, sizeof (Link));
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        scanf ("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
    {
        xp++;
        for (int j = 1; j <= m; j++)
        {
            a[i][j] = xp;
            if (mp[i][j] == '#') xp++;
        }
    }
    // yp = xp;
    for (int j = 1; j <= m; j++)
    {
        yp++;
        for (int i = 1; i <= n; i++)
        {
            b[i][j] = yp;
            if (mp[i][j] == '#') yp++;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '*') 
                add(a[i][j], b[i][j]);
    int ans = 0;
    for (int i = 1; i <= xp; i++)
    {
        tim++;
        ans += find(i);
    }
    printf ("%d\n", ans);
    // while (1);
}