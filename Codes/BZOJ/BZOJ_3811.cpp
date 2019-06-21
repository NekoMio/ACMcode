#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
long long a[MAXN], b[65];
int main()
{
    int n = read(), k = read();
    if (k == 1)
    {
        unsigned long long ans = 0, tmp;
        for (int i = 1; i <= n; i++)
        {
            scanf("%llu", &tmp);
            ans = ans | tmp;
        }
        printf ("%llu%s", ans >> 1, ans & 1 ? ".5\n": "\n");
    }
    else if (k == 2)
    {
        long long ans = 0, s = 0;
        for (int i = 1; i <= n; i++)
            a[i] = read(), s |= a[i];
        int res = 0;
        for (int i = 0; i <= 32; i++)
        {
            for (int j = 0; j <= 32; j++)
            {
                if (!(s >> i & 1) || !(s >> j & 1)) continue;
                bool f = 0;
                for (int k = 1; k <= n; k++)
                {
                    if ((a[k] >> i & 1) != (a[k] >> j & 1))
                    {
                        f = 1;
                        break;
                    }
                }
                if (i + j - 1 - f < 0) res++;
                else ans += (1ll << (i + j - 1 - f));
            }
        }
        ans += res >> 1;
        printf ("%lld%s", ans, res & 1 ? ".5\n": "\n");
        // while (1);
    }
    else if (k >= 3)
    {
        for (int i = 1; i <= n; i++) a[i] = read();
        vector<long long> vc;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 63; j >= 0; j--)
            {
                if (a[i] >> j & 1)
                {
                    if (b[j]) a[i] ^= b[j];
                    else
                    {
                        b[j] = a[i];
                        vc.push_back(a[i]);
                        break;
                    }
                }
            }
        }
        int All = vc.size();
        long long ans = 0, res = 0;
        for (int i = 0; i <= (1 << All) - 1; i++)
        {
            long long val = 0;
            for (int j = 0; j < All; j++) if (i >> j & 1) val ^= vc[j];
            long long A = 0, B = 1;
            for (int j = 0; j < k; j++)
            {
                A *= val, B *= val;
                A += B >> All, B &= (1 << All) - 1;
            }
            ans += A, res += B;
            ans += res >> All, res &= (1 << All) - 1;
        }
        printf ("%lld%s", ans, res ? ".5\n": "\n");
    }
}