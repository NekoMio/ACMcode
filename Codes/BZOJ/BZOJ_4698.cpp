#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100 * 1000 + 5;
int s[1005][105];
struct SAM
{
    int last, cnt;
    map<int, int> a[MAXN << 1];
    int fa[MAXN << 1], Max[MAXN << 1];
    int Sum[MAXN << 1], Mark[MAXN << 1];
    SAM()
    {
        last = ++cnt;
    }
    void extend(int c)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[q] == Max[p] + 1) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                a[nq] = a[q];
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
    }
    int Query(int n)
    {
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int now = 1;
            for (int j = 2; j <= s[i][0]; j++)
            {
                int x = s[i][j] - s[i][j - 1];
                while (!a[now].count(x)) now = fa[now];
                if (!now) now = 1;
                now = a[now][x];
                int tmp = now;
                for (; tmp && Mark[tmp] != i; tmp = fa[tmp])
                {
                    Sum[tmp]++;
                    if (Sum[tmp] == n) ans = max(ans, Max[tmp]);
                    Mark[tmp] = i;
                }
            }
        }
        return ans + 1;
    }
}sam;
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        s[i][0] = read();
        sam.last = 1;
        s[i][1] = read();
        for (int j = 2; j <= s[i][0]; j++)
        {
            s[i][j] = read();
            sam.extend(s[i][j] - s[i][j - 1]);
        }
    }
    printf ("%d\n", sam.Query(n));
}