/*
 * @Author: WildRage 
 * @Date: 2017-07-30 13:41:21 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-07-30 13:47:36
 */
#define rocket 1
#define bomb 1
#define Single_card 1
#define Pair_cards 1
#define three_cards 1
#define three_and_one 1
#define three_and_two 1
#define four_and_two 1
#define straight 1
#define one_straight 1
#define two_straight 1
#define three_straight 1


#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Poker
{
    int Num;
    int color;
    bool operator<(const Poker &a) const
    {
        if (a.color == 0)
        {
            if (color != 0)
                return 1;
            return Num < a.Num;
        }
        if (a.Num == 2)
        {
            if (color == 0)
                return 0;
            else if (Num != 2)
                return 1;
            else
                return color < a.color;
        }
        if (a.Num == 1)
        {
            if (color == 0)
                return 0;
            if (Num == 2)
                return 0;
            if (Num != 1)
                return 1;
            else
                return color < a.color;
        }
        if (color == 0)
        {
            if (color != 0)
                return 0;
            return Num < a.Num;
        }
        if (Num == 2)
        {
            if (a.color == 0)
                return 1;
            else if (a.Num != 2)
                return 0;
            else
                return color < a.color;
        }
        if (Num == 1)
        {
            if (a.color == 0)
                return 1;
            if (a.Num == 2)
                return 1;
            if (a.Num != 1)
                return 0;
            else
                return color < a.color;
        }
        if (Num == a.Num)
            return color < a.color;
        return Num < a.Num;
    }
} a[25];
int DFS(int s, Poker *b)
{
    if (s == 0)
        return 0;
    Poker c[25];
    int ans = 0x3f3f3f3f;
//大王
#ifdef rocket
    if (b[s].color == b[s - 1].color && b[s].color == 0)
    {
        for (int i = 0; i <= s - 2; i++)
            c[i] = b[i];
        ans = min(ans, DFS(s - 2, c) + 1);
    }
#endif
    int times = 1;
//连排
#ifdef bomb
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            times++;
            if (times == 4)
            {
                int t = 0;
                for (int j = 0; j <= i - 4; j++, t++)
                    c[t] = b[j];
                for (int j = i + 1; j <= s; j++, t++)
                    c[t] = b[j];
                ans = min(ans, DFS(s - 4, c) + 1);
            }
        }
        else
            times = 1;
    }
#endif
#ifdef Single_card
    for (int i = 1; i <= s; i++)
    {
        int t = 0;
        for (int j = 0; j < i; j++, t++)
            c[t] = b[j];
        for (int j = i + 1; j <= s; j++, t++)
            c[t] = b[j];
        ans = min(ans, DFS(s - 1, c) + 1);
    }
#endif 
#ifdef Pair_cards
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            int t = 0;
            for (int j = 0; j <= i - 2; j++, t++)
                c[t] = b[j];
            for (int j = i + 1; j <= s; j++, t++)
                c[t] = b[j];
            ans = min(ans, DFS(s - 2, c) + 1);
        }
    }
#endif
    times = 1;
#ifdef three_cards
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            times++;
            if (times == 3)
            {
                int t = 0;
                for (int j = 0; j <= i - 3; j++, t++)
                    c[t] = b[j];
                for (int j = i + 1; j <= s; j++, t++)
                    c[t] = b[j];
                ans = min(ans, DFS(s - 3, c) + 1);
            }
        }
        else
            times = 1;
    }
#endif
#ifdef three_and_one
    times = 1;
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            times++;
            if (times == 3)
            {
                for (int k = 1; k <= s; k++)
                {
                    if (k > i - 3 && k <= i)
                        continue;
                    int t = 0;
                    for (int j = 0; j <= i - 3; j++)
                        if (j == k)
                            continue;
                        else
                            c[t++] = b[j];
                    for (int j = i + 1; j <= s; j++)
                        if (j == k)
                            continue;
                        else
                            c[t++] = b[j];
                    ans = min(ans, DFS(s - 4, c) + 1);
                }
            }
        }
        else
            times = 1;
    }
#endif
    times = 1;
#ifdef three_and_two
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            times++;
            if (times == 3)
            {
                for (int k = 1; k <= s; k++)
                {
                    if (b[k].Num != b[k - 1].Num)
                        continue;
                    if ((k > i - 3 && k <= i) || (k - 1 > i - 3 && k - 1 <= i))
                        continue;
                    int t = 0;
                    for (int j = 0; j <= i - 3; j++)
                        if (j == k || j == k - 1)
                            continue;
                        else
                            c[t++] = b[j];
                    for (int j = i + 1; j <= s; j++)
                        if (j == k || j == k - 1)
                            continue;
                        else
                            c[t++] = b[j];
                    ans = min(ans, DFS(s - 5, c) + 1);
                }
            }
        }
        else
            times = 1;
    }
#endif
    times = 1;
#ifdef four_and_two
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            times++;
            if (times == 4)
            {
                for (int k = 1; k <= s; k++)
                {
                    if (k > i - 4 && k <= i)
                        continue;
                    for (int m = 1; m <= s; m++)
                    {
                        if (m > i - 4 && m <= i && m != k)
                            continue;
                        int t = 0;
                        for (int j = 0; j <= i - 4; j++)
                            if (j == k || j == m)
                                continue;
                            else
                                c[t++] = b[j];
                        for (int j = i + 1; j <= s; j++)
                            if (j == k || j == m)
                                continue;
                            else
                                c[t++] = b[j];
                        ans = min(ans, DFS(s - 6, c) + 1);
                    }
                }
            }
        }
        else
            times = 1;
    }
#endif
//顺子
#ifdef straight
    int head[25];
    bool mark[25];
    times = 1;
#ifdef one_straight
    for (int i = 1; i <= s; i++)
    {
        memset(mark, 0, sizeof(mark));
        head[i] = 0;
        int x = i;
        for (int j = i; j <= s; j++)
        {
            if (b[j].Num != b[i].Num + 1)
                continue;
            if (b[j].Num > b[i].Num + 1)
                break;
            head[j] = x;
            x = j;
            times++;
        }
        if (times >= 5)
        {
            for (int j = x; j; j = head[j])
                mark[j] = 1;
            int t = 0;
            for (int j = 0; j <= s; j++)
                if (!mark[j])
                    c[t++] = b[j];
            ans = min(ans, DFS(s - times, c) + 1);
        }
        times = 1;
    }
#endif
#ifdef two_straight
    times = 1;
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            memset(mark, 0, sizeof(mark));
            head[i] = 0;
            int x = i;
            for (int j = i; j <= s; j++)
            {
                if (b[j].Num != b[j - 1].Num)
                    continue;
                if (b[j].Num != b[i].Num + 1)
                    continue;
                if (b[j].Num > b[i].Num + 1)
                    break;
                head[j] = x;
                x = j;
                times++;
            }
            if (times >= 3)
            {
                for (int j = x; j; j = head[j])
                    mark[j] = mark[j - 1] = 1;
                int t = 0;
                for (int j = 0; j <= s; j++)
                    if (!mark[j])
                        c[t++] = b[j];
                ans = min(ans, DFS(s - times * 2, c) + 1);
            }
        }
        times = 1;
    }
#endif
#ifdef three_straight
    times = 1;
    int TIME = 1;
    for (int i = 1; i <= s; i++)
    {
        if (b[i].Num == b[i - 1].Num)
        {
            TIME++;
            if (TIME == 3)
            {
                memset(mark, 0, sizeof(mark));
                head[i] = 0;
                int x = i;
                int T = 1;
                for (int j = i; j <= s; j++)
                {
                    if (b[j].Num != b[i].Num + 1)
                        continue;
                    if (b[j].Num > b[i].Num + 1)
                        break;
                    if (b[j].Num == b[j - 1].Num)
                    {
                        T++;
                        if (T == 3)
                        {
                            head[j] = x;
                            x = j;
                            times++;
                        }
                    }
                    else
                        T = 1;
                }
                if (times >= 2)
                {
                    for (int j = x; j; j = head[j])
                        mark[j] = mark[j - 1] = mark[j - 2] = 1;
                    int t = 0;
                    for (int j = 0; j <= s; j++)
                        if (!mark[j])
                            c[t++] = b[j];
                    ans = min(ans, DFS(s - times * 3, c) + 1);
                }
            }
        }
        times = 1;
        TIME = 1;
    }
#endif
#endif
    return ans;
}
int main()
{
    freopen("landlords.in","r",stdin);
    freopen("landlords.out","w",stdout);
    int T, n;
    // printf("%d\n", ((Poker){1, 3}) < ((Poker){3, 2}));
    // while (1)
    //     ;
    scanf("%d%d", &T, &n);
    while (T--)
    {
        memset(a, 0, sizeof(a));
        a[0].color = -1;
        a[0].Num = -1;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &a[i].Num, &a[i].color);
        }
        sort(a + 1, a + n + 1);
        printf("%d\n", DFS(n, a));
    }
}