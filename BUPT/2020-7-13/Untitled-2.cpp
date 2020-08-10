#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define zmd main
int a, b, n;
int sta[1026][1026][12], sti[1026][1026][12];
int kk;
inline int query1(int x, int y, int xx, int yy) {
  int t1 = sta[x][y][kk], t2 = sta[xx - (1 << kk) + 1][y][kk],
      t3 = sta[x][yy - (1 << kk) + 1][kk],
      t4 = sta[xx - (1 << kk) + 1][yy - (1 << kk) + 1][kk];
  return max(max(max(t1, t2), t3), t4);
}
inline int query2(int x, int y, int xx, int yy) {
  int t1 = sti[x][y][kk], t2 = sti[xx - (1 << kk) + 1][y][kk],
      t3 = sti[x][yy - (1 << kk) + 1][kk],
      t4 = sti[xx - (1 << kk) + 1][yy - (1 << kk) + 1][kk];
  return min(min(min(t1, t2), t3), t4);
}
inline int Max(int a, int b, int c, int d) { return max(max(max(a, b), c), d); }
inline int Min(int a, int b, int c, int d) { return min(min(min(a, b), c), d); }
int zmd() {
  std::cin >> a >> b >> n;
  for (int i = 1; i <= a; ++i)
    for (int j = 1, tmp; j <= b; ++j) {
      scanf("%d", &tmp);
      sta[i][j][0] = sti[i][j][0] = tmp;
    }
  int shit = min(a, b);
  for (int k = 1; k <= 11; ++k)
    for (int i = 1; i + (1 << k) - 1 <= a; ++i)
      for (int j = 1; j + (1 << k) - 1 <= b; ++j) {
        sta[i][j][k] = Max(sta[i][j][k - 1], sta[i + (1 << k - 1)][j][k - 1],
                           sta[i][j + (1 << k - 1)][k - 1],
                           sta[i + (1 << k - 1)][j + (1 << k - 1)][k - 1]);
        sti[i][j][k] = Min(sti[i][j][k - 1], sti[i + (1 << k - 1)][j][k - 1],
                           sti[i][j + (1 << k - 1)][k - 1],
                           sti[i + (1 << k - 1)][j + (1 << k - 1)][k - 1]);
      }
  kk = (int)(log(n) / log(2));
  int ans = 0x3f3f3f3f;
  for (int i = 1; i + n - 1 <= a; i++)
    for (int j = 1; j + n - 1 <= b; j++)
      ans = std::min(ans, query1(i, j, i + n - 1, j + n - 1) -
                              query2(i, j, i + n - 1, j + n - 1));
  cout << ans;
  return 0;
}