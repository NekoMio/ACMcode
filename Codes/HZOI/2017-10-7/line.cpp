#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int t = 0;
bool Judge(char *s)
{
    int now = 1;
    while (s[now] == 'G') now++;
    return now - 1 == t;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("line.in", "r", stdin);
    freopen("line.out", "w", stdout);
#endif
    static char s[1000005];
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    if (n <= 10000)
    {
        for (int i = 1; i <= n; i++)
            if (s[i] == 'G') 
                t++;
        int ans = 0;
        while (!Judge(s))
        {
            for (int i = 1; i < n; i++)
                if (s[i] == 'B' && s[i + 1] == 'G') swap(s[i], s[i + 1]), i++;
            ans++;
        }
        printf("%d", ans);
        getchar(), getchar();
    }
    else
    {
        int h = 0, e = 0, ans = 0;
        for (int i = n; i >= 1; i--)
        {
            if (s[i] == 'G')
            {
                if (h) h--;
            }
            else
            {
                ++e;
                ans = max(ans, n - e + 1 - i + (n - e + 1 == i ? 0 : h++));
            }
        }
        printf("%d", ans);
    }
    return 0;
}