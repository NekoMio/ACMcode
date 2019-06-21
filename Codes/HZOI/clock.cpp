#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int v[305][305];
int a[1000005];
int pre[1000005], nxt[1000005];
bool die[1000005];
int n, c;
int val[1000005];
inline bool Judge()
{
    int last = -1;
    for (int i = nxt[0]; i <= n; i = nxt[i])
    {
        if (last == -1)
            last = a[i];
        if (last != a[i])
            return 1;
    }
    return 0;
}
inline void Delete(int x)
{
    pre[nxt[x]] = pre[x];
    nxt[pre[x]] = nxt[x];
}
int main()
{
    scanf("%d%d", &c, &n);
    for (int i = 1; i <= c; i++)
        for (int j = 1; j <= c; j++)
            scanf("%d", &v[i][j]);
    for (int i = 1; i <= n; i++)
        val[i] = 1;
    nxt[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        pre[i] = i - 1;
        nxt[i] = i + 1;
    }
    while (Judge())
    {
        for (int i = nxt[0]; i<=n; i = nxt[i])
            val[i] += v[a[i]][a[nxt[i]]] + v[a[i]][a[pre[i]]];
        for (int i = nxt[0]; i<=n; i = nxt[i])
            if (val[i] <= 0)
                Delete(i);
    }
    printf("%d\n", a[nxt[0]]);
    //while (1)
    ;
}
