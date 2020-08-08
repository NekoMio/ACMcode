#include <bits/stdc++.h>
using namespace std;
map<int, int> mp;
const int MAXN = 2e6 + 6;
int a[MAXN], tmp[MAXN];
int main() {
  int n, m, k;
  scanf ("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf ("%d", &k);
    for (int i = 1; i <= k; i++) {
      scanf ("%d", tmp + i);
    }
    sort(tmp + 1, tmp + k + 1);
    k = unique(tmp + 1, tmp + k + 1) - tmp - 1;
    
  }
}