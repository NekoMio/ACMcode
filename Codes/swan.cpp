#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool map[1505][1505];
int dis[1505][1505];
struct Point
{
    int x, y;
} S, E, Q[20000000];
int R, C;
int movex[5] = {0, 0, 0, 1, -1},
    movey[5] = {0, 1, -1, 0, 0};
bool flag[1505][1505];
void bfs_init()
{
    //memset(flag,0,sizeof(flag));
    int l = 1, r = 0;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (!map[i][j])
            {
                Q[++r] = (Point){i, j};
                dis[i][j] = 0;
            }
        }
    }
    while (l <= r)
    {
        Point k = Q[l++];
        for (int i = 1; i <= 4; i++)
        {
            if (k.x + movex[i] > R || k.x + movex[i] < 1)
                continue;
            if (k.y + movey[i] > C || k.y + movey[i] < 1)
                continue;
            if (dis[k.x + movex[i]][k.y + movey[i]] > dis[k.x][k.y] + 1)
            {
                dis[k.x + movex[i]][k.y + movey[i]] = dis[k.x][k.y] + 1;
                Q[++r] = (Point) { k.x + movex[i], k.y + movey[i] };
            }
        }
    }
}
int d[1505][1505];

int SPFA()
{
    memset(d, 0x3f, sizeof(d));
    d[S.x][S.y] = 0;
    int l = 1, r = 0;
    Q[++r] = S;
    //flag[S.x][S.y] = 1;
    while (l <= r)
    {
        Point k = Q[l++];
        //flag[k.x][k.y] = 0;
        for (int i = 1; i <= 4; i++)
        {
            if (k.x + movex[i] > R || k.x + movex[i] < 1)
                continue;
            if (k.y + movey[i] > C || k.y + movey[i] < 1)
                continue;
            if (d[k.x + movex[i]][k.y + movey[i]] > max(d[k.x][k.y], dis[k.x + movex[i]][k.y + movey[i]]))
            {
                d[k.x + movex[i]][k.y + movey[i]] = max(d[k.x][k.y], dis[k.x + movex[i]][k.y + movey[i]]);
                //if (!flag[k.x + movex[i]][k.y + movey[i]])
                //{
                    Q[++r] = (Point){k.x + movex[i], k.y + movey[i]};
                    //flag[k.x + movex[i]][k.y + movey[i]] = 1;
                //}
            }
        }
    }
    return d[E.x][E.y];
}
int main()
{
    //freopen("swan.in", "r", stdin);
    // freopen("swan.out", "w", stdout);
    char c;
    scanf("%d%d", &R, &C);
    bool flag = 0;
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            c = getchar();
            while (c != '.' && c != 'X' && c != 'L')
                c = getchar();
            if (c == 'X')
                map[i][j] = 1;
            else if (c == 'L')
            {
                if (flag)
                    E = (Point){i, j};
                else
                {
                    S = (Point){i, j};
                    flag = 1;
                }
            }
        }
    }
    bfs_init();
    printf("%d", SPFA());
    //while (1)
    ;
}
