#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MAXN = 1e5 + 5;
int a[MAXN], type[MAXN];
int f[MAXN][35], pre[MAXN][35];
int ans[MAXN];
int val[MAXN];
int Get_Num(int x)
{
    int ans = 0;
    while (x)
    {
        ans += x & 1;
        x >>= 1;
    }
    return ans;
}
int main()
{
    int n, m, c;
    scanf ("%d%d%d", &n, &m, &c);
    char s[5];
    for (int i = 1; i < n; i++)
    {
        scanf ("%s", s);
        if (s[0] == 'X') type[i] = 1;
        else if (s[0] == 'A') type[i] = 2;
        else if (s[0] == 'O') type[i] = 3;
    }
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]);
    f[1][a[1]] = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= m; j++) if (f[i][j])
        {
            for (int k = 0; k <= min(j, a[i + 1]); k++) if (j + a[i + 1] - k <= m)
            {
                if (type[i] == 1)
                    f[i + 1][j + a[i + 1] - 2 * k] = f[i][j], pre[i + 1][j + a[i + 1] - 2 * k] = j;
                if (type[i] == 2)
                    f[i + 1][k] = f[i][j], pre[i + 1][k] = j;
                if (type[i] == 3)
                    f[i + 1][j + a[i + 1] - k] = f[i][j], pre[i + 1][j + a[i + 1] - k] = j;
            }
        }
    }
    if (!f[n][Get_Num(c)]) return printf ("OvO\n"), 0;
    ans[n] = c;
    int now = Get_Num(c);
    for (int i = n; i >= 2; i--)
    {
        int p = pre[i][now];
        // printf ("%d\n", p);
        if (type[i - 1] == 2)
        {
            int mid = now;
            int s1 = 0, s2 = 0, s3 = 0;
            for (int j = 0; j < m; j++)
            {
                if ((ans[i]&(1<<j)) && (s1 < mid)) s1++, ans[i - 1] += (1 << j), val[i] += (1 << j);
                else if ((!(ans[i]&(1<<j))) && s2 + mid < p) s2++, ans[i - 1] += (1 << j);
                else if ((!(ans[i]&(1<<j))) && s3 + mid < a[i]) s3++, val[i] += (1 << j);
            }
        }
        else if (type[i - 1] == 1)
        {
            int mid = (p + a[i] - now) / 2;
            int s1 = 0, s2 = 0, s3 = 0;
            for (int j = 0; j < m; j++)
            {
                if ((!(ans[i]&(1<<j))) && (s1 < mid)) s1++, ans[i - 1] += (1 << j), val[i] += (1 << j); 
                else if ((ans[i]&(1<<j)) && (s2 + mid < p)) s2++, ans[i - 1] += (1 << j);
                else if ((ans[i]&(1<<j)) && (s3 + mid < a[i])) s3++, val[i] += (1 << j);
            }
        }
        else
        {
            int mid = p + a[i] - now;
            int s1 = 0, s2 = 0, s3 = 0;
            for (int j = 0; j < m; j++)
            {
                if ((ans[i]&(1<<j)) && (s1 < mid)) s1++, ans[i - 1] += (1 << j), val[i] += (1 << j);
                else if ((ans[i]&(1<<j)) && (s2 + mid < p)) s2++, ans[i - 1] += (1 << j);
                else if ((ans[i]&(1<<j)) && (s3 + mid < a[i])) s3++, val[i] += (1 << j);
            }
        }
        now = p;
    }
    val[1] += ans[1];
    for (int i = 1; i <= n; i++)
        printf ("%d ", val[i]);
    // while(1);
}
