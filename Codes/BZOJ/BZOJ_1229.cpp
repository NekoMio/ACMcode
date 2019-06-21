#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
int Tc, N1, N2, C1, C2, n;
int a[100005];
deque<pair<int, int> > Q;
int Calc(int x)
{
    Q.clear();
    int ans = x * Tc;
    Q.push_front(pair<int, int>(-N2, x));
    for (int i = 1; i <= n; i++)
    {
        if (i - N1 > 0)
            Q.push_front(pair<int, int>(i - N1, a[i - N1]));
        int T = a[i];
        while (T)
        {
            if (Q.empty())  return 0x3f3f3f3f;
            pair<int, int> tmp = Q.back();
            if (tmp.first + N2 <= i && C1 > C2)
            {
                int o = min(T, tmp.second);
                T -= o;
                tmp.second -= o;
                if(tmp.first != -N2)
                    ans += o * C2;
                Q.pop_back();
                if (tmp.second) Q.push_back(tmp); 
            }
            else
            {
                tmp = Q.front();
                int o = min(T, tmp.second);
                T -= o;
                tmp.second -= o;
                ans += o * C1;
                Q.pop_front();
                if (tmp.second) Q.push_front(tmp);
            }
        }
    }
    return ans;
}
int main()
{
    scanf ("%d%d%d%d%d%d", &n, &N1, &N2, &C1, &C2, &Tc);
    if (N1 > N2)
        swap(N1, N2), swap(C1, C2);
    int r = 0, l = 0;
    for (int i = 1; i <= n; i++)
        scanf ("%d", &a[i]), r += a[i];
    while (l + 2 < r)
    {
        int x = l + (r - l) / 3, y = l + 2 * (r - l) / 3;
        int fx = Calc(x), fy = Calc(y);
        if (fx < fy)
            r = y;
        else
            l = x; 
    }
    int ans = 0x3f3f3f3f;
    for (int i = l; i <= r; i++)
        ans = min(ans, Calc(i));
    printf("%d", ans);
}