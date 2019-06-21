#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int fa1[1000005], fa2[1000005];
long long w1[1000005], w2[1000005];
long long Min1[1000005], Min2[1000005];
struct Point
{
    int x, y, v;
} a[1000005];
bool cmpx(const Point &A, const Point &B)
{
    return A.x < B.x;
}
bool cmpy(const Point &A, const Point &B)
{
    return A.y < B.y;
}
int find1(int x)
{
    if (x == fa1[x])
        return x;
    int rt = find1(fa1[x]);
    w1[x] += w1[fa1[x]];
    return fa1[x] = rt;
}
int find2(int x)
{
    if (x == fa2[x])
        return x;
    int rt = find2(fa2[x]);
    w2[x] += w2[fa2[x]];
    return fa2[x] = rt;
}
bool link1(int a, int b, int w)
{
    if (find1(a) != find1(b))
    {
        int fa = find1(a), fb = find1(b);
        fa1[fa] = fa1[fb];
        w1[fa] = w + w1[b] - w1[a];
        return 1;
    }
    else
        return w1[a] == w + w1[b];
}
bool link2(int a, int b, int w)
{
    if (find2(a) != find2(b))
    {
        int fa = find2(a), fb = find2(b);
        fa2[fa] = fa2[fb];
        w2[fa] = w + w2[b] - w2[a];
        return 1;
    }
    else
        return w2[a] == w + w2[b];
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        bool flag = 1;
        int R, C;
        scanf("%d%d", &R, &C);
        for (int i = 1; i <= R; i++)
        {
            fa1[i] = i;
            w1[i] = 0;
        }
        for (int i = 1; i <= C; i++)
        {
            fa2[i] = i;
            w2[i] = 0;
        }
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].v);
        for (int i = 1; i <= n; i++)
            if (a[i].v < 0)
                flag = 0;
        sort(a + 1, a + n + 1, cmpx);
        for (int i = 1; i < n; i++)
            if (a[i].x == a[i + 1].x)
                if (!link2(a[i].y, a[i + 1].y, a[i + 1].v - a[i].v))
                    flag = false;
 
        sort(a + 1, a + n + 1, cmpy);
        for (int i = 1; i < n; i++)
            if (a[i].y == a[i + 1].y)
                if (!link1(a[i].x, a[i + 1].x, a[i + 1].v - a[i].v))
                    flag = false;
 
        memset(Min1, 0x3f, sizeof(Min1));
        memset(Min2, 0x3f, sizeof(Min2));
        for (int i = 1; i <= n; i++)
        {
            int rt = find1(a[i].x);
            Min1[rt] = min(Min1[rt], a[i].v + w1[a[i].x]);
        }
        for (int i = 1; i <= R; i++)
        {
            int rt = find1(i);
            Min2[rt] = min(Min2[rt], -w1[i]);
        }
        for (int i = 1; i <= R; i++)
        {
            if (fa1[i] == i && Min1[i] + Min2[i] < 0)
                flag = 0;
        }
        if(flag)
            puts("Yes");
        else
            puts("No");
    }
}