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
const int MAXN = 300005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;
int n;
long long ans[MAXN], Num[MAXN];
struct SAM
{
    int cnt, last;
    int a[MAXN << 1][26], fa[MAXN << 1], Max[MAXN << 1];
    long long size[MAXN << 1], Num_Max[MAXN << 1][2], Num_Min[MAXN << 1][2];
    int buc[MAXN << 1], q[MAXN << 1];
    SAM()
    {
        last = ++cnt;
        for (int i = 0; i <= 2 * MAXN - 1; i++)
        {
            Num_Max[i][0] = Num_Max[i][1] = -INF;
            Num_Min[i][0] = Num_Min[i][1] = INF;
        }
    }
    void extend(int c, int v)
    {
        int p = last, np = last = ++cnt;
        Max[np] = Max[p] + 1;
        size[np] = 1;
        Num_Max[np][0] = v, Num_Min[np][0] = v;
        while (!a[p][c] && p) a[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else
        {
            int q = a[p][c];
            if (Max[q] == Max[p] + 1) fa[np] = q;
            else
            {
                int nq = ++cnt;
                Max[nq] = Max[p] + 1;
                memcpy(a[nq], a[q], sizeof(a[nq]));
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while (a[p][c] == q) a[p][c] = nq, p = fa[p];
            }
        }
    }
    void Push_Max(int p, long long x)
    {
        if (x > Num_Max[p][0])
        {
            Num_Max[p][1] = Num_Max[p][0];
            Num_Max[p][0] = x;
        }
        else if (x > Num_Max[p][1])
            Num_Max[p][1] = x;
    }
    void Push_Min(int p, long long x)
    {
        if (x < Num_Min[p][0])
        {
            Num_Min[p][1] = Num_Min[p][0];
            Num_Min[p][0] = x;
        }
        else if (x < Num_Min[p][1])
            Num_Min[p][1] = x;
    }
    void init()
    {
        for (int i = 1; i <= cnt; i++) buc[Max[i]]++;
        for (int i = 1; i <= cnt; i++) buc[i] += buc[i - 1];
        for (int i = 1; i <= cnt; i++) q[buc[Max[i]]--] = i;
    }
    void Query()
    {
        init();
        for (int i = 0; i <= n + 1; i++) ans[i] = -INF;
        for (int i = cnt; i >= 1; i--)
        {
            int now = q[i];
            if (size[now] > 1)
            {
                Num[Max[now]] += (size[now] - 1) * size[now] / 2;
                if (i != 1) Num[Max[fa[now]]] -= (size[now] - 1) * size[now] / 2;
                ans[Max[now]] = max(ans[Max[now]], max(Num_Max[now][0] * Num_Max[now][1], Num_Min[now][0] * Num_Min[now][1]));
            }
            if (i != 1)
            {
                size[fa[now]] += size[now];
                Push_Max(fa[now], Num_Max[now][0]);
                Push_Max(fa[now], Num_Max[now][1]);
                Push_Min(fa[now], Num_Min[now][0]);
                Push_Min(fa[now], Num_Min[now][1]);
            }
        }
        for (int i = n; i >= 0; i--) Num[i] += Num[i + 1];
        for (int i = n; i >= 0; i--) ans[i] = max(ans[i], ans[i + 1]);
        for (int i = n; i >= 0; i--) if (ans[i] == -INF) ans[i] = 0;
    }
}sam;
char s[MAXN];
int a[MAXN];
int main()
{
    freopen("savour.in","r",stdin);
	freopen("savour.out","w",stdout);
    n = read();
    scanf ("%s", s + 1);
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = n; i >= 1; i--)
        sam.extend(s[i] - 'a', a[i]);
    sam.Query();
    for (int i = 0; i < n; i++)
        printf ("%lld %lld\n", Num[i], ans[i]);
}