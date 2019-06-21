/**
******************************************************************************
* @file	Evensgn
* @author WildRage
* @version v 1.0
* @date  2017-5-10 10:55:23
* @brief 
******************************************************************************
*/
#include <cstdio>
#include <cstring>
#include <vector>
const int P = 1e9 + 7;
namespace Mine_WorkSpace
{
struct data
{
    struct edge
    {
        int END, next;
    } v[200005];
    int first[100005], p;
    data()
    {
        memset(first, -1, sizeof(first));
        p = 0;
    }
    void add(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
} Edge;
bool color[100005];
long long f[100005][2];
void  DP(int rt, int fa)
{
    f[rt][0] = 1;
    f[rt][1] = 0;
    for (int i = Edge.first[rt]; i != -1; i = Edge.v[i].next)
    {
        if (fa != Edge.v[i].END)
        {
            DP(Edge.v[i].END, rt);
            f[rt][1] = (f[rt][1] * f[Edge.v[i].END][0]) % P;
            f[rt][1] = (f[rt][1] + f[Edge.v[i].END][1] * f[rt][0]) % P;
            f[rt][0] = (f[rt][0] * f[Edge.v[i].END][0]) % P;
        }
    }
    if (color[rt])
        f[rt][1] = f[rt][0];
    else
        f[rt][0] = (f[rt][1] + f[rt][0]) % P;
}
int Main()
{
    int n;
    scanf("%d", &n);
    int a, b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &b);
        Edge.add(i + 1, b + 1), Edge.add(b + 1, i + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        if (a)
            color[i] = 1;
    }
    DP(1,0);
    printf("%lld\n", f[1][1]);
    // Print_tree(1);
    // while(1);
}
}
int main() { Mine_WorkSpace::Main(); }
