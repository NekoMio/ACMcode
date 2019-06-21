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
int pow_mod(int a, int b, int P)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return ans;
}
int trans(int a, int b, int t, int x, int p)
{
    return ((t - b * pow_mod(1 - a + p, p - 2, p) % p) % p + p) % p * pow_mod(((x - b * pow_mod(1 - a + p, p - 2, p) % p) + p) % p, p - 2, p) % p;
}
struct Hash_Table
{
    struct edge
    {
        int x, ans, next;
    }v[100005];
    int first[7718], p;
    int &operator[](const int &x)
    {
        int H = x % 7717;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return v[i].ans;
        v[p].x = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].ans = 0x3f3f3f3f;
    }
    bool count(const int &x)
    {
        int H = x % 7717;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return 1;
        return 0;
    }
    void clear()
    {
        memset (first, -1, sizeof(first));
        p = 0;
    }
}Hash;
int BSGS(int a, int b, int c)
{
    a %= c;
    b %= c;
    Hash.clear();
    int m = floor(sqrt(c)) + 1;
    for (int i = 0; i <= m; i++)
    {
        Hash[b] = min(Hash[b], i), b = b * a % c;
    }
    int s = pow_mod(a, m, c);
    int d = 1;
    for (int i = 1; i <= m; i++)
    {
        d = d * s % c;
        if (Hash.count(d)) return i * m - Hash[d] + 1;
    }
    return -1;
}
signed main()
{
    // freopen ("random0.in", "r", stdin);
    int T = read();
    while (T--)
    {
        int p = read(), a = read(), b = read(), x = read(), t = read();
        if (t == x) printf ("1\n");
        else if (a == 0)
            printf (b == t ? "2\n" : "-1\n");
        else if (a == 1)
        {
            printf (b == 0 ? "-1\n" : "%lld\n", (((t - x) % p + p) % p) * pow_mod(b, p - 2, p) % p + 1);
        }
        else printf ("%lld\n", BSGS(a, trans(a, b, t, x, p), p));
    }
}