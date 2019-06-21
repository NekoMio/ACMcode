#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
struct Martix
{
    double a[1005];
    int n;
    Martix(int x)
    {
        n = x;
        memset(a, 0, sizeof(a));
    }
    Martix operator*(const Martix &b)
    {
        Martix ans(n);
        ans.a[1] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int k = 1; k <= n; k++)
            {
                int t=(i-k+n+1)%n;
                if(!t) t+=n;
                ans.a[i] += a[k] * b.a[t];
            }
        }
        return ans;
    }
    Martix operator^(const int x)
    {
        Martix a = *this, ans(n);
        int k = x;
        ans.a[1] = 1;
        while (k)
        {
            if (k & 1)
                ans = ans * a;
            k >>= 1;
            a = a * a;
        }
        return ans;
    }
};
int a[1005];
double ans[1005];
int main(int argc, char const *argv[])
{
    int n, m, k;
    scanf("%d%d%d",&n,&m,&k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    Martix K(n);
    K.a[1] = (double)1 - ((double)1 / m);
    K.a[2] = ((double)1 / m);
    K=K^k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int t=(i+j-1)%n;
            if(!t) t+=n;
            ans[t] += K.a[i] * a[j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%.3lf\n", ans[i]);
    }
    //while(1);
    return 0;
}
