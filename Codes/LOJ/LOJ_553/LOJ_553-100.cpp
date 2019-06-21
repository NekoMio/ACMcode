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
inline void gmin(int &a, int b) { if (a > b) a = b; }
const int MAXN = 100005;
int M;
struct data
{
    int v, l;
    data(int _v = 0, int _l = 0) : v(_v), l(_l) {}
    data operator + (const data &a) const 
    {
        data c(v + a.v, l | a.l);
        for (int i = M; i >= 0; i--)
            if (l & a.l & (1 << i))
            {
                c.l |= ((1 << (i + 1)) - 1);
                break;
            }
        return c;
    }
    bool operator < (const data &a) const 
    {
        return v < a.v;
    }
}a[MAXN], s[MAXN], t[MAXN], tmp[MAXN];
int cnt, len;
int Calc(int x)
{
    for (int i = 1; i <= cnt; i++)
        if (s[i].l >= x)
            return s[i].v;
    return -1;
}
int main()
{
    // freopen ("1.out", "w", stdout);
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i].v = read(), a[i].l = read();
    for (M = 31; M && (1 << (M - 1)) >= m; M--);
    s[++cnt] = data(0, 0);
    tmp[0] = data(0, -1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= cnt; j++) 
            t[j] = s[j] + a[i];
        len = 0;
        int j = 0, k = 0, l;
        while (j < cnt || k < cnt)
        {
            data tp = j >= cnt ? t[++k] : (k >= cnt ? s[++j] : s[j + 1] < t[k + 1] ? s[++j] : t[++k]);
            for (l = 1; l <= len; l++)
                if (tmp[l].l >= tp.l)
                    break;
            if (l == len + 1)
                tmp[++len] = tp;
        }
        for (int j = 1; j <= len; j++)
            s[j] = tmp[j];
        cnt = len;
    }
    int q = read();
    while (q--)
    {
        printf ("%d\n", Calc(read()));
    }
}