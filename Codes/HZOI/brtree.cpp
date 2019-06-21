#include <cstdio>
#include <cstring>
int P;
class frac
{
  public:
    long long a, b;
    long long gcd(long long A, long long B)
    {
        return B == 0 ? A : gcd(B, A % B);
    }
    frac Update(frac s)
    {
        if (s.a == 0)
            return s;
        int GCD = s.gcd(s.a, s.b);
        return (frac){s.a / GCD, s.b / GCD};
    }
    frac operator*(const frac A)
    {
        return (frac){a * A.a % P, b * A.b % P};
    }
    frac operator*(const int A)
    {
        return (frac){a * A % P, b % P};
    }
};
frac ans[1000001];
// 0 b, 1 r
// 0 = ,1 b>r ,2,b<r
int main()
{
    //freopen("brtree.in", "r", stdin);
    //freopen("brtree.out", "w", stdout);
    int p, q, T;
    scanf("%d%d%d%d", &p, &q, &T, &P);
    p %= P;
    q %= P;
    frac B = (frac){q - p, q};
    frac R = (frac){p, q};
    frac BR = B * R * 2;
    frac BBRR = (frac){p * p + (q - p) * (q - p), q * q};
    BR = BR.Update(BR);
    BBRR = BBRR.Update(BBRR);
    ans[2] = BBRR;
    for (int i = 4; i <= 1000000; i += 2)
    {
        ans[i] = ans[i - 2] * BR;
    }
    int k = 0, r = 0;
    while (T--)
    {
        scanf("%d", &k);
        k -= r;
        //int Gcd = ans[k].gcd(ans[k].a, ans[k].b);
        r = 0;
        printf("%lld %lld\n", ans[k].a % P, ans[k].b % P);
        r = ans[k].a % P;
    }
}