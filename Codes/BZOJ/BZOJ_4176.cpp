#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
// #define int long long
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 4e6;
const int MOD = 1000000007;
int prime[MAXN + 2], mu[MAXN + 2], cnt, Sum[MAXN + 2];
bool isnprime[MAXN + 2];
void Get_mu()
{
    isnprime[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            else
                mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= MAXN; i++)
        Sum[i] = (Sum[i - 1] + mu[i] + MOD) % MOD; 
}
struct Hash_Table
{
    struct data
    {
        int x, ans, next;
    }v[MAXN];
    int first[76545], p;
    Hash_Table()
    {
        memset(first, -1, sizeof(first));
        p = 1;
    }
    bool count(int x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x) return 1;
        return 0;
    }
    int &operator[](const int &x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x) return v[i].ans;
        v[p].x = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[first[H]].ans = 0;
    }
}Hash;

int Mu(int x)
{
    if (x < MAXN) return Sum[x];
    if (Hash.count(x)) return Hash[x];
    int ans = 1, nxt;
    for (int i = 2; i <= x; i = nxt + 1)
    {
        nxt = x / (x / i);
        ans = (ans - 1ll * (nxt - i + 1) * Mu(x / i) % MOD + MOD) % MOD;
    }
    return Hash[x] = ans;
}

int Get_F(int n)
{
    int ans = 0, nxt;
    for (int i = 1; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = (ans + 1ll * (nxt - i + 1) * (n / i) % MOD) % MOD;
    }
    return 1ll * ans * ans % MOD;
}

long long Calc(int n)
{
    int ans = 0, nxt;
    for (int i = 1; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        ans = (ans + 1ll * (Mu(nxt) - Mu(i - 1)) * Get_F(n / i) % MOD) % MOD;
    }
    return (ans + MOD) % MOD;
}

signed main()
{
    Get_mu();
    int n = read();
    printf ("%lld\n", Calc(n));
}