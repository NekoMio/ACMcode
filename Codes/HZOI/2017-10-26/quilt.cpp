#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char map[305][305];
int Num[60];
int main()
{
    // freopen("quilt.in", "r", stdin);
    // freopen("quilt.out", "w", stdout);
    int T;
    scanf ("%d", &T);
    while (T--)
    {
        memset (Num, 0, sizeof (Num));
        int n, m;
        scanf ("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf ("%s", map[i] + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                Num[map[i][j] - 'a' + 1]++;
        int t1 = 0, t2 = 0;
        if ((n & 1) && (m & 1)) t1 = 1;
        if (n & 1) t2 += m;
        if (m & 1) t2 += n;
        t2 >>= 1;
        t2 -= t1;
        for (int i = 1; i <= 26; i++)
        {
            if (Num[i] & 1)
            {
                if (t1) t1 = 0,Num[i]--;
            }
            if (Num[i] % 4 != 0)
            {
                if (t2) t2--,Num[i] -= 2;
            }
            if (Num[i] % 4 == 0)
            {
                Num[i] = 0;
            }
        }
        bool flag = 0;
        for (int i = 1; i <= 26; i++)
            if (Num[i]) 
                flag = 1;
        printf ("%s\n", flag ? "No" : "Yes");
    }
    // fclose(stdin); fclose(stdout);
}