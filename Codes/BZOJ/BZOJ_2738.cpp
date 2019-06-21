#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Quer
{
    int x1, y1, x2, y2, k;
}Q[60005], *q[60005], *nq[60005];
struct data
{
    int val, x, y;
    bool operator < (const data &a) const 
    {
        return val < a.val;
    }
}a[505 * 505];
int Sum[505][505];
int cnt, ans[60005], n, now;
#define lowbit(_) ((_)&(-_))
void add(int x, int y, int c)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            Sum[i][j] += c;
}
int Query(int x, int y)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            ans += Sum[i][j];
    return ans;
}
int Query(int x_1, int y_1, int x_2, int y_2)
{
    return Query(x_2, y_2) - Query(x_2, y_1 - 1) - Query(x_1 - 1, y_2) + Query(x_1 - 1, y_1 - 1);
}
void Solve(int l, int r, int L, int R)
{
    if (l > r) return;
    int mid = L + R >> 1;
    if (L == R)
    {
        for (int i = l; i <= r; i++)
            ans[q[i] - Q] = mid;
        return;
    }
    while ( now != cnt && a[now + 1].val <= mid)
    {
        now++;
        add(a[now].x, a[now].y, 1);
    }
    while ( now && a[now].val > mid)
    {
        add(a[now].x, a[now].y, -1);
        now--;
    }
    int x = l, y = r;
    for (int i = l; i <= r; i++)
    {
        int K = Query(q[i]->x1, q[i]->y1, q[i]->x2, q[i]->y2);
        if (q[i]->k > K) nq[y--] = q[i];
        else  nq[x++] = q[i];
    }
    memcpy(q + l, nq + l, sizeof(q[0]) * (r - l + 1));
    Solve(l, x - 1, L, mid);
    Solve(y + 1, r, mid + 1, R);
}
int main()
{
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[++cnt].val), a[cnt].x = i, a[cnt].y = j;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d%d", &Q[i].x1, &Q[i].y1, &Q[i].x2, &Q[i].y2, &Q[i].k);
        q[i] = &Q[i];
    }
    sort(a + 1, a + cnt + 1);
    Solve(1, m, 0, a[cnt].val);
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
}