#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 4e5 + 5;
int a[MAXN];
int main()
{
    // freopen ("1.out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    int Q = read();
    while (Q--)
    {
        int r1 = read(), c1 = read(), r2 = read(), c2 = read();
        if (r1 < r2)
        {
            int id = r1 - 1;
            for (int j = r2; j >= r1; j--)
                if (a[j] < c2)
                {
                    id = j;
                    break;
                }
            int ans = 0x3f3f3f3f, s = 0;
            for (int i = id + 1; i <= r2; i++)
                if (ans > a[i] - c2)
                    ans = a[i] - c2, s = i;
            int Ans = ans + r2 - r1 + (id == r1 - 1 ? c1 < a[s] : 1);
            // Ans = min(Ans, r2 - r1 + abs(c2 - (min(c1, a[id]))));
            if (id == r1 - 1 || c1 <= a[id]) Ans = min(Ans, r2 - r1 + abs(c2 - c1));
            if (id != r1 - 1 && a[id] <= c2 && a[id] <= c1) Ans = min(Ans, r2 - r1 + c2 - a[id]);
            Ans = min(Ans, r2 - r1 + c2 + 1);
            printf ("%d\n", Ans);
        }
        else if (r1 > r2)
        {
            int id = r1 + 1;
            for (int j = r2; j <= r1; j++)
                if (a[j] < c2)
                {
                    id = j;
                    break;
                }
            int ans = 0x3f3f3f3f, s = 0;
            for (int i = r2; i <= id - 1; i++)
                if (ans > a[i] - c2)
                    ans = a[i] - c2, s = i;
            int Ans = ans + r1 - r2 + (id == r1 + 1 ? c1 < a[s] : 1);
            // Ans = min(Ans, r1 - r2 + abs(c2 - (min(c1, a[id]))));
            if (id == r1 + 1 || c1 <= a[id]) Ans = min(Ans, r1 - r2 + abs(c2 - c1));
            if (id != r1 + 1 && a[id] <= c2 && a[id] <= c1) Ans = min(Ans, r1 - r2 + c2 - a[id]);
            Ans = min(Ans, r1 - r2 + c2 + 1);
            printf ("%d\n", Ans);
        }
        else if (r1 == r2)
        {
            // if (c1 > c2) swap(c1, c2);
            int Ans;
            if (c1 < c2) Ans = min(c2 - c1, a[r1] - c2 + 1);
            else Ans = min(c1 - c2, c2 + 1);
            printf ("%d\n", Ans);
        }
    }
}