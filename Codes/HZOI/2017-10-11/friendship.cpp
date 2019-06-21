#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
}v[800005][2];
int first[800005][2], p[2];
void add (int a, int b, int op)
{
    v[p[op]][op].END = b;
    v[p[op]][op].next = first[a][op];
    first[a][op] = p[op]++;
}
int id, n, m;
int Type[800005], size[800005];
bool DFS(int rt, int S, int tp, int END)
{
    if (tp == 0)
    {
        if (rt == END) return 1;
        if (Type[rt] != tp && Type[rt] != -1 && size[rt] != 1) return 0;
    }
    else if (S != rt)
    {
        if (Type[rt] != tp && Type[rt] != -1 && size[rt] != 1) return 0;
    }
    if (rt == END) return 1;
    bool ans = 0;
    for (int i = first[rt][tp]; i != -1; i = v[i][tp].next)
    {
        ans |= DFS(v[i][tp].END, S, tp, END);
    }
    return ans;
}
int Get_Ans(int x, int y)
{
    if (x == y) return 1;
    if (x <= n && y <= n) return 0;
    if (x < y)
        return DFS(x, x, 1, y);
    else
        return DFS(x, x, 0, y);
}
int main()
{
    memset (first, -1, sizeof (first));
    scanf ("%d%d", &n, &m);
    id = n;
    for (int i = 1; i <= n; i++) Type[i] = -1;
    int op, K, a, tpye;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%d%d%d", &tpye, &op, &K);
        if (tpye == 0)
        {
            Type[++id] = op;
            size[id] = K;
            for (int j = 1; j <= K; j++)
            {
                scanf ("%d", &a);
                add(a, id, 1);
                add(id ,a, 0);
            }
        }
        else
        {
            // OP = X, K = Y;
            printf("%d\n", Get_Ans(op, K));
        }
    }
    // while (1);
}