#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct edge
{
    int END, next;
}v[40005];
int first[205],p;
void add(int a,int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int link[205];
bool vis[205];
int find(int x)
{
    for (int i = first[x]; i != -1; i = v[i].next)
    {
        if(!vis[v[i].END])
        {
            vis[v[i].END] = 1;
            if(link[v[i].END]==-1||find(link[v[i].END]))
            {
                link[v[i].END] = x;
                return 1; 
            }
        }
    }
    return 0;
}
int main()
{
    int T, a;
    scanf("%d", &T);
    while (T--)
    {
        memset(first, -1, sizeof(first));
        p = 0;
        memset(link, -1, sizeof(link));
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &a);
                if (a)
                    add(i, j);
            }
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            memset(vis, 0, sizeof(vis));
            if (find(i))
                ans++;
        }
        if(ans == n)
            printf("Yes\n");
        else
            printf("No\n");
    }
}