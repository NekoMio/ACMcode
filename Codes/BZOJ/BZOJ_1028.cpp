#include <cstdio>
#include <cstring>
#include <cstring>
using namespace std;
int cnt[405], now[405], n;
int ans[405];
bool Check()
{
    memcpy(now, cnt, sizeof(now));
    for (int i = 1; i <= n; i++)
        while (now[i])
        {
            if (now[i] >= 3) 
            {
                now[i] -= 3;
                continue;
            }
            if (i <= n - 2 && now[i + 1] && now[i + 2]) 
            {
                now[i]--;
                now[i + 1]--;
                now[i + 2]--;
                continue;
            }
            return 0;
        }
    return 1;
}
int main()
{
    int a, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= 3 * m + 1; i++)
        scanf ("%d", &a), cnt[a]++;
    for (int i = 1; i <= n; i++)
    {
        cnt[i]++;
        for (int j = 1; j <= n; j++)
        {
            if (cnt[j] >= 2)
            {
                cnt[j] -= 2;
                if (Check()) 
                {
                    ans[++ans[0]] = i;
                    cnt[j] += 2;
                    break;
                }
                cnt[j] += 2;
            }
        }
        cnt[i]--;
    }
    if (ans[0])
    {
        for (int i = 1; i <= ans[0]; i++)
            printf ("%d%c", ans[i], " \n"[i == ans[0]]);
    }
    else
        printf ("NO");
}