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
int n;
#define pre(x) (x == 1 ? n : x - 1)
#define nxt(x) (x == n ? 1 : x + 1)
#define dis(i, j) (i <= j ? j - i + 1 : n + j - i + 1)
char s[205];
int cnt[205][205], pr[205];
double f[205][205], g[205][205], p[205][205][205];
double C[205][205], Mi[205][205][205];
double P(int i, int j, int k);
double G(int i, int j)
{
    if (g[i][j] > -1e60) return g[i][j];
    double &ans = g[i][j] = 0;
    if (i == j)
    {
        ans = s[j] == '.';
        return ans;
    }
    for (int k = i; k != j; k = nxt(k))
        if (s[k] == '.')
            ans = ans + P(i, j, k);
    ans += P(i, j, j);
    return ans;
}
double P(int i, int j, int k)
{
    if (p[i][j][k] > -1e60) return p[i][j][k];
    double &ans = p[i][j][k] = 0;
    if (s[j] == 'X' || s[k] == 'X') return ans = 0;
    if (k == j) return ans = (cnt[i][j] == 1);
    int lc = (k == i ? 0 : cnt[i][pre(k)]), rc = ((k == pre(j)) ? 0 : cnt[nxt(k)][pre(j)]);
    ans = C[lc + rc][lc];
    ans = ans * Mi[dis(i, j)][dis(i, k)][lc + 1];
    // printf ("%d %d\n", dis(i, j), dis(i, k));
    ans = ans * Mi[dis(i, j)][dis(nxt(k), j)][rc];
    ans = ans * G(i, k) * G(nxt(k), j);
    // printf ("P[%d][%d][%d] = %.3f\n", i, j, k, ans);
    return ans;
}
double F(int i, int j)
{
    if (f[i][j] >= -1e60) return f[i][j];
    double &ans = f[i][j] = 0;
    if (i == j || G(i, j) == 0)
        return ans = 0;
    int len = 0;
    for (int k = i; k != j; k = nxt(k), len++)
    {
        ans = ans + P(i, j, k) * (F(i, k) + F(nxt(k), j) + len / 2.0);
    }
    ans = ans * (1.0 / G(i, j));
    // printf ("F[%d][%d] = %.3f\n", i, j, ans);
    return ans;
}
int main()
{
    int T = read();
    while (T--)
    {
        scanf ("%s", s + 1);
        n = strlen(s + 1);
        memset (f, 0xdd, sizeof (f));
        memset (g, 0xdd, sizeof (g));
        memset (p, 0xdd, sizeof (p));
        for (int i = 0; i <= 200; i++)
        {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
        for (int i = 1; i <= n; i++) pr[i] = pr[i - 1] + (s[i] == '.');
        if (pr[n] == 0)
        {
            printf ("0\n");
            continue;
        }
        //for (int i = 1; i <= n; i++) printf ("%d ", pr[i]);
        //printf ("\n");
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cnt[i][j] = i > j ? pr[n] - (pr[i - 1] - pr[j]) : (pr[j] - pr[i - 1]);
                //printf ("%d ", cnt[i][j]);
            }
            //printf ("\n");
        }
        for (int i = 0; i <= n; i++) Mi[i][0][0] = Mi[0][i][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                Mi[i][j][0] = 1;
                for (int k = 1; k <= n; k++)
                    Mi[i][j][k] = Mi[i][j][k - 1] * (1.0 * j / i);
            }
        double ans = 0;
        // F(3, 1);
        // G(3, 2);
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == '.')
            {
                ans = ans + F(nxt(i), i) * G(nxt(i), i);
                //printf ("F[%d][%d]=%.3f\n", nxt(i), i, F(nxt(i), i));
                //printf ("G[%d][%d]=%.3f\n", nxt(i), i, G(nxt(i), i));
            }
        }
        ans = ans + ((n - 1.0) / 2.0);
        printf ("%.10f\n", ans);
    }
}
