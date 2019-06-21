#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
namespace MineWorkSpace
{
int n;
class Block_Main
{
    int block, n;
    int a[50005], in[50005], sum[305];

  public:
    void Init(int N)
    {
        memset(in, 0, sizeof(in));
        memset(sum, 0, sizeof(sum));
        memset(a, 0, sizeof(a));
        n = N;
        block = sqrt(n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
            in[i] = (i - 1) / block + 1;
            sum[in[i]] += a[i];
        }
    }
    void Updata(int i, int c)
    {
        a[i] += c;
        sum[in[i]] += c;
    }
    int Query(int l, int r)
    {
        int ans = 0;
        if (in[l] == in[r])
        {
            for (int i = l; i <= r; i++)
                ans += a[i];
            return ans;
        }
        else
        {
            for (int i = in [l] + 1; i <= in[r] - 1; i++)
                ans += sum[i];
            for (int i = l; i <= in[l] * block; i++)
                ans += a[i];
            for (int i = (in[r] - 1) * block + 1; i <= r; i++)
                ans += a[i];
            return ans;
        }
    }
} Block;
class Order_run
{
    int l, r;

  public:
    void Run(char c)
    {
        if (c == 'Q')
        {
            scanf("%d%d", &l, &r);
            if (l > r)
                printf("0\n");
            else
                printf("%d\n", Block.Query(l, r));
            return;
        }
        if (c == 'A')
        {
            scanf("%d%d", &l, &r);
            Block.Updata(l, r);
            return;
        }
        if (c == 'S')
        {
            scanf("%d%d", &l, &r);
            Block.Updata(l, -r);
            return;
        }
    }
} Order;
class Main
{
  public:
    Main()
    {
        int T;
        scanf("%d", &T);
        for (int L = 1; L <= T; L++)
        {
            printf("Case %d:\n", L);
            scanf("%d", &n);
            Block.Init(n);
            char s[10];
            while (1)
            {
                scanf("%s", s);
                if (s[0] == 'E')
                    break;
                Order.Run(s[0]);
            }
        }
    }
} run;
}
int main() { ; }