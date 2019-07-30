#include <bits/stdc++.h>
using namespace std;
#define int long long
inline long long read() {
  long long x = 0, f = 1;
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
const int MAXN = 5e5 + 5;
struct data {
  int s, e, a;
}a[MAXN];
vector<int> Start[MAXN * 2], END[MAXN * 2];
long long Hash[MAXN * 2], cnt;
set<long long> st;
signed main() {
  int T = read();
  while (T--) {
    int n = read(), w = read(), d = read();
    cnt = 0;
    for (int i = 1; i <= n; i++) {
      a[i].a = read(), a[i].s = read(), a[i].e = read();
      Hash[++cnt] = a[i].s;
      Hash[++cnt] = a[i].e;
    }
    sort(Hash + 1, Hash + cnt + 1);
    cnt = unique(Hash + 1, Hash + cnt + 1) - Hash - 1;
    for (int i = 1; i <= n; i++) {
      a[i].s = lower_bound(Hash + 1, Hash + cnt + 1, a[i].s) - Hash;
      a[i].e = lower_bound(Hash + 1, Hash + cnt + 1, a[i].e) - Hash;
      Start[a[i].s].push_back(i);
      END[a[i].e].push_back(i);
    }
    set<long long>::iterator it, it1, it2;
    long long Sum = 0, Ans = -1;
    st.insert(0), st.insert(w);
    if (w - 0 > d) Sum++;
    long long last = -1, S = 0;
    for (int i = 1; i <= cnt; i++) {
      for (auto x : END[i]) {
        it = st.find(a[x].a);
        it2 = it, it1 = it;
        it2++, it1--;
        Sum = Sum + (*it2 - *it1 > d) - (*it2 - *it > d) - (*it - *it1 > d);
        st.erase(it);
      }
      for (auto x : Start[i]) {
        it = st.insert(a[x].a).first;
        it2 = it, it1 = it;
        it2++, it1--;
        Sum = Sum - (*it2 - *it1 > d) + (*it2 - *it > d) + (*it - *it1 > d);
      }
      if (Sum == 0) {
        if (Ans == -1) Ans = Hash[i];
        if (last != -1) S += Hash[i] - last;
        last = Hash[i];
      } else {
        if (last != -1) S += Hash[i] - last;
        last = -1;
      }
    }
    printf ("%lld %lld\n", Ans, S);
    for (int i = 1; i <= cnt; i++) Start[i].clear(), END[i].clear();
    st.clear();
  }
  // while (1);
}