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
const int MAXN = 2005;
int a[MAXN][MAXN];
unsigned int Hash[MAXN][MAXN][5];
unsigned int pow1[MAXN], pow2[MAXN];
int base1 = 1000000007, base2 = 1000000009;
bool Judge(int x, int y, int l)
{
    unsigned int hash, tmp;
    hash = Hash[x + l - 1][y + l - 1][1] - Hash[x - l][y + l - 1][1] * pow1[l + l - 1] - Hash[x + l - 1][y - l][1] * pow2[l + l - 1] + Hash[x - l][y - l][1] * pow1[l + l - 1] * pow2[l + l - 1];
    tmp = Hash[x + l - 1][y - l + 1][2] - Hash[x - l][y - l + 1][2] * pow1[l + l - 1] - Hash[x + l - 1][y + l][2] * pow2[l + l - 1] + Hash[x - l][y + l][2] * pow1[l + l - 1] * pow2[l + l - 1];
    if (hash != tmp) return false;
    tmp = Hash[x - l + 1][y + l - 1][3] - Hash[x + l][y + l - 1][3] * pow1[l + l - 1] - Hash[x - l + 1][y - l][3] * pow2[l + l - 1] + Hash[x + l][y - l][3] * pow1[l + l - 1] * pow2[l + l - 1];
    // printf ("%d\n", tmp);
    if (hash != tmp) return false;
    tmp = Hash[x - l + 1][y - l + 1][4] - Hash[x + l][y - l + 1][4] * pow1[l + l - 1] - Hash[x - l + 1][y + l][4] * pow2[l + l - 1] + Hash[x + l][y + l][4] * pow1[l + l - 1] * pow2[l + l - 1];
    return hash == tmp;
}
int n, m;
int Solve(int x, int y)
{
    int l = 1, r = min(min(x, n - x + 1), min(y, m - y + 1));
    // printf ("%d %d\n", l, r);
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (Judge(x, y, mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
int main()
{
    // freopen ("1.out", "w", stdout);
    n = read(), m = read();
    n = n * 2 + 1;
    m = m * 2 + 1;
    for (int i = 2; i < n; i += 2)
        for (int j = 2; j < m; j += 2)
        {
            a[i][j] = read();  
            for (int k = 1; k <= 4; k++) Hash[i][j][k] = a[i][j];
        }
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i < MAXN; i++)
        pow1[i] = pow1[i - 1] * base1, pow2[i] = pow2[i - 1] * base2;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            Hash[i][j][1] += Hash[i - 1][j][1] * base1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            Hash[i][j][1] += Hash[i][j - 1][1] * base2;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            Hash[i][j][2] += Hash[i - 1][j][2] * base1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            Hash[i][j][2] += Hash[i][j + 1][2] * base2;
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++)
            Hash[i][j][3] += Hash[i + 1][j][3] * base1;
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++)
            Hash[i][j][3] += Hash[i][j - 1][3] * base2;
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            Hash[i][j][4] += Hash[i + 1][j][4] * base1;
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            Hash[i][j][4] += Hash[i][j + 1][4] * base2;
    // for (int k = 1; k <= 4; k++)
    // {
    //     for (int i = 1; i <= n; i++)
    //         for (int j = 1; j <= m; j++)
    //             printf ("%d%c", Hash[i][j][k], " \n"[j == m]);
    //     printf ("\n");
    // }
    int ans = 0;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cnt++;
            if ((i ^ j ^ 1) & 1)
                ans += Solve(i, j) / 2;
            // printf ("%d\n", ans);
        }
    printf ("%d\n", ans);
    // while (1);
}