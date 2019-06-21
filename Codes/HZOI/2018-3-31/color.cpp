#ifdef ONLINE_JUDGE
#pragma GCC diagnostic error "-std=c++11"
#endif // ONLINE_JUDGE
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
struct Graph
{
    struct edge
    {
        int END, next;
    }v[MAXN];
    int fa[MAXN];
    int first[MAXN], p;
    Graph()
    {
        memset (first, -1, sizeof (first));
    }
    void add(int a, int b)
    {
        v[p].END = b;
        v[p].next = first[a];
        first[a] = p++;
    }
    int dfn[MAXN], low[MAXN], Index;
    stack<int> st;
    int belong[MAXN], T, size[MAXN];
    bool vis[MAXN];
    void tarjan(int rt)
    {
        low[rt] = dfn[rt] = ++Index;
        st.push(rt);
        vis[rt] = 1;
        for (int i = first[rt]; i != -1; i = v[i].next)
        {
            if (!dfn[v[i].END])
            {
                tarjan(v[i].END);
                low[rt] = min(low[rt], low[v[i].END]);
            }
            else if (vis[v[i].END])
                low[rt] = min(low[rt], dfn[v[i].END]);
        }
        if (low[rt] == dfn[rt])
        {
            T++;
            int x;
            do
            {
                size[T]++;
                x = st.top();
                st.pop();
                belong[x] = T;
                vis[x] = 0;
            }
            while (dfn[x] != low[x]);
        }
    }
    int Circle;
    vector<int> C;
    bool test(int x)
    {
        return belong[x] == Circle;
    }
}G;
struct Math_data
{
    long long pow_mod(long long a, int b)
    {
        long long ans = 1;
        while (b)
        {
            if (b & 1) ans = ans * a % MOD;
            b >>= 1;
            a = a * a % MOD;
        }
        return ans;
    }
    int F[MAXN], Inv[MAXN];
    Math_data()
    {
        F[0] = 1;
        for (int i = 1; i < MAXN; i++) F[i] = 1ll * F[i - 1] * i % MOD;
        Inv[MAXN - 1] = pow_mod(F[MAXN - 1], MOD - 2);
        for (int i = MAXN - 2; i >= 0; i--) Inv[i] = 1ll * Inv[i + 1] * (i + 1) % MOD;
    }
    int C(int n, int m)
    {
        int ans = Inv[m];
        for (int i = 1; i <= m; i++)
            ans = 1ll * ans * (n - i + 1) % MOD;
        return ans; 
    }
    int phi(int x)
    {
        int ans = x;
        for (int i = 2; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                while (x % i == 0) x /= i;
                ans = ans - ans / i;
            }
        }
        if (x != 1) ans = ans - ans / x;
        return ans;
    }
}Math;
struct Tree_DP
{
    int size[MAXN], m;
    unsigned int Hash[MAXN];
    struct Hash_Table
    {
        struct edge
        {
            int ans, next;
            unsigned int x;
        }v[MAXN];
        int first[76545], p;
        Hash_Table()
        {
            memset (first, -1, sizeof (first));
        }
        int &operator[](unsigned int x)
        {
            int H = x % 76543;
            for (int i = first[H]; i != -1; i = v[i].next)
                if (v[i].x == x)
                    return v[i].ans;
            v[p].x = x;
            v[p].next = first[H];
            first[H] = p++;
            return v[p - 1].ans = 0;
        }
        bool count(unsigned int x)
        {
            int H = x % 76543;
            for (int i = first[H]; i != -1; i = v[i].next)
                if (v[i].x == x)
                    return 1;
            return 0;
        }
    }mp;
    void DFS(int rt, int fa)
    {
        vector<int> vc;
        size[rt] = 1;
        int du = 0;
        for (int i = G.first[rt]; i != -1; i = G.v[i].next)
        {
            if (G.v[i].END == fa || G.test(G.v[i].END)) continue;
            DFS(G.v[i].END, rt);
            du++;
            size[rt] += size[G.v[i].END];
            vc.push_back(Hash[G.v[i].END]);
        }
        Hash[rt] = 1u * du * size[rt] * 31;
        sort(vc.begin(), vc.end());
        for (auto z : vc) Hash[rt] = (Hash[rt] * 2 + ((z * 998244353 + z * 131) ^ (z * 23333)));
        if (mp.count(Hash[rt])) return;
        int &ans = mp[Hash[rt]];
        ans = m;
        int cnt = 0;
        for (int i = 0; i < du; i++)
        {
            cnt++;
            if (i == du - 1 || vc[i] != vc[i + 1])
                ans = (1ll * ans * Math.C(cnt + mp[vc[i]] - 1, cnt)) % MOD, cnt = 0;
        }
    }
}DP;
struct BurnSide
{
    unsigned int H[MAXN];
    int S[MAXN], cnt, fail[MAXN];
    void add(unsigned int x, int y)
    {
        H[++cnt] = x, S[cnt] = y;
    }
    void Get_Next()
    {
        fail[0] = 0;
        fail[1] = 0;
        int j = 0;
        for (int i = 2; i <= cnt; i++)
        {
            while (j && H[j + 1] != H[i])
                j = fail[j];
            if (H[j + 1] == H[i])
                j++;
            fail[i] = j;
        }
    }
    int Calc()
    {
        for (int i = 2; i <= cnt; i++)
            S[i] = (1ll * S[i] * S[i - 1]) % MOD;
        Get_Next();
        int ans = 0, All = 0;
        for (int i = cnt; i * 2 >= cnt; i = fail[i])
        {
            int t = cnt - i;
            if (t == 0)
            {
                ans = S[cnt];
                All++;
            }
            else if (cnt % t == 0)
            {
                int tmp = Math.phi(cnt / t);
                All += tmp;
                ans = (ans + 1ll * S[t] * tmp % MOD) % MOD;
            }
        }
        return (int)(1ll * ans * Math.pow_mod(All, MOD - 2) % MOD);
    }
}BS;
int main()
{
    // freopen ("color11.in", "r", stdin);
    // freopen ("color11.out", "w", stdout);
    int n = read();
    DP.m = read();
    for (int i = 1; i <= n; i++)
    {
        G.fa[i] = read();
        G.add(G.fa[i], i);
    }
    for (int i = 1; i <= n; i++)
        if (!G.dfn[i])
            G.tarjan(i);
    for (int i = 1; i <= G.T; i++)
    {
        if (G.size[i] > 1)
        {
            G.Circle = i;
            for (int j = 1; j <= n; j++)
                if (G.belong[j] == i)
                    G.C.push_back(j);
            break;
        }
    }
    bool *vis = new bool[MAXN];
    memset (vis, 0, sizeof (vis[0]) * MAXN);
    for (int x = G.C[0]; !vis[x]; x = G.fa[x])
    {
        vis[x] = 1;
        DP.DFS(x, 0);
        BS.add(DP.Hash[x], DP.mp[DP.Hash[x]]);
        // printf ("%d %d\n", x, DP.mp[DP.Hash[x]]);
    }
    printf ("%d\n", BS.Calc());
}