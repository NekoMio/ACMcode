#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
struct data
{
    int t, l, r;
};
int cnt[16];
int backcnt[16];
vector<data> s;
int times[5];
int Query()
{
    memcpy(backcnt, cnt, sizeof(backcnt));
    memset(times, 0, sizeof(times));
    // int ans = s.size();
    // for (int i = 0; i < s.size(); i++)
    // {
    //     for (int j = s[i].l; j <= s[i].r; j++)
    //         backcnt[j] -= s[i].t;
    // }
    int ans = 0;
    for (int i = 1; i <= 14; i++)
    {
        times[backcnt[i]]++;
    }
    while (times[4] > 0 && times[2] > 1)
    {
        times[4]--;
        times[2] -= 2;
        ans++;
    }
    while (times[4] > 0 && times[1] > 1)
    {
        times[4]--;
        times[1] -= 2;
        ans++;
    }
    while (times[4] > 0 && times[2] > 0)
    {
        times[4]--;
        times[2]--;
        ans++;
    }
    while (times[3] > 0 && times[2] > 0)
    {
        times[3]--;
        times[2]--;
        ans++;
    }
    while (times[3] > 0 && times[1] > 0)
    {
        times[3]--;
        times[1]--;
        ans++;
    }
    while (times[4] > 0)
    {
        times[4]--;
        ans++;
    }
    while (times[3] > 0)
    {
        times[3]--;
        ans++;
    }
    while (times[2] > 0)
    {
        times[2]--;
        ans++;
    }
    while (times[1] > 0)
    {
        times[1]--;
        ans++;
    }
    return ans;
}
int DFS()
{
    //int ans = 0x3f3f3f3f;
    int ans = Query();
    for (int i = 1; i <= 12; i++)
    {
        if (cnt[i])
        {
            for (int j = i + 1; j <= 12; j++)
            {
                if (!cnt[j])
                    break;
                if (j - i + 1 >= 5)
                {
                    //s.push_back((data){1, i, j});
                    for (int k = i; k <= j; k++)
                        cnt[k] -= 1;
                    ans = min(ans, DFS()+1);
                    for (int k = i; k <= j; k++)
                        cnt[k] += 1;
                    //ans = min(ans, Query(1));
                    //s.pop_back();
                }
            }
        }
        if (cnt[i] >= 2)
        {
            for (int j = i + 1; j <= 12; j++)
            {
                if (cnt[j] < 2)
                    break;
                if (j - i + 1 >= 3)
                {
                    for (int k = i; k <= j; k++)
                        cnt[k] -= 2;
                    ans = min(ans, DFS()+1);
                    for (int k = i; k <= j; k++)
                        cnt[k] += 2;
                    // s.push_back((data){2, i, j});
                    // ans = min(ans, DFS(j + 1));
                    // ans = min(ans, Query(1));
                    // s.pop_back();
                }
            }
        }
        if (cnt[i] >= 3)
        {
            for (int j = i + 1; j <= 12; j++)
            {
                if (cnt[j] < 3)
                    break;
                if (j - i + 1 >= 2)
                {
                    for (int k = i; k <= j; k++)
                        cnt[k] -= 3;
                    ans = min(ans, DFS()+1);
                    for (int k = i; k <= j; k++)
                        cnt[k] += 3;
                    // s.push_back((data){3, i, j});
                    // ans = min(ans, DFS(j + 1));
                    // ans = min(ans, Query(1));
                    // s.pop_back();
                }
            }
        }
    }
    //ans = min(ans, Query(1));
    return ans;
}
int main(int argc, char const *argv[])
{
    freopen("landlords.in", "r", stdin);
    freopen("landlords.out", "w", stdout);
    int T, n;
    //int C = 1;
    scanf("%d%d", &T, &n);
    while (T--)
    {
        int a, b;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &a, &b);
            if (a)
                if ((a + 11) % 13)
                    cnt[(a + 11) % 13]++;
                else
                    cnt[13]++;
            else
                cnt[14]++;
        }
        s.clear();
        printf("%d\n", DFS());
    }

    return 0;
}
