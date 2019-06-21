#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double pi = acos(-1.);
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 30005;
struct Complex
{
    double x, y;
    Complex(double _x = 0, double _y = 0): x(_x), y(_y) {}
    Complex operator+(const Complex &a) { return Complex(x + a.x, y + a.y); }
    Complex operator-(const Complex &a) { return Complex(x - a.x, y - a.y); }
    Complex operator*(const Complex &a) { return Complex(x * a.x - y * a.y, x * a.y + a.x * y); }
    Complex operator*(const double  &a) { return Complex(x * a, y * a); }
}a[MAXN << 2];
int N, rev[MAXN << 2];
double Inv;
void FFT(Complex *A, int op)
{
    for (int i = 1; i < N; i++)
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    Complex w, wn, t;
    for (int k = 1; k < N; k <<= 1)
    {
        wn = Complex(cos(pi / k), op * sin(pi / k));
        for (int j = 0; j < N; j += (k << 1))
        {
            w = Complex(1, 0);
            for (int i = 0; i < k; i++, w = w * wn)
            {
                t = A[i + j + k] * w;
                A[i + j + k] = A[i + j] - t;
                A[i + j] = A[i + j] + t;
            }
        }
    }
    if (op == -1)
        for (int i = 0; i < N; i++)
            A[i] = A[i] * Inv;
}
struct edge
{
    int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int size[MAXN], Max[MAXN], Sum, root;
bool vis[MAXN];
int dis[MAXN], c[MAXN], M;
void Get_Root(int rt, int fa)
{
    size[rt] = 1;
    Max[rt] = 0;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END]) continue;
        Get_Root(v[i].END, rt);
        size[rt] += size[v[i].END];
        Max[rt] = max(Max[rt], size[v[i].END]);
    }
    Max[rt] = max(Max[rt], Sum - size[rt]);
    if (Max[rt] < Max[root]) root = rt;
}
void dfs(int rt, int fa)
{
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (v[i].END == fa || vis[v[i].END]) continue;
        dis[v[i].END] = dis[rt] + 1;
        c[dis[v[i].END]] ++;
        M = max(dis[v[i].END], M);
        dfs(v[i].END, rt);
    }
}
int g[MAXN << 2];
void Calc(int M, int type)
{
    N = 1;
    while (N <= (M * 2)) N <<= 1;
    for (int i = 1; i <= N; i++)
        if (i & 1)
            rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
    Inv = 1. / N;
    for (int i = 0; i <= M; i++) a[i] = Complex(c[i], 0), c[i] = 0;
    for (int i = M + 1; i < N; i++) a[i] = Complex(0, 0);
    FFT(a, 1);
    for (int i = 0; i < N; i++) a[i] = a[i] * a[i];
    FFT(a, -1);
    for (int i = 1; i <= 2 * M + 1; i++) g[i] += type * round(a[i - 1].x);
}
void DFS(int rt)
{
    vis[rt] = 1;
    dis[rt] = 0, c[0]++, M = 0, dfs(rt, 0);
    Calc(M, 1);
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END]) continue;
        dis[v[i].END] = 1, c[1]++, M = 1, dfs(v[i].END, rt);
        Calc(M, -1);
    }
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        if (vis[v[i].END]) continue;
        root = 0, Max[0] = Sum = size[v[i].END];
        Get_Root(v[i].END, 0);
        DFS(v[i].END);
    }
}
int main()
{
    memset (first, -1, sizeof (first));
    int n = read();
    for (int i = 1; i <= n - 1; i++)
    {
        int a = read() + 1, b = read() + 1;
        add(a, b);
        add(b, a);
    }
    root = 0, Max[0] = Sum = n;
    Get_Root(1, 0);
    DFS(root);
    double ans = 0;
    for (int i = 1; i <= n; i++) if (g[i]) ans += 1.0 * g[i] / i;
    printf ("%.4f\n", ans);
}