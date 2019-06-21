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
const int MAXN = 305;
int C, n;
int Color[MAXN];
int Sum[MAXN];
#define lowbit(_) ((_) & (-_))
void add(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i))
    {
        if (Color[i] != C) Sum[i] = 0;
        Color[i] = C;
        Sum[i] += c;
    }
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
    {
        if (Color[i] == C)
            ans += Sum[i];
    }
    return ans;
}
int a[MAXN], b[MAXN];
int Calc()
{
    C++;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += Query(n) - Query(a[i]);
        add(a[i], 1);
    }
    return ans;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        b[i] = a[i] = read();
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    int Ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            swap(a[i], a[j]);
            Ans = min(Ans, Calc() + 1);
            swap(a[i], a[j]);
            
        }
    Ans = min(Ans, Calc());
    printf ("%d\n", Ans);
}