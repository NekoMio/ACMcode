#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 1e5 + 5;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Tree
{
    long long dis[MAXN];
    struct edge
    {
        int next, END;
        long long v;
    }v[MAXN << 1];
    int first[MAXN], p;
    Tree()
    {
        memset (first, -1, sizeof (first));
        p = 0;
    }
    void add(int a, int b, long long c)
    {
        v[p].END = b;
        v[p].v = c;
        v[p].next = first[a];
        first[a] = p++;
    }
    void Read(int n)
    {
        for (int i = 1; i < n; i++)
        {
            int a = read(), b = read();
            long long w;
            scanf ("%lld", &w);
            add(a, b, w);
            add(b, a, w);
        }
    }
    void DFS(int rt, int fa, long long c)
    {
        dis[rt] = dis[fa] + c;
        for (int i = first[rt]; i != -1; i = v[i].next)
        {
            if (v[i].END == fa) continue;
            DFS(v[i].END, rt, v[i].v);
        }
    }
}A, B, C;
int main()
{
    int n = read();
    A.Read(n);
    B.Read(n);
    C.Read(n);
    int T = 30;
    long long Ans = 0;
    while (T--)
    {
        set<int> st;
        int root = rand() % n + 1;
        while (1)
        {
            if (st.find(root) != st.end())
                break;
            st.insert(root);
            A.DFS(root, 0, 0ll);
            B.DFS(root, 0, 0ll);
            C.DFS(root, 0, 0ll);
            long long tmp = 0;
            int nxt = 0;
            for (int i = 1; i <= n; i++)
            {
                long long vi = A.dis[i] + B.dis[i] + C.dis[i];
                if (vi > tmp) tmp = vi, nxt = i;
            }
            Ans = max(Ans, tmp);
            root = nxt;
        }
    }
    printf ("%lld\n", Ans);
    // while (1);
}