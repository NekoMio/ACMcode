#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int pow_mod(int a, int b, int c)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % c;
        b >>= 1;
        a = a * a % c;
    }
    return ans;
}
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
struct Hash_Table
{
    struct edge
    {
        int next, x, ans;
    }v[100005];
    int first[7718], p;
    int &operator[](int x)
    {
        int H = x % 7717;
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
        int H = x % 7717;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return 1;
        return 0;
    }
    void clear()
    {
        memset (first, -1, sizeof (first));
        p = 0;
    }
}Hash;
int TMP[100005];
int Get_G(int p, int phi)
{
    int num = 0;
    for (int i = 2; i * i <= phi; i++)
    {
        if (phi % i == 0)
            TMP[++num] = i;
        if (i * i != phi) TMP[++num] = phi / i;
    }
    for (int g = 2; g < p; g++)
    {
        bool flag = 0;
        for (int i = 1; i <= num; i++)
            if (pow_mod(g, TMP[i], p) == 1)
                flag = 1;
        if (!flag) return g;
    }
}
int BSGS(int a, int b, int c)
{
    Hash.clear();
    int m = floor(sqrt(c)) + 1;
    for (int i = 0; i <= m; i++)
    {
        if (!Hash.count(b)) Hash[b] = i;
        b = b * a % c;
    }
    int s = pow_mod(a, m, c);
    int d = 1;
    for (int i = 1; i <= m; i++)
    {
        d = d * s % c;
        if (Hash.count(d)) return i * m - Hash[d];
    }
}
int Calc(int a, int b, int p, int d)
{
    int p_d = pow_mod(p, d, 0x3f3f3f3f3f3f3f3fll);
    b %= p_d;
    if (b == 0) 
        return pow_mod(p, d - ((d - 1) / a + 1), 0x3f3f3f3f3f3f3f3fll);
    int tmp = 0;
    while (b % p == 0) b /= p, tmp++;
    if (tmp % a) return 0;
    d -= tmp;
    int phi = p_d - p_d / p;
    int g = Get_G(p_d, phi);
    int ind = BSGS(g, b, p_d);
    int GCD = gcd(a, phi);
    if (ind % GCD) return 0;
    return GCD * pow_mod(p, tmp - tmp / a, 0x3f3f3f3f3f3f3f3fll);
}
signed main()
{
    int T = read();
    while (T--)
    {
        int a = read(), b = read(), c = read();
        int ans = 1;
        c = c << 1 | 1;
        for (int i = 2; i * i <= c && ans; i++)
            if (c % i == 0)
            {
                int tmp = 0;
                while (c % i == 0)
                    c /= i, tmp++;
                ans *= Calc(a, b, i, tmp);
            }
        if (ans && c != 1) ans *= Calc(a, b, c, 1);
        printf ("%lld\n", ans);
    }
}