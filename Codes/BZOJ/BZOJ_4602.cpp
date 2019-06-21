#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
double eps = 1e-7;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge
{
    int END, next;
    double v;
}v[20010];
int first[1005], p;
void add(int a, int b, double c)
{
    v[p].END = b;
    v[p].next = first[a];
    v[p].v = c;
    first[a] = p++;
}
double dis[1005];
queue<int> Q;
int main()
{
    int T = read();
    int t = 0;
    while (T--)
    {
        int n = read(), m = read();
        for (int i = 1; i <= n; i++) dis[i] = 0;
        memset (first, -1, sizeof (first)), p = 0;
        for (int i = 1; i <= m; i++)
        {
            int a = read(), b = read(), c = read(), d = read();
            add(a, b, (double)d / c);
            add(b, a, (double)c / d);
        }
        dis[1] = 1;
        Q.push(1);
        while (!Q.empty())
        {
            int k = Q.front();
            Q.pop();
            for (int i = first[k]; i != -1; i = v[i].next)
            {
                if (!dis[v[i].END])
                {
                    dis[v[i].END] = dis[k] * v[i].v;
                    Q.push(v[i].END);
                }
                else if (abs(dis[v[i].END] - dis[k] * v[i].v) > eps)
                {
                    printf ("Case #%d: No\n", ++t);
                    goto end;
                }
            }
        }
        printf ("Case #%d: Yes\n", ++t);
        end:;
        while (!Q.empty()) Q.pop();
    }
}
