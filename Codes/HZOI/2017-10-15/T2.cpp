#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
#define ULL unsigned long long
map<ULL, int> mp;
int cnt;
const int MOD = 1000000007;
ULL Hash(char *s)
{
    const static ULL base = 31;
    ULL ans = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        ans = ans * base + s[i];
    return ans;
}
char A[100], B[100];
int rudu[50005], cudu[50005];
struct edge
{
    int END, next;
}v[200005];
int first[50005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
long long f[50005];
int main()
{
    memset(first, -1, sizeof(first));
    int m;
    scanf ("%d", &m);
    int a, b;
    ULL Ha,Hb;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%s%s", A, B);
        Ha = Hash(A), Hb = Hash(B);
        if(!mp.count(Ha)) mp[Ha] = ++cnt;
        if(!mp.count(Hb)) mp[Hb] = ++cnt;
        a = mp[Ha], b = mp[Hb];
        add(a, b);
        rudu[b]++, cudu[a]++;
    }
    queue<int> Q;
    for (int i = 1; i <= cnt; i++)
        if (rudu[i] == 0)
            Q.push(i), f[i] = 1;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            f[v[i].END] = (f[v[i].END] + f[k]) % MOD;
            rudu[v[i].END]--;
            if (rudu[v[i].END] == 0)
            {
                Q.push(v[i].END);
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= cnt; i++)
        if (cudu[i] == 0)
            ans = (ans + f[i]) % MOD;
    printf ("%lld", ans);
}