#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int S, E, next;
}v[4005];
int first[2005], p;
void add(int a, int b)
{
    v[p].E = b;
    v[p].S = a;
    v[p].next = first[a];
    first[a] = p++;
}
int Sum;
void dfs(int x, int fa, int Dep, int S)
{
    Sum = max(Sum, Dep);
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if (v[i].E == fa) continue;
        dfs(v[i].E, x, Dep + (((S & (1 << (i >> 1))) != 0 && (i & 1)) || (!(i & 1) && (((S & (1 << (i >> 1))) == 0)))), S);
    }
}
int n;
int Get_Num(int x)
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
        Sum = 0, dfs(i, 0, 0, x), ans = max(ans, Sum);
    return ans;
}
int main()
{
    int a, b;
    memset (first, -1, sizeof (first));
    scanf ("%d", &n);
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    int N = (1 << (n - 1)) - 1;
    int Min = 0x3f3f3f3f, Num = 0;
    for (int i = 0; i <= N; i++)
    {
        int now = Get_Num(i);
        if (now < Min) Min = now, Num = 1;
        else if (now == Min) Num++;
    }
    printf ("%d", Num);
}