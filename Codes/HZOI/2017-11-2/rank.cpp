#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int Rank[2000005], n, sa[2000005];
char ans[2000005];
int main()
{
    // freopen("rank.in", "r", stdin);
    // freopen("rank.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        Rank[i] = read();
    for (int i = 1; i <= n; i++)
        sa[Rank[i]] = i;
    int cnt = 0;
    ans[sa[1]] = cnt + 'a';
    for (int i = 1; i <= n; i++)
    {
        if (Rank[sa[i] + 1] < Rank[sa[i + 1] + 1])
            ans[sa[i + 1]] = cnt + 'a';
        else
            ans[sa[i + 1]] = (++cnt) + 'a';
    }
    ans[n + 1] = '\0';
    if (cnt > 26) return puts("-1"), 0;
    printf ("%s", ans + 1);
    // else puts("-1");
    // DFS(0);
}