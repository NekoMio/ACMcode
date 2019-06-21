#include <cstdio>
#include <algorithm>
#include <cstring>
#include <deque>
using namespace std;
int a[100005], l[100005], r[100005];
int Hash[200005];
template<typename _Tp>
inline _Tp read()
{
    _Tp a = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -f; ch = getchar();}
    while (ch >= '0' && ch <= '9') {a = a * 10 + ch - 48; ch = getchar();}
    return a * f;
}
struct data
{
    int type, v;
}Query[100005];
long long Sum[200005];
int cnt;
#define lowbit(_) ((_) & (-_))
void add(int x, long long c)
{
    for (int i = x; i <= cnt; i += lowbit(i))
        Sum[i] += c;
}
long long Query_Sum(int x)
{
    long long ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += Sum[i];
    return ans;
}
long long Calc(int i)
{
    long long L = i - l[i] + 1;
    long long R = r[i] - i + 1;
    return L * R;
}
int main()
{
    int n = read<int>();
    int q = read<int>();
    for (int i = 1; i <= n; i++)
        Hash[i] = a[i] = read<int>();
    char s[5];
    for (int i = 1; i <= q; i++)
    {
        scanf ("%s", s);
        if (s[0] == '>') Query[i].type = 1;
        else if (s[0] == '=') Query[i].type = 2;
        else if (s[0] == '<') Query[i].type = 3;
        Hash[i + n] = Query[i].v = read<int>();
    }
    sort(Hash + 1, Hash + n + q + 1);
    cnt = unique(Hash + 1, Hash + n + q + 1) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + cnt + 1, a[i]) - Hash;
    deque<pair<int, int> > Q;
    for (int i = 1; i <= n; i++) l[i] = r[i] = i;
    for (int i = 1; i <= n; i++)
    {
        pair<int, int> k(a[i], i);
        while (!Q.empty() && a[i] >= Q.back().first)
        {
            k = Q.back();
            Q.pop_back();
        }
        if (Q.empty()) l[i] = 1;
        else l[i] = l[k.second];
        Q.push_back(pair<int, int>(a[i], i));
    }
    Q.clear();
    for (int i = n; i >= 1; i--)
    {
        pair<int, int> k(a[i], i);
        while (!Q.empty() && a[i] > Q.back().first)
        {
            k = Q.back();
            Q.pop_back();
        }
        if(Q.empty()) r[i] = n;
        else r[i] = r[k.second];
        Q.push_back(pair<int, int>(a[i], i));
    }
    for (int i = 1; i <= n; i++)
        add(a[i], Calc(i));
    for (int i = 1; i <= q; i++)
    {
        Query[i].v = lower_bound(Hash + 1, Hash + cnt + 1, Query[i].v) - Hash;
        if (Query[i].type == 1)
        {
            printf ("%lld\n", Query_Sum(cnt) - Query_Sum(Query[i].v));
        }
        else if (Query[i].type == 2)
        {
            printf ("%lld\n", Query_Sum(Query[i].v) - Query_Sum(Query[i].v - 1));
        }
        else
            printf ("%lld\n", Query_Sum(Query[i].v - 1));
    }
    // while (1);
}