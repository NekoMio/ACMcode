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
const int MAXN = 1e6 + 5;
int a[MAXN], Hash[MAXN * 10], Cnt, now;
int prime[MAXN], pre[MAXN], cnt;
bool isnprime[MAXN];
void Get_Prime() {
  isnprime[1] = 1;
  for (int i = 1; i <= 1000000; i++) {
    if (!isnprime[i]) prime[++cnt] = i, pre[i] = i;
    for (int j = 1; j <= cnt; j++) {
      if (i * prime[j] > 1000000) break;
      isnprime[i * prime[j]] = 1;
      pre[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}
void Divide(int x, void C(int)) {
  while (x != 1) {
    C(pre[x]);
    x /= pre[x];
  }
}
vector<int> vc[MAXN];
int main() {
  Get_Prime();
  int n = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  for (int i = 1; i <= n; i++) {
    Divide(a[i], [](int x){
      Hash[++Cnt] = x;
    });
  }
  sort(Hash + 1, Hash + Cnt + 1);
  Cnt = unique(Hash + 1, Hash + Cnt + 1) - Hash - 1;
  for (int i = 1; i <= Cnt; i++) vc[i].push_back(0);
  for (int i = 1; i <= n; i++) {
    now = i;
    Divide(a[i], [](int x){
      vc[lower_bound(Hash + 1, Hash + Cnt + 1, x) - Hash].push_back(now);
    });
  }
  for (int i = 1; i <= Cnt; i++) vc[i].push_back(n + 1);
  long long Ans = 0;
  int t;
  for (int i = 1; i <= Cnt; i++) {
    // if (vc[i].size()) {
    Ans += 1ll * n * (n + 1) / 2;
    for (int j = 0; j + 1 < vc[i].size(); j++) {
      t = vc[i][j + 1] - vc[i][j] - 1;
      Ans -= 1ll * t * (t + 1) / 2;
    }
  }
  printf ("%lld\n", Ans);
  // while (1);
}