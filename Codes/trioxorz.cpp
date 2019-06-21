#include <cstring>
#include <cstdio>
using namespace std;

struct Vector
{
    int x, y;
    Vector operator-(const Vector &a)
    {
        return (Vector){x - a.x, y - a.y};
    }
    int operator*(const Vector &a)
    {
        return x * a.y - a.x * y;
    }
} A, B, C, D;

int main()
{
    freopen("trioxorz.in","r",stdin);
    freopen("trioxorz.out","w",stdout);
    A.x = 0, A.y = 0;
    int n;
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d%d%d%d", &B.x, &B.y, &C.x, &C.y, &D.x, &D.y);
        int a = (B - C) * (A - C);
        int b = (D - B) * (A - B);
        int c = (C - D) * (A - D);
        if (a > 0 && b > 0 && c > 0)
            ans++;
        if (a < 0 && b < 0 && c < 0)
            ans++;
    }
    printf("%d", ans);
}