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
const int MAXN = 100005 << 2;
double Max[MAXN];
int ans[MAXN];
int Calc(int l, int r, int rt, double val)
{
    if (l == r) return Max[rt] > val;
    int m = l + r >> 1;
    if (Max[rt << 1] <= val) return Calc(m + 1, r, rt << 1 | 1, val);
    return ans[rt] - ans[rt << 1] + Calc(l, m, rt << 1, val);
}
void Update(int x, double c, int l, int r, int rt)
{
    if (l == r)
    {
        ans[rt] = 1;
        Max[rt] = c;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) Update(x, c, l, m, rt << 1);
    else Update(x, c, m + 1, r, rt << 1 | 1);
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
    ans[rt] = ans[rt << 1] + Calc(m + 1, r, rt << 1 | 1, Max[rt << 1]);
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        int x = read(), y = read();
        Update(x, (double)y / x, 1, n, 1);
        printf ("%d\n", ans[1]);
    }
}