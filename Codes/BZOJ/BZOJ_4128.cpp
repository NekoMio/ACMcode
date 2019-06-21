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
int MOD;
unsigned long long base = 31;
struct Hash_Table
{
    struct edge
    {
        int next, x, ans;
    }v[100005];
    int first[7718], p;
    int &operator[](unsigned int x)
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
    bool count(unsigned int x)
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
struct Matrix
{
    int n;
    int a[75][75];
    unsigned int hash;
    Matrix()
    {
        memset (a, 0, sizeof (a));
        n = 0;
        hash = 0;
    }
    void init()
    {
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }
    int *operator[](int x)
    {
        return a[x];
    }
    const int *operator[](int x) const
    {
        return a[x];
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix ans;
        ans.n = n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % MOD;
        return ans;
    }
    Matrix operator ^ (int b)
    {
        Matrix ans, a = *this;
        ans.n = n;
        ans.init();
        while (b)
        {
            if (b & 1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
    void read()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = ::read();
    }
    unsigned int To_Hash()
    {
        if (hash) return hash;
        unsigned int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                ans = ans * base + a[i][j];
        return hash = ans;
    }
}A, B;
signed main()
{
    // freopen ("1.txt", "r", stdin);
    A.n = B.n = read(), MOD = read();
    A.read();
    B.read();
    Hash.clear();
    int m = floor(sqrt(MOD)) + 1;
    for (int i = 0; i <= m; i++)
    {
        if (!Hash.count(B.To_Hash()))
            Hash[B.To_Hash()] = i;
        B = B * A;
    }
    Matrix s = A ^ m, d;
    d.n = A.n;
    d.init();
    for (int i = 1; i <= m; i++)
    {
        d = d * s;
        if (Hash.count(d.To_Hash())) 
            return printf ("%lld\n", i * m - Hash[d.To_Hash()]), 0;
    }
    printf ("-1");
}