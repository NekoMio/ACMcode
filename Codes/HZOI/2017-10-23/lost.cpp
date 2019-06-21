#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5;
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
int c[N];
struct data
{
    int next, END;
}v[N];
int first[N], p, dep[N];
int que[N], cnt;
double ans[N];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
double K(int a, int b)
{
    return ((double)c[a] - c[b]) / (dep[a] - dep[b]);
}
void DFS(int rt, int len, int Dep)
{
    dep[rt] = Dep;
    int l = 1, r = len;
    int Ans = 1;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (mid == len) {Ans = len; break;}
        if (K(que[mid], que[mid + 1]) <= K(que[mid + 1], rt)) Ans = mid + 1, l = mid + 1;
        else r = mid - 1;
    }
    ans[rt] = -K(que[Ans], rt);
    Ans++;
    int tmp = que[Ans];
    que[Ans] = rt;
    for (int i = first[rt]; i != -1; i = v[i].next)
        DFS(v[i].END, Ans, Dep + 1);
    que[Ans] = tmp;
}
int main()
{
    int n;
    memset(first, -1, sizeof(first));
    n = read();
    for (int i = 1; i <= n; i++)
        c[i] = read();
    int a;
    for (int i = 2; i <= n; i++)
    {
        a = read();
        add(a, i);
    }
    DFS(1, 0, 0);
    for (int i = 2; i <= n; i++)
        printf ("%.10lf\n", ans[i]);
    // printf("%lf", (double)clock()/CLOCKS_PER_SEC);
}
