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
const int MOD = 1e9;
int id[50][50];
char s[55][55];
int dx[4] = {0,0,1,-1},
    dy[4] = {1,-1,0,0};
long long a[300][300];
void add(int c, int b)
{
    a[c][b]--, a[b][c]--;
    a[c][c]++, a[b][b]++;
}
long long gauss(int n)
{
    long long ans = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = (MOD + a[i][j]) % MOD;
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
                ans = (MOD - ans) % MOD;
            }
        ans = ans * a[i][i] % MOD;
    }
    return ans;
}
inline bool OK(int a, int b)
{
    if (!id[a][b]) return 0;
    return 1;
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        scanf ("%s", s[i] + 1);
    int Index = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] != '*')
                id[i][j] = ++Index;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] != '*')
                for (int k = 0; k <= 3; k++)
                    if (OK(i + dx[k], j + dy[k]))
                        add(id[i][j], id[i + dx[k]][j + dy[k]]);
    for (int i = 1; i <= Index; i++)
        for (int j = 1; j <= Index; j++)
            a[i][j] /= 2;
    printf ("%lld\n", gauss(Index - 1));
}