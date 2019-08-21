#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
#define int long long
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAXN = 1000005;
struct data {
  int a, b;
  bool operator<(const data &c) const { return a > c.a; }
} a[MAXN];
multiset<int> st;
signed main() {
  int T = read();
  while (T--) {
    st.clear();
    multiset<int>::iterator it1, it2;
    int n = read();
    for (int i = 1; i <= n; i++) a[i].a = read(), a[i].b = read();
    sort(a + 1, a + n + 1);
    int ans = 0x3f3f3f3f3f3f3f3f;
    // int Mx = 0;
    int Mx = -0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; i++) st.insert(a[i].b);
    for (int i = 1; i <= n; i++) {
      // if (abs(Mx - a[i].a) > ans) break;
      st.erase(st.find(a[i].b));
      it1 = it2 = st.upper_bound(a[i].a);
      if (it1 != st.end()) {
        ans = min(ans, abs(max(*it1, Mx) - a[i].a));
      }
      if (it2 != st.begin()) {
        it2--;
        if (Mx <= *it2) ans = min(ans, abs(*it2 - a[i].a));
      }
      ans = min(ans, abs(Mx - a[i].a));
      Mx = max(Mx, a[i].b);
    }
    printf ("%lld\n", ans);
  }
}