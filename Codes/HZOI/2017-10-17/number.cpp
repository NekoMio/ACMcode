#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define int long long
const int MAXN = 293;
int k;
long long m;
int prime[MAXN], isnprime[MAXN + 1], cnt;
void Get_prime()
{
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isnprime[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAXN) break;
            isnprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
int Max[MAXN];
vector<pair<int, int> > Update(vector<pair<int, int> > a, int p)
{
    vector<pair<int, int> > ans;
    ans.clear();
    for (int i = 0; i < a.size(); i++)
    {
        int tot = 1;
        long long P = 1;
        while (m / P >= a[i].first)
        {
            ans.push_back(pair<int, int>(a[i].first * P, a[i].second * tot));
            P *= p, tot++;
        }
    }
    sort(ans.begin(), ans.end());
    unique(ans.begin(), ans.end());
    return ans;
}
void Update(int x)
{
    int now = k;
    while (now && Max[now - 1] < x) now--;
    for (int i = k; i > now; i--) Max[i] = Max[i - 1];
    Max[now] = x;
}
vector<pair<int, int> > change(vector<pair<int, int> > a)
{
    memset(Max, 0, sizeof (Max));
    vector<pair<int, int> > ans;
    ans.clear();
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].second >= Max[k])
        {
            Update(a[i].second);
            ans.push_back(a[i]);
        }
    }
    return ans;
}
vector<pair<int, int> > Ans;
void Get_ans()
{
    Ans.push_back(pair<int,int>(1, 1));
    for (int i = 1; i <= cnt; i++)
    {
        Ans = Update(Ans, prime[i]);
        Ans = change(Ans);
        // for (int i = 0; i < Ans.size(); i++)
            // printf ("%lld ", Ans[i].first);
        // printf ("\n");
    }
}
signed main()
{
    long long n;
    int t;
    Get_prime();
    scanf ("%lld%lld%lld", &t, &k, &m);
    Get_ans();
    while (t--)
    {
        scanf ("%lld", &n);
        printf ("%lld\n", Ans[n - 1].first);
    }
    // while (1);
}