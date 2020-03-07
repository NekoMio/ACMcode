#include <bits/stdc++.h>
using namespace std;
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
const int MAXN = 1e5 + 5;
int s[MAXN];
vector<int> /*vc[MAXN], */h, d;
set<int> st[MAXN];
int main() {
  int n = read(), m = read();
  int Sum = 0;
  for (int i = 1; i <= n; i++) {
    s[i] = read();
    Sum += s[i];
    for (int j = 1; j <= s[i]; j++) {
      // vc[i].push_back(read());
      st[i].insert(read());
    }
    // sort(vc[i].begin(), vc[i].end());
  }
  int Div = Sum / n;
  int mo = Sum % n;
  int tmp = mo, tmp2 = mo;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] > Div) tmp--;
  }
  for (int i = 1; i <= n; i++) {
    if (tmp2 > 0) {
      if (s[i] > Div + 1) {
        h.push_back(i);
        ans += s[i] - (Div + 1);
        tmp2--;
      } else if (s[i] == Div + 1) {
        tmp2--;
      } else if (s[i] == Div) {
        if (tmp > 0)
          d.push_back(i);
      } else {
        d.push_back(i);
      }
    } else {
      if (s[i] > Div) {
        ans += s[i] - Div;
        h.push_back(i);
      } else if (s[i] < Div) {
        d.push_back(i);
      }
    }
  }
  printf ("%d\n", ans);
  auto l = d.begin();
  for (auto i : h) {
    // if (s[i] > Div + (mo > 0)) {
    for (; l != d.end(); l++) {
      bool flag = 0;
      for (auto x = st[i].begin(), x2 = x; x != st[i].end(); x = x2) {
        x2++;
        if (s[i] == Div + (mo > 0)) {
          flag = 1;
          break;
        }
        if (!st[*l].count(*x)) {
          printf ("%d %d %d\n", i, *l, *x);
          s[*l]++;
          st[*l].insert(*x);
          st[i].erase(x);
          s[i]--;
        }
        if (tmp2 > 0) {
          if (s[*l] == Div + 1) {
            tmp2--;
            break;
          }
        } else {
          if (s[*l] == Div) break;
        }
      }
      if (flag) break;
    }
    mo--;
  }
}