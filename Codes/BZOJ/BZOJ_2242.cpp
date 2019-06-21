#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int MOD;
int pow_mod(int a, int b)
{
    int ans = 1;
    a %= MOD;
    while (b) 
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int query(int y, int z, int p)
{
    y %= p, z %= p;
    return z * pow_mod(y, p - 2) % MOD;
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
        return v[p - 1].ans = 0;
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
        memset (first, -1, sizeof (first));
        p = 0;
    }
}Hash;
int BSGS(int a, int b, int c)
{
    a %= c;
    b %= c;
    if (a == 0)
    {
        return b == 0 ? 1 : -1;
    }
    Hash.clear();
    int m = floor(sqrt(c)) + 1;
    for (int i = 0; i <= m; i++)
    {
        if (!Hash.count(b)) Hash[b] = i;
        b = b * a % c;
    }
    int s = pow_mod(a, m);
    int d = 1;
    for (int i = 1; i <= m; i++)
    {
        d = d * s % c;
        if (Hash.count(d)) return i * m - Hash[d];
    }
    return -1;
}
signed main()
{
    int t = read(), k = read();
    if (k == 1)
    {
        while (t--)
        {
            int y = read(), z = read();
            MOD = read();
            printf ("%lld\n", pow_mod(y, z));
        }
    }
    else if (k == 2)
    {
        while (t--)
        {
            int y = read(), z = read();
            MOD = read();
            if ((y % MOD) == 0 && (z % MOD) != 0) printf ("Orz, I cannot find x!\n");
            else printf ("%lld\n", query(y, z, MOD));
        }
    }
    else
    {
        while (t--)
        {
            int y = read(), z = read();
            MOD = read();
            int ans = BSGS(y, z, MOD);
            if (ans == -1) printf ("Orz, I cannot find x!\n");
            else printf ("%lld\n", ans);
        }
    }
}