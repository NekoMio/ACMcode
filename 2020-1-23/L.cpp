#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
vector<pair<int, int> > a[505][505];
int c[505][505];
int Min[2][MAXN], Max[2][MAXN];
int Sum[505][505];
#define lowbit(_) ((_) & (-_))
int n, m;
void Add(int x, int y) {
  for (int i = x; i <= n; i += lowbit(i)) {
    for (int j = y; j <= m; j += lowbit(j)) {
      Sum[i][j]++;
    }
  }
}
int Query(int x, int y) {
  int ans = 0;
  for (int i = x; i > 0; i -= lowbit(i)) {
    for (int j = y; j > 0; j -= lowbit(j)) {
      ans += Sum[i][j];
    }
  }
  return ans;
}
int main() {
  // int n, m;
  scanf ("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf ("%d", &c[i][j]);
    }
  }
  memset (Min, 0x3f, sizeof(Min));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      Min[0][c[i][j]] = min(Min[0][c[i][j]], i);
      Min[1][c[i][j]] = min(Min[1][c[i][j]], j);
      Max[0][c[i][j]] = max(Max[0][c[i][j]], i);
      Max[1][c[i][j]] = max(Max[1][c[i][j]], j);
    }
  }
  for (int i = 1; i <= 1000000; i++) {
    if (Min[0][i] < 1000) {
      a[Min[0][i]][Min[1][i]].push_back(pair<int,int>(Max[0][i], Max[1][i]));
    }
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    memset (Sum, 0, sizeof(Sum));
    for (int j = 1; j <= m; j++) {
      for (int k = 1; k <= i; k++) {
        for (auto x : a[k][j]) {
          Add(n - x.first + 1, m - x.second + 1);
        }
      }
      for (auto x : a[i][j]) {
        ans = ans + Query(n - x.first + 1, m - x.second + 1);
        ans--;
      }
    }
  }
  printf ("%lld\n", ans);
} 