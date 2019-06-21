#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int st[1005], top, n;
struct Point
{
    int x, y;
} a[1005];
struct Vector
{
    int x, y;
    long long operator*(const Vector &a)
    {
        return (long long)x * a.y - (long long)a.x * y;
    }
    Vector operator-(const Vector &a)
    {
        return (Vector){x - a.x, y - a.y};
    }
} P[1005];
double dis(Vector a, Vector b)
{
    return sqrt((long long)(a.x - b.x) * (a.x - b.x) + (long long)(a.y - b.y) * (a.y - b.y));
}
bool operator<(Vector a, Vector b)
{
    long long s = (a - P[1]) * (b - P[1]);
    if (s == 0)
        return dis(a, P[1]) < dis(b, P[1]);
    return s > 0;
}
bool nok[1005];
long long Graham()
{
    memset(P, 0, sizeof(P));
    memset(st, 0, sizeof(st));
    int cnt = 0;
    int k = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!nok[i])
        {
            P[++cnt].x = a[i].x;
            P[cnt].y = a[i].y;
            if ((P[cnt].x < P[k].x && P[cnt].y < P[k].y)||!k)
                k = cnt;
        }
    }
    swap(P[1], P[k]);
    sort(P + 2, P + cnt + 1);
    int top = 0;
    st[++top] = 1;
    for (int i = 2; i <= cnt; i++)
    {
        while (top > 1 && (P[st[top]] - P[st[top - 1]]) * (P[i] - P[st[top]]) < 0)
            top--;
        st[++top] = i;
    }
    long long ans = 0;
    for (int i = 1; i < top; i++)
    {
        ans += P[st[i]] * P[st[i + 1]];
    }
    ans += P[st[top]] * P[1];
    return ans;
}
int main()
{
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    long long S = -1, k, c;
    while (m--)
    {
        scanf("%lld", &k);
        memset(nok,0,sizeof(nok));
        for (int i = 1; i <= k; i++)
        {
            scanf("%lld", &c);
            nok[(S + c) % n + 1] = 1;
        }
        S = Graham();
        printf("%lld\n",S);
    }
}
