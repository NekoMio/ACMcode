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
struct Hash_Table
{
    struct edge
    {
        int next, x, ans;
    }v[100005];
    int first[76545], p;
    int &operator[](int x)
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
    void clear()
    {
        memset (first, -1, sizeof (first));
        p = 0;
    }
}Hash;
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int BSGS(int a, int b, int c, int d)
{
    Hash.clear();
    int m = floor(sqrt(c)) + 1;
    for (int i = 0; i <= m; i++)
    {
        // if (!Hash.count(b)) 
        Hash[b] = i;
        b = b * a % c;
    }
    int s = pow_mod(a, m, c);
    for (int i = 1; i <= m; i++)
    {
        d = d * s % c;
        if (Hash.count(d)) return i * m - Hash[d];
    }
    return -1;
}
int exBSGS(int a, int b, int c)
{
    b %= c;
    int s = 1;
    for (int i = !a; i <= 40; i++)
    {
        if (s == b) return i;
        s = s * a % c;
    }
    int cnt = 0, d = 1;
    for (int i; (i = gcd(a, c)) != 1; cnt++)
    {
        if (b % i) return -1;
        b /= i, c /= i;
        d = d * a / i % c;
    }
    int ret = BSGS(a, b, c, d);
    if (ret == -1) return -1;
    return ret + cnt;
}
signed main()
{
    // int T = read();
    while (1)
    {
        int a = read(), b = read(), c = read();
        if (a == 0 && b == 0 && c == 0) break;
        int ans = exBSGS(a, c, b);
        if (ans == -1) printf ("No Solution\n");
        else printf ("%lld\n", ans);
    }
}