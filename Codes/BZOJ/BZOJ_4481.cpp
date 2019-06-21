#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
}v[500005];
int first[500005], p;
void add(int a, int b)
{
    v[p].next = first[a];
    v[p].END = b;
    first[a] = p++;
}
double P;
int n, m;
int tmp[500005];
double Sum[500005];
#define lowbit(_) ((_) & (-_))
void add(int a, double c)
{
    for (int i = a; i <= n; i += lowbit(i))
        Sum[i] += c;
}
double Query(int a)
{
    double ans = 0;
    for (int i = a; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
double pow_db(double a, int b)
{
    double ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a;
        b >>= 1;
        a = a * a;
    }
    return ans;
}
int main()
{
    n = read(), m = read();
    scanf ("%lf", &P);
    int a, b;
    memset(first, -1, sizeof (first));
    for (int i = 1; i <= m; i++)
    {
        a = read(), b = read();
        add(a, b);
    }
    double ans = 0;
    for (int i = n; i >= 1; i--)
    {
        int cnt = 0;
        for (int j = first[i]; j != -1; j = v[j].next) tmp[++cnt] = v[j].END;
        if (cnt == 0) continue;
        sort(tmp + 1, tmp + cnt + 1);
        for (int j = 1; j <= cnt; j++)
            ans += pow_db((1 - P), j - 1) * P / (1 - pow_db(1 - P, cnt)) * Query(tmp[j] - 1);
        for (int j = 1; j <= cnt; j++)
            add(tmp[j], pow_db((1 - P), j - 1) * P / (1 - pow_db(1 - P, cnt)));
    }
    printf ("%.2f", ans);
}
