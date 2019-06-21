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
const int MOD = 1e9 + 7;
struct Hash_Table
{
    struct edge
    {
        int a, b, next;
        long long ans;
    }v[100005];
    int first[76545], p;
    long long &operator()(int a, int b)
    {
        int H = (a % 7717) * (b % 9991) % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].a == a && v[i].b == b)
                return v[i].ans;
        v[p].a = a, v[p].b = b;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].ans = 0;
    }
    long long &operator[](int x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].a == x)
                return v[i].ans;
        v[p].a = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].ans = 0;
    }
    bool count(int a, int b)
    {
        int H = (a % 7717) * (b % 9991) % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].a == a && v[i].b == b)
                return 1;
        return 0;
    }
    bool count(int a)
    {
        int H = a % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].a == a)
                return 1;
        return 0;
    }
    void clear()
    {
        memset (first, -1, sizeof (first));
        p = 0;
    }
}s, Hash;
const int MAXN = 1e6;
int prime[MAXN + 2], from[MAXN + 2], cnt, pr[MAXN + 2];
long long phi[MAXN + 2], Sum[MAXN + 2];
bool isnprime[MAXN + 2];
void Get_phi()
{
    isnprime[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, phi[i] = i - 1, from[i] = 1, pr[i] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            from[i * prime[j]] = i;
            pr[i * prime[j]] = prime[j];
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    for (int i = 1; i <= MAXN; i++)
        Sum[i] = (Sum[i - 1] + phi[i]) % MOD;
}
long long Phi(int x)
{
    if (x <= MAXN) return Sum[x];
    if (Hash.count(x)) return Hash[x];
    long long ans = (1ll * x * (x + 1) / 2) % MOD;
    int nxt = 1;
    for (int i = 2; i <= x; i = nxt + 1)
    {
        nxt = x / (x / i);
        ans = ((ans - (nxt - i + 1) * Phi(x / i) % MOD) % MOD + MOD) % MOD;
    }
    return Hash[x] = ans;
}
int tmp[100005];
long long S(int n, int m)
{
    if (!m) return 0;
    if (n == 1) return Phi(m);
    if (m == 1) return phi[n];
    if (s.count(n, m)) return s(n, m);
    long long ans = (S(n / pr[n], m) * (pr[n] - 1) % MOD + S(n, m / pr[n])) % MOD;
    // printf ("%lld\n", ans);
    return ans;
}
int main()
{
    Hash.clear();
    s.clear();
    int n = read(), m = read();
    Get_phi();
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int tmn = i;
        int w = 1, y = 1, num = 0;
        while (tmn > 1)
        {
            int x = tmn / from[tmn];
            w *= x, tmn = from[tmn];
            tmp[++num] = x;
            while (tmn % x == 0) tmn /= x, y *= x;
        }
        long long tmp = S(w, m);
        ans = (ans + y * (s(w, m) = tmp) % MOD) % MOD;
    }
    printf ("%lld\n", ans);
}
