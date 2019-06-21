// #pragma GCC optimize("O2")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
int w[MAXN << 1];
struct data
{
    int id;
    long long v;
    data(int a = 0, int b = 0): id(a), v(b) {}
    bool operator < (const data &b) const
    {
        return v == b.v ? w[id] < w[b.id] : v < b.v;
    }
};
struct heap
{
    data a[MAXN];
    int x;
    heap() { x = 0; }
    inline void push(const data &b)
    {
        a[++x] = b;
        int j = x;
        int i;
        while (j > 1)
        {
            i = j >> 1;
            if (a[j] < a[i]){ swap(a[i], a[j]); j = i; }
            else break;
        }
    }
    inline data pop()
    {
        data y = a[1];
        a[1] = a[x--];
        int i = 1;
        while ((i << 1) <= x)
        {
            int j = i << 1;
            if (j + 1 <= x && a[j + 1] < a[j]) j++;
            if (a[j] < a[i])
            {
                swap(a[j], a[i]);
                i = j;
            }
            else break;
        }
        return y;
    }
    inline bool empty() { return x == 0; }
    inline int size() { return x; }
}Q1, Q2;
long long a[MAXN * 10], b[MAXN * 10];
int main()
{
    int l = read(), n = read(), m = read();
    for (int i = 1; i <= n; i++) w[i] = read();
    for (int i = 1; i <= m; i++) w[i + n] = read();
    for (int i = 1; i <= n; i++) Q1.push(data(i, w[i]));
    for (int i = 1; i <= m; i++) Q2.push(data(i + n, w[i + n]));
    for (int i = 1; i <= l; i++)
    {
        data c = Q1.pop();
        a[i] = c.v;
        c.v += w[c.id]; Q1.push(c);
    }
    for (int i = 1; i <= l; i++)
    {
        data c = Q2.pop();
        b[i] = c.v;
        c.v += w[c.id]; Q2.push(c);
    }
    long long ans = 0;
    for (int i = 1; i <= l; i++)
        ans = max(ans, a[i] + b[l - i + 1]);
    printf ("%lld\n", ans);
    // while (1);
}