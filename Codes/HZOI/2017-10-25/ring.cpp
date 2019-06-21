#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1048580;
bool vis[MAXN];
int main()
{
    // freopen("ring.in", "r", stdin);
    // freopen("ring.out", "w", stdout);
    int n;
    scanf ("%d", &n);
    int N = 1 << n;
    int now = 0;
    vis[now] = 1;
    for (int i = 1; i <= n; i++) printf ("0");
    for (int i = n + 1; i <= N; i++)
    {
        now = (now << 1) % N;
        if (!vis[now | 1]) vis[now | 1] = 1, now++, printf("1"); 
        else vis[now] = 1, printf ("0");
    }
    while (1);
    return 0;
}
