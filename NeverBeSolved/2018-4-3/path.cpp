#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline void gmax(int &a, int b) { if (a < b) a = b; }
inline void gmin(int &a, int b) { if (a > b) a = b; }
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 1005;
int nxt[MAXN][MAXN];
int Color[MAXN];
vector<int> Nc[50];
vector<int> now;
int main()
{
    // freopen ("path.in", "r", stdin);
    // freopen ("path.out", "w", stdout);
    int n = read(), m = read();
    int ct = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        Color[i] = read();
        gmax(ct, Color[i]);
        Nc[Color[i]].push_back(i);
    }
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        if (!nxt[a][b])
            nxt[a][b] = c;
        else
            gmin(nxt[a][b], c);
    }
    int N = (1 << ct) - 1;
    int ans = 0x3f3f3f3f;
    for (int S = 0; S <= N; S++)
    {
        now.clear();
        now.push_back(0);
        now.push_back(n);
        for (int i = 1; i <= ct; i++)
            if (S & (1 << (i - 1)))
                for (int j = 0; j < Nc[i].size(); j++)
                    now.push_back(Nc[i][j]);
        sort(now.begin(), now.end());
        bool flag = 0;
        int tmp = 0;
        for (int i = 0; i < now.size() - 1; i++)
        {
            if (!nxt[now[i]][now[i + 1]])
            {
                flag = 1;
                break;
            }
            else
                tmp += nxt[now[i]][now[i + 1]];
        }
        if (!flag)
            gmin(ans, tmp);
    }
    if (ans < 0x3f3f3f3f) printf ("%d\n", ans);
    else printf ("-1\n");
    // else printf ("-1\n");
}