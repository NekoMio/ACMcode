#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
long long ans;
struct SAM
{
    int last, cnt;
    map<int, int> a[MAXN << 1];
    int fa[MAXN << 1], Max[MAXN << 1];
    SAM()
    {
        last = ++cnt;
    }
    void extend(int c)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[q] == Max[p] + 1) 
                fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                a[nq] = a[q];
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
        ans -= Max[fa[np]];
    }
}sam;
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        int c = read();
        ans += i;
        sam.extend(c);
        printf ("%lld\n", ans);
    }
    // while (1);
}