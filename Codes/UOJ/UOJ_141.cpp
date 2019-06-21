#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
// long long vc[(1 << 16) + 1];
int a[15], b[15], cnt;
int mp[15][15];
const int MOD = 998244353;
template<typename _Tp, typename _T>
struct Hash_Table
{
    struct edge
    {
        int next, z;
        _Tp x;
        _T ans;
    }v[500005];
    int p;
    int first[105][76545];
    bool count(int z, _Tp x)
    {
        int H = x % 76543;
        for (int i = first[z][H]; i != -1; i = v[i].next)
            if (v[i].x == x && v[i].z == z)
                return 1;
        return 0;
    }
    _T &operator()(int z, _Tp x)
    {
        int H = x % 76543;
        for (int i = first[z][H]; i != -1; i = v[i].next)
            if (v[i].x == x && v[i].z == z)
                return v[i].ans;
        v[p].x = x;
        v[p].z = z;
        v[p].next = first[z][H];
        first[z][H] = p++;
        return v[p - 1].ans = 0;
    }
    void clear()
    {
        memset (first, -1, sizeof (first));
        // for (int i = 0; i <= 100; i++) Hp[i].p = 0;
        p = 0;
    }
    Hash_Table()
    {
        clear();
    }
};
Hash_Table<long long, int> F[2];
// map<long long, int> F[2][105];
long long c[15][15];
long long pow51[15];
int Get(long long S, int x)
{
    return (S / pow51[x - 1]) % 51;
}
long long Cs[105];
void DP(int n, int m, long long K)
{
    c[1][1] = K;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            c[i][j + 1] += c[i][j] / 2, c[i + 1][j] += c[i][j] / 2, c[i][j] &= 1;
    pow51[0] = 1;
    for (int i = 1; i <= 11; i++) pow51[i] = pow51[i - 1] * 51;
    F[0](0, 0) = 1;
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            now ^= 1;
            F[now].clear();
            for (int k = 0; k < F[now ^ 1].p; k++)
            {
                long long S = F[now ^ 1].v[k].x;
                int L = Get(S, j), U = Get(S, j + 1), x = F[now ^ 1].v[k].z;
                S -= L * pow51[j - 1] + U * pow51[j];
                int Sum = L + U + c[i][j], w1 = Sum / 2, w2 = Sum - w1;
                if (i < n)
                {
                    if (j < m)
                    {
                        (F[now](x, S + w1 * pow51[j - 1] + w2 * pow51[j]) += F[now ^ 1].v[k].ans) %= MOD;
                        (F[now](x, S + w1 * pow51[j] + w2 * pow51[j - 1]) += F[now ^ 1].v[k].ans) %= MOD;
                    }
                    else
                    {
                        (F[now](x + w1 * a[i], S + w2 * pow51[j - 1]) += F[now ^ 1].v[k].ans) %= MOD;
                        (F[now](x + w2 * a[i], S + w1 * pow51[j - 1]) += F[now ^ 1].v[k].ans) %= MOD;
                    }
                }
                else
                {
                    if (j < m)
                    {
                        (F[now](x + w1 * b[j], S + w2 * pow51[j]) += F[now ^ 1].v[k].ans) %= MOD;
                        (F[now](x + w2 * b[j], S + w1 * pow51[j]) += F[now ^ 1].v[k].ans) %= MOD;
                    }
                    else
                    {
                        (F[now](x + w1 * a[i] + w2 * b[j], S) += F[now ^ 1].v[k].ans) %= MOD;
                        (F[now](x + w2 * a[i] + w1 * b[j], S) += F[now ^ 1].v[k].ans) %= MOD;
                    }
                }
            }
        }
        for (int k = 0; k < F[now].p; k++)
            F[now].v[k].x *= 51;
    }
    for (int i = 0; i < F[now].p; i++)
        (Cs[F[now].v[i].z] += F[now].v[i].ans) %= MOD;
}
long long died = 0;
int main()
{
    int n = read(), m = read();
    long long K = read();
    for (int i = 1; i <= n; i++) scanf ("%1d", a + i);
    for (int i = 1; i <= m; i++) scanf ("%1d", b + i);
    DP(n, m, K);
    for (int i = 1; i <= n; i++) died += a[i] * c[i][m + 1];
    for (int i = 1; i <= m; i++) died += b[i] * c[n + 1][i];
    int Q = read();
    for (int i = 1; i <= n * m; i++)
        (Cs[i] += Cs[i - 1]) %= MOD;
    while (Q--)
    {
        long long l = read(), r = read();
        l -= died, r -= died;
        if (r < 0) printf ("0\n");
        else if (l < 0) printf ("%lld\n", Cs[min(r, 1ll * n * m)]);
        else printf ("%lld\n", (Cs[min(r, 1ll * n * m)] - Cs[min(l - 1, 1ll * n * m)] + MOD) % MOD);
    }
    // while (1);
}