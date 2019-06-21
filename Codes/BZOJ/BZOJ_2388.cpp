#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long
const int MAXN = 1e5 + 5;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int INF = 0x3f3f3f3f3f3f3f3f;
int in[MAXN];
int a[MAXN], block;
int L[MAXN], R[MAXN], m;
struct data
{
    int a[350], cnt;
    int &operator[](int x){return a[x];}
}v[350];
int f[350], KD[350], Add[350];
int st[MAXN];
double K(int x, int y) 
{
    return ((double)a[x] - a[y]) / (x - y);
}
void Build(int x)
{
    int top = 0;
    for (int i = L[x]; i <= R[x]; i++)
    {
        while (top > 1 && K(i, st[top - 1]) >= K(st[top], st[top - 1])) top--;
        st[++top] = i;
    }
    for (int i = 1; i <= top; i++) v[x][i] = st[i];
    v[x].cnt = top, v[x][0] = v[x][top + 1] = 0;
}
void Pushdown(int x)
{
    int now = f[x];
    for (int i = L[x]; i <= R[x]; i++) a[i] += now + Add[x], now += KD[x];
    f[x] = KD[x] = Add[x] = 0;
}
void add(int l, int r, int c)
{
    int now = 0;
    if (in[l] == in[r])
    {
        Pushdown(in[l]);
        for (int i = l; i <= r; i++) now += c, a[i] += now;
        for (int i = r + 1; i <= R[in[l]]; i++) a[i] += now;
        Build(in[l]);
        for (int i = in[l] + 1; i <= m; i++) Add[i] += now;
    }
    else
    {
        Pushdown(in[l]);
        for (int i = l; i <= R[in[l]]; i++) now += c, a[i] += now;
        Build(in[l]);
        for (int i = in[l] + 1; i < in[r]; i++)
        {
            now += c;
            f[i] += now;
            KD[i] += c;
            now += c * (block - 1);
        }
        Pushdown(in[r]);
        for (int i = L[in[r]]; i <= r; i++) now += c, a[i] += now;
        for (int i = r + 1; i <= R[in[r]]; i++) a[i] += now;
        Build(in[r]);
        for (int i = in[r] + 1; i <= m; i++) Add[i] += now;
    }
}
int Calc(int x)
{
    if (x == 0) return -INF;
    return a[x] + f[in[x]] + Add[in[x]] + KD[in[x]] * (x - L[in[x]]);
}
int Search(int x)
{
    int l = 1, r = v[x].cnt;
    while (l <= r)
    {
        int mid = l + r >> 1;
        int n1 = Calc(v[x][mid - 1]), n2 = Calc(v[x][mid]), n3 = Calc(v[x][mid + 1]);
        if (n1 < n2 && n2 < n3) l = mid + 1;
        else if (n1 > n2 && n2 > n3) r = mid - 1;
        else return n2;
    }
    return 0;
}
int Query(int l, int r)
{
    int ans = -INF;
    if (in[l] == in[r])
    {
        for (int i = l; i <= r; i++) ans = max(ans, Calc(i));
    }
    else
    {
        for (int i = l; i <= R[in[l]]; i++) ans = max(ans, Calc(i));
        for (int i = in[l] + 1; i < in[r]; i++) ans = max(ans, Search(i));
        for (int i = L[in[r]]; i <= r; i++) ans = max(ans, Calc(i));
    }
    return ans;
}
signed main()
{
    // freopen("travel1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read() + a[i - 1];
    block = sqrt(n);
    m = (n - 1) / block + 1;
    for (int i = 1; i <= n; i++) in[i] = (i - 1) / block + 1;
    for (int i = 1; i <= m; i++) L[i] = (i - 1) * block + 1, R[i] = i * block;
    for (int i = 1; i <= m; i++) Build(i);
    R[m] = n;
    int Q = read();
    while (Q--)
    {
        int op = read();
        if (op == 1)
        {
            int x = read(), y = read();
            printf ("%lld\n", Query(x, y));
        }
        else
        {
            int x = read(), y = read(), c = read();
            add(x, y, c);
        }
    }
}