#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
unordered_map<int, int> mp;
const int MAXN = 2e6 + 6;
int tmp[MAXN];
pair<int, int> a[MAXN];
int main() {
  int n, m, k, Min;
  scanf ("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &k);
    Min = 0x3f3f3f3f;
    for (int i = 1; i <= k; i++) {
      scanf ("%d", tmp + i);
      Min = min(Min, tmp[i]);
    }
    // sort(tmp + 1, tmp + k + 1);
    // k = unique(tmp + 1, tmp + k + 1) - tmp - 1;
    mp[Min]++;
    // for (int i = 1; i <= k; i++)
      // mp[tmp[i]]++;
  }
  // printf ("--\n");
  int i = 1;
  for (auto x : mp) {
    a[i] = x;
    i++;
  }
  sort(a + 1, a + i);
  // printf ("---\n");
  i--;
  for (int j = 1; j <= i; j++) a[j].second += a[j - 1].second;
  int ans = 0x3f3f3f3f;
  for (int p1 = 1, p2 = 2; p2 <= i; p2++) {
    if (a[p2].second - a[p1 - 1].second >= m) {
      ans = min(ans, a[p2].first - a[p1].first);
      p1++;
    }
  }
  printf ("%d\n", ans);
}