#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int lim;
bool isheavy[100005];
int id[100005], t;
int cnt[100005][505];
long long Sum[505], Add[505], a[100005];
vector<int> All[100005], heavy[100005];
vector<int> v[100005];
int main()
{
    int n, m, q;
    scanf ("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    lim = sqrt(n);
    for (int i = 1; i <= m; i++)
    {
        int s, b;
        scanf ("%d", &s);
        if (s >= lim) id[i] = ++t, isheavy[i] = 1;
        for (int j = 1; j <= s; j++)
        {
            scanf ("%d", &b);
            All[b].push_back(i);
            v[i].push_back(b);
            if (isheavy[i])
            {
                Sum[id[i]] += a[b];
                heavy[b].push_back(i); 
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < All[i].size(); j++)
            for (int k = 0; k < heavy[i].size(); k++)
                cnt[All[i][j]][id[heavy[i][k]]]++;
    // char op[4];
    int op;
    int x, y;
    while (q--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf ("%d", &x);
            if (isheavy[x])
            {
                long long ans = Sum[id[x]];
                for (int i = 1; i <= t; i++) ans += cnt[x][i] * Add[i];
                printf ("%lld\n", ans);
                continue;
            }
            else
            {
                long long ans = 0;
                for (int i = 0; i < v[x].size(); i++)
                    ans += a[v[x][i]];
                for (int i = 1; i <= t; i++)
                    ans += cnt[x][i] * Add[i];
                printf("%lld\n", ans);
                continue;
            }
        }
        else
        {
            scanf("%d%d", &x, &y);
            if (isheavy[x])
                Add[id[x]] += y;
            else
            {
                for (int i = 0; i < v[x].size(); i++)
                    a[v[x][i]] += y;
                for (int i = 1; i <= t; i++)
                    Sum[i] += cnt[x][i] * y;
            }
        }
    }
    // while (1);
}
/*
5 3 5
5 -5 5 1 -4
2 1 2
4 2 1 4 5
2 2 5
1 2
2 3 4
1 1
2 2 1
1 2
*/