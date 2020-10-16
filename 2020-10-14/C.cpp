#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
struct data {
  int k, id;
  bool operator < (const data &c) const {
    return k < c.k;
  }
}a[MAXN];
map<int, int> mp;
void Add(int x) {
  for (int i = x; i >= 0; i--) {
    if (mp[i] == 0 || i == 0) {
      mp[i] = 1;
      break;
    } else {
      mp[i] = 0;
    }
  }
}
bool flag[MAXN];
int main() {
  int T, cnt = 0;
  scanf ("%d", &T);
  while (T--) {
    int n;
    cnt++;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf ("%d", &a[i].k);
      a[i].id = i;
      flag[i] = 0;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      Add(a[i].k);
    }
    if (mp[0] == 0) printf ("Case %d: NO\n", cnt);
    else {
      mp.clear();
      for (int i = n; i >= 1; i--) {
        Add(a[i].k);
        flag[a[i].id] = 1;
        if (mp[1] == 1) {
          break;
        }
      }
      mp.clear();
      printf ("Case %d: YES\n", cnt);
      for (int i = 1; i <= n; i++) {
        printf("%d", flag[i] ? 1 : 0);
      }
      printf ("\n");
    }
  }
}