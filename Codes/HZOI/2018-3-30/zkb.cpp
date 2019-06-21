#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 200005;
long double Sum[MAXN], pos[10];
int a[MAXN];
bool cmp1(const int &x, const int &y)
{
    return x < y;
}
bool cmp2(const int &x, const int &y)
{
    return x > y;
}
int main()
{
    freopen ("1.in", "r", stdin);
    freopen ("1.ans", "w", stdout);
    int n = read(), m = read();
    for (int i = 1; i <= 9; i++) pos[i] = log10l(i);
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= n; i++)
        Sum[i] = Sum[i - 1] + log10l(a[i]);
    bool flag = 0;
    while (m--)
    {
        int op = read();
        if (op == 1)
        {
            int l = read(), r = read(), t = read();
            if (t) sort(a + l, a + r + 1, cmp1);
            else   sort(a + l, a + r + 1, cmp2);
            flag = 1;
			if (n > 1000) return 0;
        }
        else if (op == 2)
        {
            int l = read(), r = read();
            if (flag)
            {
                long double ans = 0;
                for (int i = l; i <= r; i++)
                    ans += log10l(a[i]);
                ans = ans - floor(ans);
                int id = 0;
                for (int i = 1; i <= 9; i++)
                    if (ans - pos[i] >= 1e-9)
                        id = i;
                printf ("%d\n", id);
            }
            else
            {
                long double ans = Sum[r] - Sum[l - 1];
                ans = ans - floor(ans);
                int id = 0;
                for (int i = 1; i <= 9; i++)
                    if (ans - pos[i] >= 1e-9)
                        id = i;
                printf ("%d\n", id);
            }
        }
        else if (op == 3)
        {
            printf ("%d\n", a[read()]);
        }
    }
}