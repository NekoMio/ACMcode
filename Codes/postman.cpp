#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;
#define LL long long
const int BA = 100000, SIZEN = 10, SIZEM = 20, BASE = 200000;
int N, M;
int H[BASE];
class BigNum /**高精度 */
{
  public:
    int n;
    int s[50];
    void operator=(int a)
    {
        n = 1;
        memset(s, 0, sizeof(s));
        s[0] = a;
    }
    void operator+=(BigNum a)
    {
        n = max(n, a.n) + 1;
        for (int i = 0; i <= n; i++)
        {
            s[i] += a.s[i];
            s[i + 1] += s[i] / BA;
            s[i] %= BA;
        }
        while (n > 0 && s[n - 1] == 0)
        {
            n--;
        }
    }
    void operator*=(int a)
    {
        n++;
        for (int i = 0; i <= n; i++)
            s[i] *= a;
        for (int i = 0; i <= n; i++)
        {
            s[i + 1] += s[i] / BA;
            s[i] %= BA;
        }
        while (n > 0 && s[n - 1] == 0)
        {
            n--;
        }
    }
    void print()
    {
        printf("%d", s[n - 1]);
        for (int i = n - 2; i >= 0; i--)
            printf("%05d", s[i]);
    }
} ans;

class Pair /**映射表 */
{
  public:
    BigNum Sum;
    LL Id;
    Pair() {}
    Pair(LL a, BigNum b)
    {
        Id = a;
        Sum = b;
    }
};
deque<Pair> f[2]; /**循环数组 */
void read()       /**read */
{
    scanf("%d%d", &N, &M);
    if (N < M)
        swap(N, M);
}
int Get(int x, int j) /**取4进制的操作 */
{
    x >>= 2 * (j - 1);
    x &= 3;
    return x;
}
int Change(int x, int j, int t) /**把x的第j位改成t */
{
    int tmp = x >> (2 * (j - 1));
    x -= tmp << (j - 1) * 2;
    tmp >>= 2;
    x += tmp << 2 * j;
    x += t << ((j - 1) * 2);
    return x;
}
int Find(int x, int j, int dat) /**找与他相连的括号 */
{
    int now = dat, k = j;
    while (k >= 1 && k <= M + 1)
    {
        k += now;
        int tmp = Get(x, k);
        if (tmp == 1)
            dat++;
        if (tmp == 2)
            dat--;
        if (dat == 0)
            return k;
    }
}
void Push(int k, int Id, BigNum Sum) /**插入hash表 */
{
    int now = Id % BASE;
    while (H[now]) /**如果有 */
    {
        if (f[k][H[now]].Id == Id) /**且就是这个状态 */
        {
            f[k][H[now]].Sum += Sum; /**加值，和并答案 */
            return;
        }
        now++; /**找自己的状态 */
        if (now == BASE)
            now = 0;
    }
    H[now] = f[k].size(); /**如果第一次出现 */
    f[k].push_back(Pair(Id, Sum));
}
/**
 * 1为左括号
 * 2为右括号
 * 0为无括号
 */
void DP()
{
    int k = 0;
    BigNum p;
    p = 1; /**初始化状态 */
    f[k].push_back(Pair(0, p));
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            k ^= 1;                  /**滚动数组 */
            f[k].clear();            /**清空本维 */
            memset(H, 0, sizeof(H)); /**hash 数组 */
            for (int m = 0; m < f[k ^ 1].size(); m++)
            {
                int Id = f[k ^ 1][m].Id;       /**取状态 */
                BigNum date = f[k ^ 1][m].Sum; /**取值 */
                int L = Get(Id, j), U = Get(Id, j + 1);
                /**
                 * L:左面的 ，U: 右面的
                 */
                int tmp;      /**分类讨论开始 */
                if (!L && !U) /**两个插头都是无插头状态 */
                {
                    if (i != N && j != M) /**如果不是最后一个 */
                    {
                        tmp = Change(Id, j, 1); /**构造一组新的括号 */
                        tmp = Change(tmp, j + 1, 2);
                        Push(k, tmp, date); /**插入Hash */
                    }
                }
                else if (!L && U) /**左面的没有 */
                {
                    if (j != M)            /**向右转移 */
                        Push(k, Id, date); /**延续状态 当j==M事不能向右动*/
                    if (i != N)            /**向下转移 */
                    {
                        /**将L,U位置的 状态互换 转移*/
                        tmp = Change(Id, j, U);
                        tmp = Change(tmp, j + 1, 0);
                        Push(k, tmp, date);
                    }
                }
                else if (L && !U) /**上面的没有 */
                {
                    if (i != N) /**向下 */
                        Push(k, Id, date);
                    if (j != M) /**向右 */
                    {
                        /**于上同理 */
                        tmp = Change(Id, j, 0);
                        tmp = Change(tmp, j + 1, L);
                        Push(k, tmp, date);
                    }
                }
                else if (L == 1 && U == 1) /**两个都是左括号 */
                {
                    tmp = Change(Id, Find(Id, j + 1, 1), 1); /**将与上面相连的右括号转为左括号 */
                    tmp = Change(tmp, j, 0);                 /**这两位都制为无括号 */
                    tmp = Change(tmp, j + 1, 0);
                    Push(k, tmp, date);
                }
                else if (L == 2 && U == 2)                /**两个都是右括号 */
                {                                         /**与上面对称 */
                    tmp = Change(Id, Find(Id, j, -1), 2); /**将与左面相连的左括号制为右括号 */
                    tmp = Change(tmp, j, 0);               /**这两位都为无括号 */
                    tmp = Change(tmp, j + 1, 0);
                    Push(k, tmp, date);
                }
                else if (L == 2 && U == 1) /**左插头为右括号 上插头为左括号 */
                {                          /**都制为无 */
                    tmp = Change(Id, j, 0);
                    tmp = Change(tmp, j + 1, 0);
                    Push(k, tmp, date);
                }
                else if (L == 1 && U == 2)
                {
                    if (i == N && j == M)
                        ans += date;
                }
            }
        }
        for (int km = 0; km < f[k].size(); km++) /**提前换行准备为下一行使用 */
            f[k][km].Id <<= 2;
    }
    ans *= 2;
    ans.print();
}
int main()
{
    //freopen("postman.in", "r", stdin);
    //freopen("postman.out", "w", stdout);
    read();
    if (M == 1)
    {
        printf("1");
        return 0;
    }
    DP();
    return 0;
}