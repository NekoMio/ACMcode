#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
set<pair<int, int> > st;
const int MAXN = 2e5 + 5;
const int MAXM = 4000005;
int a[MAXN], n, pre, suf;
long long S[MAXN], S1[MAXN];
bool vis[MAXN];
const int MOD = 1e9 + 7;
pair<int, int> b[MAXN];
long long ans = 0;
long long Sum(long long x)
{
    return (x * (x + 1) / 2) % MOD;
}
void Erase(pair<int, int> x)
{
    st.erase(x);
    if (x.first == 1 || x.second == n) return;
    ans = (ans - S[x.second - x.first + 1] + MOD) % MOD;
}
void Insert(pair<int, int> x)
{
    st.insert(x);
    if (x.first == 1 || x.second == n) return;
    ans = (ans + S[x.second - x.first + 1]) % MOD;
}
long long Calc(int pre, int suf)
{
    if (!pre && !suf) return 0;
    if (!pre) return S[suf];
    if (!suf) return S[pre];
    pre--;
    if (pre == 0) return (S[suf] + 1) % MOD;
    return (((S[max(suf, pre) - min(suf, pre)] + Sum(pre + 1)) % MOD + S1[suf + pre]) % MOD - S1[max(suf, pre) - min(suf, pre)] + MOD) % MOD;
}
int main()
{
    // freopen ("a1.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= n; i++) S[i] = (S[i - 1] + Sum(i)) % MOD;
    S1[0] = 0, S1[1] = Sum(1);
    for (int i = 2; i <= n; i++) S1[i] = (S1[i - 2] + Sum(i)) % MOD;
    for (int i = 1; i <= n; i++) b[i] = pair<int, int>(a[i], i);
    sort(b + 1, b + n + 1);
    int last = 0;
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int pos = b[i].second;
        vis[pos] = 1;
        ans = (ans - Calc(pre, suf) + MOD) % MOD;
        // printf ("%lld\n", ans);
        while (vis[pre + 1]) pre++;
        while (vis[n - suf]) suf++;
        ans = (ans + Calc(pre, suf)) % MOD;
        // printf ("%lld\n", ans);
        set<pair<int,int> >::iterator it = st.insert(pair<int, int>(pos, pos)).first, it1 = it, it2 = it;
        it2++;
        int l = pos, r = pos;
        if (it2 != st.end() && it2->first == it->second + 1)
        {
            r = it2->second;
            Erase(*it2);
        }
        if (it != st.begin() && (--it1)->second + 1 == it->first)
        {
            l = it1->first;
            Erase(*it1);
        }
        st.erase(*it);
        Insert(pair<int, int>(l, r));
        if (b[i].first != b[i + 1].first && i != n)
            sum = (sum + 1ll * b[i].first * (ans - last + MOD) % MOD) % MOD, last = ans;
        // printf ("%lld %lld\n", ans, sum);
    }
    sum = (sum + 1ll * b[n].first * (Sum(Sum(n)) - last + MOD) % MOD) % MOD;
    printf ("%lld\n", sum);
}