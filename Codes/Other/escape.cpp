#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int map[1005][1005];
int x1,y_1,x2,y2,n,m;
struct Point
{
    int x,y;
    Point(int a=0,int b=0)
    {
        x=a,y=b;
    }
};
int dx[4] = {0,0,-1,1},
    dy[4] = {1,-1,0,0};
bool flag[1005][1005];
void bfs()
{
    memset(flag,0,sizeof(flag));
    queue<Point> Q;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(!map[i][j])
            {
                Q.push(Point(i,j));
                flag[i][j] = 1;
            }
    while(!Q.empty())
    {
        Point k = Q.front();
        Q.pop();
        flag[k.x][k.y] = 0;
        for(int i = 0; i <= 3; i++)
        {
            Point now(k.x+dx[i],k.y+dy[i]);
            if(now.x<=0||now.x>n)continue;
            if(now.y<=0||now.y>m)continue;
            if(map[now.x][now.y] > map[k.x][k.y] + 1)
            {
                map[now.x][now.y] = map[k.x][k.y] + 1;
                if(!flag[now.x][now.y])
                {
                    Q.push(now);
                    flag[now.x][now.y] = 1;
                }
            }
        }
    }
}
int dis[1005][1005];
bool spfa(int t)
{
    memset(flag,0,sizeof(flag));
    memset(dis,0x3f,sizeof(dis));
    queue<Point> Q;
    Q.push(Point(x1,y_1));
    if(map[x1][y_1] < t)return 0;
    flag[x1][y_1] = 1;
    dis[x1][y_1] = 0;
    while(!Q.empty())
    {
        Point k = Q.front();
        Q.pop();
        flag[k.x][k.y] = 0;
        for(int i = 0; i <= 3; i++)
        {
            Point now(k.x+dx[i],k.y+dy[i]);
            if(now.x<=0||now.x>n)continue;
            if(now.y<=0||now.y>m)continue;
            if(map[now.x][now.y]<t)continue;
            if(dis[now.x][now.y] > dis[k.x][k.y] + 1)
            {
                dis[now.x][now.y] = dis[k.x][k.y] + 1;
                if(!flag[now.x][now.y])
                {
                    Q.push(now);
                    flag[now.x][now.y] = 1;
                }
            }
        }
    }
    return dis[x2][y2] != 0x3f3f3f3f;
}
int main()
{
    //freopen("1.in","r",stdin);
    int e;
    memset(map,0x3f,sizeof(map));
    scanf("%d%d%d",&e,&n,&m);
    scanf("%d%d%d%d",&x1,&y_1,&x2,&y2);
    x1++,x2++,y_1++,y2++;
    int a,b;
    for(int i = 1; i <= e; i++)
    {
        scanf("%d%d",&a,&b);
        map[a+1][b+1] = 0;
    }
    bfs();
    int l = 0,r = 2005;
    int len = 0,ans = 0;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(spfa(mid))
        {
            l = mid + 1;
            len = mid;
            ans = dis[x2][y2];
        }
        else
            r = mid;
    }
    printf("%d %d\n",len,ans);
}