#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef pair<int, int> pii;
typedef set<int>::iterator it;
int n, fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
set<int> S[N], T[N];
queue<pii> Q;
void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        S[i].clear();
        T[i].clear();
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        S[u].insert(v);
        S[v].insert(u);
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (S[u].count(v))
        {
            Q.push(pii(u, v));
            S[u].erase(v);
            S[v].erase(u);
        }
        else
        {
            T[u].insert(v);
            T[v].insert(u);
        }
    }
    int cnt = 0;
    while (!Q.empty())
    {
        int u = Q.front().first, v = Q.front().second;
        Q.pop();
        u = find(u);
        v = find(v);
        cnt++;
        if (S[u].size() + T[u].size() < S[v].size() + T[v].size())
            swap(u, v);
        fa[v] = u;
        for (it i = S[v].begin(); i != S[v].end(); ++i)
        {
            int x = *i;
            S[x].erase(v);
            if (T[u].count(x))
            {
                Q.push(pii(u, x));
                T[u].erase(x);
                T[x].erase(u);
            }
            else
            {
                S[x].insert(u);
                S[u].insert(x);
            }
        }
        S[v].clear();
        for (it i = T[v].begin(); i != T[v].end(); ++i)
        {
            int x = *i;
            T[x].erase(v);
            if (S[u].count(x))
            {
                Q.push(pii(u, x));
                S[u].erase(x);
                S[x].erase(u);
            }
            else
            {
                T[u].insert(x);
                T[x].insert(u);
            }
        }
        T[v].clear();
    }
    puts(cnt == n - 1 ? "YES" : "NO");
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
