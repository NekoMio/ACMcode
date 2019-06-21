#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template<typename _T>
// #define int unsigned int 
struct Read
{
    _T operator()()
    {
        _T x=0,f=1;char ch=getchar();
        while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
        while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
        return x*f;
    }
};
Read<long long> read;
const int MAXN = 5e6;
int prime[MAXN + 2], mu[MAXN + 2], Summu[MAXN + 2], g[MAXN + 2], d[MAXN + 2], t[MAXN + 2], e[MAXN + 2], phi[MAXN + 2], Sum[MAXN + 2], cnt, k;
bool isnprime[MAXN + 2];
void Get_G()
{
    isnprime[1] = 1;
    phi[1] = 1;
    mu[1] = 1;
    g[1] = k;
    d[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i])
        {
            prime[++cnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            g[i] = -k;
            d[i] = -1;
            t[i] = 0;
            e[i] = 0;
        }
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            int z = i * prime[j];
            isnprime[z] = 1;
            d[z] = -d[i];
            if (i % prime[j] == 0)
            {
                phi[z] = phi[i] * prime[j];
                e[z] = e[i] + 1;
                if (e[z] <= t[i] || e[z] > k)
                {
                    g[z] = -g[i];
                    t[z] = t[i];
                }
                else
                {
                    t[z] = e[z];
                    g[z] = -(g[i] - d[i]);
                }
                mu[z] = 0;
                break;
            }
            phi[z] = phi[i] * (prime[j] - 1);
            e[z] = 0;
            t[z] = t[i];
            mu[z] = -mu[i];
            g[z] = -g[i];
        }
    }
    // for (int i = 1; i <= 100; i++) printf ("%d %d\n", i, phi[i]);
    for (int i = 1; i <= MAXN; i++)
        phi[i] += phi[i - 1];
    for (int i = 1; i <= MAXN; i++)
        g[i] += g[i - 1];
    for (int i = 1; i <= MAXN; i++)
        Sum[i] = Sum[i - 1] + d[i];
}
const int MAXM = 1e7;
struct Hash_Table
{
    struct edge
    {
        int ans, next;
        long long x;
    }v[MAXM];
    signed first[76545], p;
    Hash_Table()
    {
        memset(first, -1, sizeof (first));
        p = 0;
    }
    int &operator[](const long long &x)
    {
        int H = x % 76543;
        for (signed i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return v[i].ans;
        v[p].x = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].ans = 0;
    }
    bool count(const long long &x)
    {
        int H = x % 76543;
        for (signed i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return 1;
        return 0;
    }
}Hash, PHI, AA;
long long pow(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a;
        b >>= 1;
        a = a * a;
    }
    return ans;
}
int A(long long n)
{
    if (n <= MAXN) return Sum[n];
    if (AA.count(n)) return AA[n];
    long long nxt;
    int ans = sqrt(n) + 0.0001;
    for (long long i = 2; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = ans - (nxt - i + 1) * A(n / i);
    }
    return AA[n] = ans;
}
int G(long long n)
{
    if (n <= MAXN) return g[n];
    int ans = 0;
    for (int s = 1; s <= k; s++)
    {
        int H = pow(n, 1.0 / (s + 1)) + 0.0001;
        for (int i = 1; i <= H; i++) if(pow(i, s + 1))
        {
            ans = (ans + pow(d[i], s + 1) * mu[i] * A(n / pow(i, s + 1)));
        }
    }
    return ans;
}
int Phi(long long n)
{
    if (n <= MAXN) return phi[n];
    if (PHI.count(n)) return PHI[n];
    int ans = (n * (n + 1)) >> 1;
    long long nxt;
    for (long long i = 2; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = ans - (nxt - i + 1) * Phi(n / i);
    }
    return PHI[n] = ans;
}
signed main()
{
    // freopen ("2.txt", "w", stdout);
    long long n = read();
    k = read();
    Get_G();
    // for (int i = 1; i <= 100; i++) printf ("%d %d\n", i, g[i]);
    long long nxt = 0;
    int ans = 0;
    for (long long i = 1; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = ans + (G(nxt) - G(i - 1)) * (2 * Phi(n / i) - 1);
        // printf ("%lld\n", i);
    }
    printf ("%d\n", (ans % (1 << 30) + (1 << 30)) % (1 << 30));
    // while (1);
}
