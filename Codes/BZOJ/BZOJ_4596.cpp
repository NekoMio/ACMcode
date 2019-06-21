#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
vector<pair<int, int> > v[17];
const int MOD = 1e9 + 7;
long long a[18][18];
void add(int c, int b)
{
    a[c][b]--, a[b][c]--;
    a[c][c]++, a[b][b]++;
}
int gauss(int n)
{
    long long ans = 1;
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
    int n = read();
    for (int i = 0; i <= n - 2; i++)
    {
        int m = read();
        for (int j = 1; j <= m; j++)
        {
            int a = read(), b = read();
            v[i].push_back(pair<int, int>(a, b));
        }
    }
    int N = (1 << (n - 1)) - 1;
    long long ans = 0;
    for (int S = 0; S <= N; S++)
    {
        memset (a, 0, sizeof (a));
        for (int i = 0; i < n - 1; i++)
            if (!(S & (1 << i)))
                for (int j = 0; j < v[i].size(); j++)
                    add(v[i][j].first, v[i][j].second); 
        if (Get_Num(S) & 1)
            ans = (ans - gauss(n - 1) + MOD) % MOD;
        else
            ans = (ans + gauss(n - 1)) % MOD;
    }
    printf ("%lld\n", ans);
}