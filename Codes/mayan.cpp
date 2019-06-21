#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;
//#define WILDRAGE 1
int a[6][8];
bool over[6][8];
void print(const int c[6][8])
{
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 7; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
    printf("\n");
}
bool ok(const int c[6][8])
{
    //return 0;
    for (int i = 1; i <= 5; i++)
    {
        if (c[i][1])
            return 0;
    }
    return 1;
}
bool remove(int c[6][8])
{
    int it1, it2;
    for (int i = 1; i <= 5; i++)
    {
        it1 = it2 = 1;
        while (1)
        {
            while (c[i][it1] != 0 && it1 <= 7)
                it1++;
            it2 = it1;
            while (c[i][it2] == 0 && it2 <= 7)
                it2++;
            if (it2 != 8)
                swap(c[i][it2], c[i][it1]);
            else
                break;
        }
    }
    // memset(over,0,sizeof(over));
    int times = 1;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
        {
            if (c[i][j] && c[i][j] == c[i][j - 1])
            {
                times++;
                if (times >= 3 && times < 4)
                {
                    over[i][j - 2] = over[i][j - 1] = over[i][j] = 1;
                }
                if (times >= 4)
                    over[i][j] = 1;
            }
            else
                times = 1;
        }
    times = 1;
    for (int j = 1; j <= 7; j++)
        for (int i = 1; i <= 5; i++)
        {
            if (c[i][j] && c[i][j] == c[i - 1][j])
            {
                times++;
                if (times >= 3 && times < 4)
                {
                    over[i - 2][j] = over[i - 1][j] = over[i][j] = 1;
                }
                if (times >= 4)
                    over[i][j] = 1;
            }
            else
                times = 1;
        }
    bool yes = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
            if (over[i][j])
                yes = 1, over[i][j] = 0, c[i][j] = 0;
    if (!yes)
        return 0;
    //int it1, it2;
    for (int i = 1; i <= 5; i++)
    {
        it1 = it2 = 1;
        while (1)
        {
            while (c[i][it1] != 0 && it1 <= 7)
                it1++;
            it2 = it1;
            while (c[i][it2] == 0 && it2 <= 7)
                it2++;
            if (it2 != 8)
                swap(c[i][it2], c[i][it1]);
            else
                break;
        }
    }
    return 1;
}
struct data
{
    int x, y, t;
};
stack<data> op;
stack<data> ans;
int n;
void dfs(int t, const int c[6][8])
{
    if (t == n)
    {
#ifdef WILDRAGE
        print(c);
#endif
        if (ok(c))
        {
            while (!op.empty())
            {
                ans.push(op.top());
                op.pop();
            }
            while (!ans.empty())
            {
                printf("%d %d %d\n", ans.top().x - 1, ans.top().y - 1, ans.top().t);
                ans.pop();
            }
            exit(0);
        }
        return;
    }
    else
    {
        int s[6][8];
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= 7; j++)
            {
                if (c[i][j] && i + 1 <= 5)
                {
                    op.push((data){i, j, 1});
                    memcpy(s, c, sizeof(s));
                    swap(s[i][j], s[i + 1][j]);
#ifdef WILDRAGE
//print(s);
#endif
                    while (remove(s))
                        ;
#ifdef WILDRAGE
                    printf("%d %d %d\n", i, j, 1);
                    print(s);
#endif
                    dfs(t + 1, s);
                    op.pop();
                }
                if (c[i][j] && i - 1 > 0 && !c[i - 1][j])
                {
                    op.push((data){i, j, -1});
                    memcpy(s, c, sizeof(s));
                    swap(s[i][j], s[i - 1][j]);
#ifdef WILDRAGE
//print(s);
#endif
                    while (remove(s))
                        ;
#ifdef WILDRAGE
                    printf("%d %d %d\n", i, j, -1);
                    print(s);
#endif
                    dfs(t + 1, s);
                    op.pop();
                }
            }
        }
    }
}
int main()
{
#ifndef WILDRAGE
    freopen("mayan.in", "r", stdin);
    freopen("mayan.out", "w", stdout);
#endif
    int s;
    scanf("%d", &n);
    for (int i = 1; i <= 5; i++)
    {
        int j = 0;
        while (scanf("%d", &s))
        {
            if (s == 0)
                break;
            a[i][++j] = s;
        }
        //a[i][0] = j;
    }
#ifdef WILDRAGE
    print(a);
#endif
    dfs(0, a);
    printf("-1\n");
}
