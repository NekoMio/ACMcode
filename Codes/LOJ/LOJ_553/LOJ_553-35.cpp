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
inline void gmin(int &a, int b) { if (a > b) a = b; }
const int MAXN = 105;
int v[MAXN], l[MAXN];
int F[MAXN][128];
int main()
{
    // freopen ("1.out", "w", stdout);
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
        v[i] = read(), l[i] = read();
    int q = read();
    if (m <= 100)
    {
        memset (F, 0x3f, sizeof (F));
        F[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 128; j++)
            {
                for (int k = 1; k <= l[i]; k++)
                    gmin(F[i][j | k], F[i - 1][j] + v[i]);
                gmin(F[i][j], F[i - 1][j]);
            }
        while (q--)
        {
            int c = read();
            printf ("%d\n", F[n][c] == 0x3f3f3f3f ? -1 : F[n][c]);
        }
    }
}