#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int Num[65537];
int main()
{
    int n, x;
    char s[5];
    scanf ("%d", &n);
    while (n--)
    {
        scanf ("%s%d", s, &x);
        if (s[0] == 'a') Num[x]++;
        else if (s[0] == 'd') Num[x]--;
        else
        {
            int ans = Num[0];
            for (int i = x; i; i = (i - 1) & x)
                ans += Num[i];
            printf ("%d\n", ans);
        }
    }
}
