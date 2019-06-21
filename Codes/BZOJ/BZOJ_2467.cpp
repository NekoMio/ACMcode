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
const int MOD = 2007;
int a[500][500];
inline int gauss(int n)
{
    int ans = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = (a[i][j] + MOD) % MOD;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
            while (a[j][i])
            {
                int t = a[i][i] / a[j][i];
                for (int k = i; k <= n; k++)
                {
                    a[i][k] = (a[i][k] - a[j][k] * t % MOD + MOD) % MOD;
                    swap(a[i][k], a[j][k]);
                }
                ans = (-ans + MOD) % MOD;
            }
        ans = ans * a[i][i] % MOD;
    }
    return ans;
}
int main()
{
    int t = read();
    while (t--)
    {
        int n = read();
        memset (a, 0, sizeof (a));
        for (int now = 1;;)
        {
            int x = now;
            a[now][now + 1] += 1;
            a[now][now]++;
            a[now + 1][now] += 1;
            a[now + 1][now + 1]++;
            a[now + 1][now + 2] += 1;
            a[now + 1][now + 1]++;
            a[now + 2][now + 1] += 1;
            a[now + 2][now + 2]++;
            a[now + 3][now + 2] += 1;
            a[now + 3][now + 3]++;
            a[now + 2][now + 3] += 1;
            a[now + 2][now + 2]++;
            a[now + 3][(now + 3) % (4 * n) + 1] += 1;
            a[now + 3][now + 3]++;
            a[(now + 3) % (4 * n) + 1][now + 3] += 1;
            a[(now + 3) % (4 * n) + 1][(now + 3) % (4 * n) + 1]++;
            now = (now + 3) % (4 * n) + 1;
            a[now][x] += 1;
            a[now][now]++;
            a[x][now] += 1;
            a[x][x]++;
            if (now == 1) break;
        }
        for (int i = 1; i <= 4 * n; i++)
            for (int j = 1; j <= 4 * n; j++)
                if (i != j && a[i][j] > 0)
                    a[i][j] = -a[i][j];
        printf ("%d\n", gauss(4 * n - 1));
    }
}