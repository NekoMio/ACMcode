#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
long long A[150005 << 3], B[150005 << 3];
int rev[150005 << 3], N, FU;
long long MOD = 1004535809;
long long INV;
long long pow_mod(long long a, long long b, long long P)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return ans;
}
void FFt(long long *a, int op)
{
    long long w, wn, t;
    for (int i = 0; i < N; i++)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (int k = 2; k <= N; k <<= 1)
    {
        wn = pow_mod(3, op == 1 ? (MOD - 1) / k: MOD - 1 - (MOD - 1) / k, MOD);
        for (int j = 0; j < N; j += k)
        {
            w = 1;
            for (int i = 0; i < (k >> 1); i++, w = w * wn % MOD)
            {
                t = a[i + j + (k >> 1)] * w % MOD;
                a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
                a[i + j] = (a[i + j] + t) % MOD;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            a[i] = a[i] * INV % MOD;
}
void FFt(const int *a, const int *b, int *res, int n)
{
    N = 1;
    while (N < n)
        N <<= 1;
    INV = pow_mod(N, MOD - 2, MOD);
    for (int i = 0; i < N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    for (int i = 0; i < N; i++)
        A[i] = a[i], B[i] = b[i];
    FFt(A, 1), FFt(B, 1);
    for (int i = 0; i < N; i++)
        A[i] = A[i] * B[i] % MOD;
    FFt(A, -1);
    for (int i = 0; i < N; i++)
        res[i] = A[i];
}
char s[150005 << 2];
struct BigNum
{
    int len;
    int a[1000005];
    void read()
    {
        scanf("%s", s);
        len = strlen(s);
        for (int i = len - 1, j = 0; i >= 0; i--, j++)
            a[j] = s[i] - '0';
    }
    BigNum operator*(const BigNum &b)
    {
        BigNum ans;
        ans.len = len + b.len - 1;
        FFt(a, b.a, ans.a, ans.len + 1);
        for (int i = 0; i <= ans.len + 2; i++)
        {
            if (ans.a[i] > 9)
            {
                ans.a[i + 1] += ans.a[i] / 10;
                ans.a[i] %= 10;
            }
        }
        while (ans.a[ans.len])
            ans.len++;
        return ans;
    }
    void print()
    {
        for (int i = len - 1; i >= 0; i--)
            printf("%d", a[i]);
        printf("\n");
    }
} a, b;
 
int main()
{
    freopen("bettermul.in","r",stdin);
    freopen("bettermul.out","w",stdout);
    a.read();
    b.read();
    (a * b).print();
    // while (1);
}