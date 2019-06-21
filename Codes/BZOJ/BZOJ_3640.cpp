#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 155;
struct edge
{
    int END, next;
}v[10005];
int first[MAXN], p;
int du[MAXN], t[MAXN];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
double a[MAXN][MAXN], c[MAXN][MAXN];
double DP[10005][MAXN], tmp[MAXN];
void Gauss_Jordan(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int k = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(a[j][i]) > fabs(a[k][i]))
                k = j;
        if (k != i)
        {
            for (int j = i; j <= n; j++)
                swap(a[i][j], a[k][j]);
            for (int j = 1; j <= n; j++)
                swap(c[i][j], c[k][j]);
        }
        for (int j = 1; j <= n; j++)
            if (j != i)
            {
                double t = a[j][i] / a[i][i];
                for (k = i; k <= n; k++)
                    a[j][k] -= a[i][k] * t;
                for (k = 1; k <= n; k++)
                    c[j][k] -= c[i][k] * t;
            }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            c[i][j] /= a[i][i];
}

int main()
{
    int n = read(), m = read(), hp = read();
    memset (first, -1, sizeof (first));
    for (int i = 1; i <= n; i++) t[i] = read();
    for (int i = 1; i <= m; i++)
    {
        int b = read(), d = read();
        add(b, d), du[b]++;
        if (b != d) add(d, b), du[d]++;
    }
    for (int i = 1; i <= n; i++)
    {
        a[i][i] = 1, c[i][i] = 1;
        if (t[i] == 0)
        {
            for (int j = first[i]; j != -1; j = v[j].next)
                if (v[j].END != n)
                    a[i][v[j].END] -= 1.0 / du[v[j].END];
        }
    }
    Gauss_Jordan(n);
    double ans = 0;
    for (int i = hp; i >= 1; i--)
    {
        memset (tmp, 0, sizeof (tmp));
        if (i == hp)
            tmp[1] = 1;
        for (int j = 1; j <= n; j++)
            if (t[j] && i + t[j] <= hp)
                for (int k = first[j]; k != -1; k = v[k].next)
                    if (v[k].END != n)
                        tmp[j] += DP[i + t[j]][v[k].END] / du[v[k].END];
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                DP[i][j] += tmp[k] * c[j][k];
        ans += DP[i][n];
    }
    printf ("%.8f\n", ans);
    // while (1);
}