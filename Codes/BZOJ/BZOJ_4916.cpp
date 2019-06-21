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
const int MAXN = 1e6;
int prime[MAXN + 2], phi[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
long long Inv2 = 500000004, Inv6 = 166666668;
void Get_fun()
{
    isnprime[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i <= MAXN; i++)
        phi[i] = (phi[i - 1] + 1ll * phi[i] * i % MOD) % MOD;
}
long long Sum(int b, int a)
{
    return ((1ll * b * (b + 1) % MOD * Inv2 % MOD - 1ll * a * (a + 1) % MOD * Inv2 % MOD) % MOD + MOD) % MOD;
}
struct Hash_Table
{
    struct edge
    {
        int x, next;
        long long ans;
    }v[MAXN];
    int first[76545], p;
    Hash_Table()
    {
        memset(first, -1, sizeof (first));
        p = 0;
    }
    long long &operator[](int x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return v[i].ans;
        v[p].x = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].ans = 0;
    }
    bool count(int x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return 1;
        return 0;
    }
}Hash;
long long Phi2(int n)
{
    if (n <= MAXN) return phi[n];
    if (Hash.count(n)) return Hash[n];
    long long ans = 1ll * n * (n + 1) % MOD * (2 * n % MOD + 1) % MOD * Inv6 % MOD;
    int nxt = 1;
    for (int i = 2; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = ((ans - Sum(nxt, i - 1) * Phi2(n / i) % MOD) % MOD + MOD) % MOD;
    }
    return Hash[n] = ans;
}
int main()
{
    Get_fun();
    int n = read();
    printf ("1\n");
    printf ("%lld\n", Phi2(n));   
    // while (1);
}