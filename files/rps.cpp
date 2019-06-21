#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
int r[55], p[55], s[55];
int main()
{
    freopen("rps.in", "r", stdin);
    freopen("rps.out", "w", stdout);
    int n;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d%d%d", &r[i], &p[i], &s[i]);
    }
    if (n == 1)
    {
        double ans = 0;
        if (r[1] >= p[1] && r[1] >= s[1])
        {
            ans = ((double)r[1] / 300) * 3 + ((double)p[1] / 300) * 1;
        }
        else if (p[1] >= r[1] && p[1] >= s[1])
        {
            ans = ((double)p[1] / 300) * 3 + ((double)s[1] / 300) * 1;
        }
        else if (s[1] >= r[1] && s[1] >= p[1])
        {
            ans = ((double)s[1] / 300) * 3 + ((double)r[1] / 300) * 1;
        }
        printf ("%.12lf", ans);
        return 0;
    }
    else
    {
        bool no = 0;
        for (int i = 2; i <= n; i++)
        {
            if (r[i] != r[i - 1] || p[i] != p[i - 1]) no = 1;
        }
        if (!no)
        {
            double ans = 0;
            if (r[1] >= p[1] && r[1] >= s[1])
            {
                ans = ((double)r[1] / 300) * 3 + ((double)p[1] / 300) * 1;
            }
            else if (p[1] >= r[1] && p[1] >= s[1])
            {
                ans = ((double)p[1] / 300) * 3 + ((double)s[1] / 300) * 1;
            }
            else if (s[1] >= r[1] && s[1] >= p[1])
            {
                ans = ((double)s[1] / 300) * 3 + ((double)r[1] / 300) * 1;
            }
            ans *= n;
            printf("%.12lf", ans);
        }
    }
}