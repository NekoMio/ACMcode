#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 5e6 + 2;
char s[N];
int S[N << 1][3];
#define Num(_,__) S[_ + 5000000][__]
int Sum[N][3];
int main()
{
    int n;
    scanf ("%d", &n);
    scanf ("%s", s + 1);
    int now[3];
    int sum[3];
    now[0] = 0, now[1] = 0, now[2] = 0;
    sum[0] = 0, sum[1] = 0, sum[2] = 0;
    long long ans = 1ll * n * (n + 1) / 2;
    Num(0, 0) = 1, Num(0, 1) = 1, Num(0, 2) = 1;
    for (int i = 1; i <= n; i++)
    {
        sum[s[i] - '0'] += Num(now[s[i] - '0']++, s[i] - '0');
        sum[(s[i] - '0' + 1) % 3] -= Num(--now[(s[i] - '0' + 1) % 3], (s[i] - '0' + 1) % 3);
        sum[(s[i] - '0' + 2) % 3] -= Num(--now[(s[i] - '0' + 2) % 3], (s[i] - '0' + 2) % 3);
        ans -= sum[1] + sum[2] + sum[0];
        Num(now[1], 1)++, Num(now[0], 0)++, Num(now[2], 2)++;
    }
    printf ("%lld", ans);
    
}