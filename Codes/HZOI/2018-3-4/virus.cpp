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
const int MAXN = 4e6 + 5;
const int MOD = 1005060097;
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
int Num(int x)
{
    int ans = 0;
    while (x) 
    {
        if (x & 1) ans++;
        x >>= 1;
    }
    return ans;
}
int N, Inv;
int rev[MAXN];
void Init(int n)
{
    N = 1;
    while (N < (n << 1)) N <<= 1;
    Inv = pow_mod(N, MOD - 2) % MOD;
    for (int i = 1; i <= N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
}
void FFt(int *a, int op)
{
    int w, wn, t;
    for (int i = 1; i <= N; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = pow_mod(5, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
        for (int j = 0; j < N; j += k)
        {
            w = 1;
            for (int i = 0; i < (k >> 1); i++, w = 1ll * w * wn % MOD)
            {
                t = 1ll * a[i + j + (k >> 1)] * w % MOD;
                a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
                a[i + j] = (a[i + j] + t) % MOD;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            a[i] = 1ll * a[i] * Inv % MOD;
}
int Data[MAXN << 2], Test[MAXN << 2], n;
char s[MAXN];
int main()
{
    // freopen ("virusb.in", "r", stdin);
    // freopen ("virusb.out", "w", stdout);
    int m = read(); n = read();
    scanf ("%s", s);
    for (int i = 0; i < n; i++) Data[i] = s[i];
    scanf ("%s", s);
    for (int i = 0; i < n; i++) Test[i] = s[i];
    for (int i = 0; i < n; i++) Data[i] -= '0', Test[i] -= '0';
    for (int i = n; i < 2 * n; i++) Data[i] = Data[i - n];
    // reverse(Data + n + 1, Data + 2 * n + 1);
    for (int i = 0; i < 2 * n; i++) if (Data[i] == 0) Data[i] = MOD - 1;
    reverse(Test, Test + n);
    for (int i = 0; i < n; i++) if (Test[i] == 0) Test[i] = MOD - 1;
    Init(2 * (n - 1));
    FFt(Data, 1), FFt(Test, 1);
    for (int i = 0; i < N; i++) Data[i] = 1ll * Data[i] * Test[i] % MOD;
    FFt(Data, -1);
    int N = (1 << m) - 1;
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= N; i++)
    {
        int x = Num(i);
        ans = min(ans, ((n + Data[i % n + n - 1]) % MOD) / 2 + 2 + x); // x2 = 1, x1 = 1;
        ans = min(ans, ((n - Data[i % n + n - 1] + MOD) % MOD) / 2 + 1 + x); // x2 = 1, x1 = 0;
        ans = min(ans, ((n + Data[2 * n - (i % n) - 1]) % MOD) / 2 + 1 + x); //x2 = 0, x1 = 1; 
        ans = min(ans, ((n - Data[2 * n - (i % n) - 1] + MOD) % MOD) / 2 + 0 + x); //x2 = 0, x1 = 0;
    }
    printf ("%d\n", ans);
}