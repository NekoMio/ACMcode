#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MAXN = 1000005;
char s[MAXN << 1];
int NumB, NumR;
int Get_ans(int n, int N)
{
    int ans = 0, Sum = 0, LB = 0, LR = 0, RB = 0, RR = 0, mid = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 'B') LB++, Sum += LR;
        else LR++;
        if (LR * 2 > NumR)
        {
            mid = i + 1;
            break;
        } 
    }
    for (int i = n; i >= mid; i--)
    {
        if (s[i] == 'B') RB++, Sum += RR;
        else RR++;
    }
    ans = Sum;
    for (int i = n + 1; i <= N; i++)
    {
        if (s[i] == 'B')
        {
            LB--;
            RB++;
        }
        else
        {
            LR--;
            RR++;
            Sum = Sum - LB + RB;
            while (LR * 2 <= NumR)
            {
                if (s[mid] == 'B') Sum = Sum - RR + LR, ++LB, --RB;
                else ++LR, --RR;
                mid++;
            }
            ans = min(ans, Sum);
        }
    }
    return ans;
}
signed main()
{
    int T;
    scanf ("%lld", &T);
    while (T--)
    {
        scanf ("%s", s + 1);
        int n = strlen(s + 1);
        NumB = NumR = 0;
        for (int i = 1; i <= n; i++)
        {
            if (s[n + i] = s[i])
            if (s[i] == 'B') NumB++;
            if (s[i] == 'R') NumR++;
        }
        printf ("%lld\n", Get_ans(n, 2 * n));
    }
    // while (1);
}