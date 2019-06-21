#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
int MOD;
struct Matrix
{
    int n, m;
    long long a[4][4];
    Matrix(int n1, int m1)
    {
        n = n1, m = m1;
        memset(a, 0, sizeof(a));
    }
    void Init_Fibonacci()
    {
        a[1][1] = a[1][2] = a[2][1] = 1;
        n = 2, m = 2;
    }
    Matrix operator*(const Matrix &A)
    {
        Matrix ans(n, A.m);
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= m; k++)
                for (int j = 1; j <= A.m; j++)
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * A.a[k][j]) % MOD;
        //ans.a[i][k] = ans.a[i][k] % MOD;
        return ans;
    }
    Matrix operator^(const long long &b)
    {
        long long k = b;
        Matrix ans(n, m);
        for (int i = 1; i <= n; i++)
        {
            ans.a[i][i] = 1;
        }
        Matrix A = *this;
        while (k)
        {
            if (k & 1)
                ans = ans * A;
            k >>= 1;
            A = A * A;
        }
        return ans;
    }
    void print()
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%lld ", a[i][j] % MOD);
            printf("\n");
        }
        printf("\n");
    }
};
LL F[6000005];
LL vis[1000005];
bool have[1000005];
LL ExtGcd(LL a, LL b, LL &x, LL &y)
{
    int ret, tmp;
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    ret = ExtGcd(b, a % b, x, y);
    tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ret;
}
int INV[1000005];
int main()
{
    freopen("rabbit17.in", "r", stdin);
    freopen("rabbit.out", "w", stdout);
    LL n, k, p;
    scanf("%lld%lld%lld", &n, &k, &p);
    MOD = p;
    F[1] = F[2] = 1;
    //vis[1] = 1;
    for (int i = 3; i <= 6 * k; i++)
    {
        F[i] = (F[i - 1] + F[i - 2]) % k;
        vis[F[i]] = vis[F[i]] ? min(vis[F[i]], (LL)i) : i;
        if (F[i] == F[i - 1] && F[i] == 1)
            break;
    }
    LL h = 0, x = 1, h1;
    LL a, b, X;
    int ans = 0;
    Matrix AL(1, 3);
    AL.a[1][2] = AL.a[1][3] = 1;
    AL.a[1][1] = 0;
    //Matrix P(3, 3);
    // P.a[1][1] = P.a[1][2] = P.a[2][1] = P.a[3][3] = 1;
    Matrix store(3, 3);
    store.a[1][1] = store.a[2][2] = store.a[3][3] = 1;
    Matrix Mark(3, 3), Metastasis1(3, 3), Metastasis2(3, 3);
    Mark.a[1][1] = Mark.a[2][2] = Mark.a[3][3] = 1;
    Metastasis1.a[1][1] = Metastasis1.a[2][1] = Metastasis1.a[1][2] = Metastasis1.a[3][3] = 1;
    Metastasis2.a[1][1] = Metastasis2.a[2][2] = Metastasis2.a[3][3] = 1;
    Metastasis2.a[3][1] = -1;
    while (h <= n)
    {
        LL Gcd;
        if (!INV[x])
        {
            Gcd = ExtGcd(x, k, a, b);
            LL t = k / Gcd;
            a = (a % t + t) % t;
            if (Gcd == 1)
                INV[x] = a;
            else
                INV[x] = -1;
        }
        else
        {
            if (INV[x] == -1)
                Gcd = 2;
            else 
            {
                a = INV[x];
                Gcd = 1;
            }
               
        }
        if (Gcd != 1 || vis[a] == 0)
        {
            Matrix KKK = AL * store * Mark;
            Matrix Now = KKK * (Metastasis1 ^ (n - h));
            //Now.print();
            ans = Now.a[1][1];
            h = n + 1;
        }
        else
        {
            LL next = vis[a];
            if (h + next > n)
                break;
            if (h != 0)
            {
                Mark = Mark * (Metastasis1 ^ next) * Metastasis2;
                //Mark.print();
            }
            else
            {
                h1 = next;
                //((Metastasis1 ^ next)* Metastasis2).print();
                store = (Metastasis1 ^ next) * Metastasis2;
                //store.print();
            }
            x = (x * F[next - 1]) % k;
            printf("x=======%d\n",x);
            if(h == 0)
                X = x;
            h = next + h;
            if(h==next)continue;
            if (x == X)
            {
                LL T = h - h1;
                (AL * store * Mark).print();
                printf("=======T=%d\n",T);
                LL K = (n - h1) / T;
                Mark = Mark ^ K;
                memset(have, 0, sizeof(have));
                h = (LL)K * T + h1;
                //printf("==========\n");
            }
        }
        //printf("X ==== %d\n",X);
    }
    //printf("============");
    //printf("%d\n", ans);
    //store.print();
    //(store * Mark).print();
    //printf("\n%d\n",n - h);
    //(Metastasis1 ^ (n - h)).print();
    //(store * Mark * Metastasis1 ^ (n - h)).print();
    //Matrix PP = (AL * store * Mark * (Metastasis1 ^ (n - h)));
    //PP.print();
    if (!ans)
        ans = (AL * store * Mark * (Metastasis1 ^ (n - h))).a[1][1];

    printf("%d", (ans%p+p)%p);
    //while(1);
}
