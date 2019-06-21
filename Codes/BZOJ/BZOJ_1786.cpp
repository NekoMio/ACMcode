#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, k;
int a[10005];
int c[2][10005];
#define lowbit(_) ((_)&(-_))
void add(int x, int add, int op)
{
    for (int i = x; i <= k; i+=lowbit(i))
        c[op][i] += add;
}
int Query(int x, int op)
{
    int ans = 0;
    for (int i = x; i > 0; i-=lowbit(i))
        ans += c[op][i];
    return ans;
}
int Get_Num(int &s)
{
    int Min = 0x3f3f3f3f, ans;
    for (int i = 1; i <= k; i++)
    {
        int now = Query(i - 1, 0) + Query(k, 1) - Query(i, 1);
        if(now < Min) Min = now, ans = i;
    }
    s += Min;
    add(ans, 1, 1);
    return ans;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if(a[i] != -1) add(a[i], 1, 0), ans += Query(k, 0) - Query(a[i], 0);
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > 0) add(a[i], -1, 0), add(a[i], 1, 1);
        else a[i] = Get_Num(ans);
    }
    printf("%d", ans);
}