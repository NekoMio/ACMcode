#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MaxN = 1000000;
int Max1[MaxN + 5], Max2[MaxN + 5], Max3[MaxN + 5];
#define lowbit(_) ((_) & (-_))
void Update1(int a, int b)
{
    for (int i = a; i <= MaxN; i += lowbit(i))
    {
        Max1[i] = max(b, Max1[i]);
    }
}
void Update2(int a, int b)
{
    for (int i = a; i > 0; i -= lowbit(i))
    {
        Max2[i] = max(b, Max2[i]);
    }
}
int MAX1(int x)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        ans = max(ans, Max1[i]);
    }
    return ans;
}
int MAX2(int x)
{
    int ans = 0;
    for (int i = x; i <= MaxN; i += lowbit(i))
    {
        ans = max(ans, Max2[i]);
    }
    return ans;
}
int a[500005], op[500005];
int f[500005][4], n, k;
void add(int len, int a)
{
    int W = (len - 1) % k + 1;
    switch (op[W])
    {
    case 1:
        Update1(a, len);
        break;
    case 2:
        Update2(a, len);
        break;
    case 3:
        Max3[a] = max(len, Max3[a]);
        break;
    default:
        printf("ERROR\n");
        exit(0);
        break;
    }
}
int main()
{
    //freopen("mot.in", "r", stdin);
    //freopen("mot.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    char c;
    for (int i = 1; i <= k; i++)
    {
        c = getchar();
        while (c != '<' && c != '>' && c != '=')
            c = getchar();
        switch (c)
        {
        case '<':
            op[i] = 1;
            break;
        case '>':
            op[i] = 2;
            break;
        case '=':
            op[i] = 3;
        }
    }
    int ans = 0;
    //f[1][1] = f[1][2] = f[1][3] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i][1] = MAX1(a[i] - 1) + 1;
        f[i][2] = MAX2(a[i] + 1) + 1;
        f[i][3] = Max3[a[i]] + 1;
        for (int j = 1; j <= 3; j++)
        {
            add(f[i][j], a[i]);
            ans = max(ans, f[i][j]);
        }
    }
    //for(int i=1;i<=n;i++)
    //    printf("%d %d %d\n",f[i][1],f[i][2],f[i][3]);
    // while(1);
    printf("%d", ans);
}
