#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int map[2005][2005];
int H[2005][2005], S[2005][2005];
int Get_map(int x_1, int y_1, int x_2, int y_2)
{
    return map[x_2][y_2] - map[x_1 - 1][y_2] - map[x_2][y_1 - 1] + map[x_1 - 1][y_1 - 1];
}
int Get_ans(int x_1, int y_1, int x_2, int y_2)
{
    return Get_map(x_1, y_1, x_2, y_2) - (H[x_2][y_2] - H[x_2][y_1 - 1] - H[x_1][y_2] + H[x_1][y_1 - 1]) - (S[x_2][y_2] - S[x_2][y_1] - S[x_1 - 1][y_2] + S[x_1 - 1][y_1]);
}
int main()
{
    freopen("duty.in", "r", stdin);
    freopen("duty.out", "w", stdout);
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%1d", &map[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            H[i][j] = (map[i][j] && map[i - 1][j]);
            S[i][j] = (map[i][j] && map[i][j - 1]);
            // printf("%d ", H[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            map[i][j] += (map[i - 1][j] + map[i][j - 1] - map[i - 1][j - 1]);
            H[i][j] += (H[i - 1][j] + H[i][j - 1] - H[i - 1][j - 1]);
            S[i][j] += (S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1]);
        }
    while (q--)
    {
        int x_1, x_2, y_1, y_2;
        scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
        printf("%d\n",Get_ans(x_1, y_1, x_2, y_2));
    }
    // while(1);
}