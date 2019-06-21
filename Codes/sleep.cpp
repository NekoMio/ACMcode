#include <cstdio>
#include <cstring>
using namespace std;
int a[100005], op[100005];
int er[31][100005];
int n, m;
void to_two(int c, int j)
{
    int i = 1;
    while (c)
    {
        er[i][j] = (c & 1);
        i++, c >>= 1;
    }
}
bool judge(int j, int c)
{
    int ans = c;
    for (int i = 1; i <= n; i++)
    {
        if (op[i] == 1)
            ans &= er[j][i];
        else if (op[i] == 2)
            ans |= er[j][i];
        else if (op[i] == 3)
            ans ^= er[j][i];
    }
    return ans;
}
int main()
{
    freopen("sleep.in","r",stdin);
    freopen("sleep.out","w",stdout);
    scanf("%d%d", &n, &m);
    char c[10];
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", c);
        if (c[0] == 'A')
            op[i] = 1;
        else if (c[0] == 'O')
            op[i] = 2;
        else
            op[i] = 3;
        scanf("%d", &a[i]);
        to_two(a[i], i);
    }
    int ans = 0;
    //printf("%d\n",ans);
    for (int i = 29; i > 0; i--)
    {
        if (judge(i, 0))
            ;
        else
        {
            if (judge(i, 1))
                if ((ans | (1 << (i - 1))) <= m)
                    ans |= (1 << (i - 1));
        }
        //printf("%d\n",ans);
    }
    //printf("%d\n",ans);
    for (int i = 1; i <= n; i++)
    {
        if (op[i] == 1)
            ans &= a[i];
        else if (op[i] == 2)
            ans |= a[i];
        else if (op[i] == 3)
            ans ^= a[i];
    }
    printf("%d", ans);
}