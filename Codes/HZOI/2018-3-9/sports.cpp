#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct data
{
    int pos, v;
    data(int _v, int _pos) : v(_v), pos(_pos) {;}
};
int a[MAXN][MAXN];
int num[MAXN], pos[MAXN];
bool vis[MAXN];
int n, m;
data Max()
{
    int v = 0, pos = 0;
    for (int i = 1; i <= m; i++)
        if (num[i] > v)
            v = num[i], pos = i;
    return data(v, pos);
}
bool Judge(int mid)
{
    memset (num, 0, sizeof (num));
    memset (pos, 0, sizeof (pos));
    memset (vis, 0, sizeof (vis));
    for (int i = 1; i <= n; i++) num[a[i][++pos[i]]]++;
    data s = Max();
    while (s.v > mid)
    {
        int t = s.pos;
        vis[t] = 1;
        int Num = 0;
        for (int i = 1; i <= n; i++)
        {
            // if (pos[i] == m) return 0;
            if (a[i][pos[i]] == t)
            {
                num[t]--;
                while (vis[a[i][pos[i]]]) pos[i]++;
                if (pos[i] == m + 1) return 0;
                num[a[i][pos[i]]]++;
            }
        }
        s = Max();
    }
    return 1;
}
int main()
{
    // freopen ("sports.in", "r", stdin);
    // freopen ("sports.out", "w", stdout);
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = read();
    int l = 1, r = n;
    int ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (Judge(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf ("%d\n", ans);
}