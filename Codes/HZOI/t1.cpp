// #pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
// #include <ctime>
using namespace std;
inline long long read()
{
    long long x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 998244353;
long long Num[1000000];
int v[1000000], cnt;

long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}
struct Hash_Table
{
    struct edge
    {
        int next, ans;
        long long x;
    }v[1000000];
    int first[76545], p;
    Hash_Table()
    {
        memset (first, -1, sizeof (first));
    }
    int &operator[](long long x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return v[i].ans;
        v[p].x = x;
        v[p].next = first[H];
        first[H] = p++;
        return v[p - 1].ans;
    }
    bool count(long long x)
    {
        int H = x % 76543;
        for (int i = first[H]; i != -1; i = v[i].next)
            if (v[i].x == x)
                return 1;
        return 0;
    }
}Hash;
void DFS(int d, int last, long long num)
{
    if (num == 0) return;
    if (d == 0) 
    {
        if (!Hash.count(num)) Hash[num] = ++cnt, Num[cnt] = num;
        return;
    }
    for (int i = last; i <= 9; i++)
        DFS(d - 1, i, num * i);
}
long long f[21][2][2][40000];
int strlen(int n)
{
    int ans = 0;
    while (n) ans++, n /= 10;
    return ans;
}
int id[40000];
int main()
{
    long long n = read();
    long long k = read();
    int a[22] = {0}, len = 0;
    while (n) a[++len] = n % 10, n /= 10;
    DFS(len, 0, 1);
    reverse(a + 1, a + len + 1);
    for (int i = 1; i <= a[1]; i++)
        f[1][i == a[1]][0][Hash[i]] = 1;
    sort(Num + 1, Num + cnt + 1);
    for (int i = 1; i <= cnt; i++)
        Hash[Num[i]] = i;
    f[1][0][1][0] = 1;
    for (int i = 1; i < len; i++)
    {
        f[i + 1][0][1][0] = 1;
        for (int j = 1; j <= 9; j++)
            f[i + 1][0][0][Hash[j]] = 1;
        for (int k = 1; k <= cnt; k++)
        {
            for (int j = 1; j <= 9; j++)
                f[i + 1][0][0][Hash[j * Num[k]]] = (f[i + 1][0][0][Hash[j * Num[k]]] + f[i][0][0][k]) % MOD;
            for (int j = 1; j <= a[i + 1]; j++)
                f[i + 1][j == a[i + 1]][0][Hash[j * Num[k]]] = (f[i + 1][j == a[i + 1]][0][Hash[j * Num[k]]] + f[i][1][0][k]) % MOD;
        }
    }
    for (int i = 1; i <= cnt; i++)
        f[len][0][0][i] = (f[len][1][0][i] + f[len][0][0][i]) % MOD;
    //for (int i = 1; i <= cnt; i++)
    //    printf ("%lld = %lld\n", Num[i], f[len][0][0][i]);
    long long ans = 0;
    long long Sum = 0;
    int t = cnt + 1, tot = 0;
    for (int i = 1; i <= cnt; i++)
    {
        if (f[len][0][0][i])
        {
            id[++tot] = i;
            if (Num[i] <= k)
                Sum = (Sum + f[len][0][0][i]) % MOD;
            else if (t == cnt + 1) t = tot;
        }
    }
    long long Tot = Sum;
    //printf ("%lld\n", Sum);
    ans = 0;
    for (int i = t; i <= tot; i++)
    {
        Tot = (f[len][0][0][id[i]] + Tot) % MOD;
        for (int j = t; j <= tot; j++)
            if (gcd(Num[id[i]], Num[id[j]]) <= k)
                ans = (ans + f[len][0][0][id[i]] * f[len][0][0][id[j]] % MOD) % MOD;
    }
    ans = (ans + 2 * Tot * Sum % MOD) % MOD;
    ans = ((ans - Sum * Sum % MOD) % MOD + MOD) % MOD;
    printf ("%lld\n", ans);
}
