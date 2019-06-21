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
int a[MAXN];
int ans[MAXN], del[5005][5005], Del[MAXN];
int Num[MAXN], id[MAXN], cnt;
vector<int> vc[MAXN];
void Init(int m, int n, int K) {
  for (int i = 1; i <= n; ++i)
    Num[a[i]]++;
  for (int i = 1; i <= n; ++i) if (Num[a[i]] < K)
    vc[a[i]].push_back(i);
  for (int i = 1; i <= m; ++i)
    if (Num[i] >= K)
      id[i] = ++cnt;
  for (int i = 1; i <= m; ++i) {
    if (Num[i] >= K) {
      for (int j = 1; j <= n; ++j) {
        if (a[j] == i) {
          if (j != 1 && Num[a[j - 1]] >= K) {
            del[id[a[j]]][id[a[j - 1]]]++;
          }
          if (j != n && Num[a[j + 1]] >= K && a[j + 1] != a[j]) {
            del[id[a[j]]][id[a[j + 1]]]++;
          }
        }
      }
      Del[id[i]] = del[id[i]][id[i]];
    }
  }
}
int vis[MAXN];
int main() {
  // freopen ("test/1.in", "r", stdin);
  // freopen ("light.in", "r", stdin);
  // freopen ("light.out", "w", stdout);
  int n = read(), m = read(), q = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  int K = sqrt(n);
  Init(m, n, K);
  int Ans = 0;
  while (q--) {
    int x = read();
    if (Num[x] >= K) {
      if (!vis[x]) {
        Ans = Ans + Num[x] - Del[id[x]];
        for (int i = 1; i <= cnt; ++i)
          if (i != id[x])
            Del[i] += del[i][id[x]];
      } else {
        Ans = Ans + Del[id[x]] - Num[x];
        for (int i = 1; i <= cnt; ++i)
          if (i != id[x])
            Del[i] -= del[i][id[x]];
      }
      vis[x] ^= 1;
    } else {
      if (!vis[x]) {
        vis[x] ^= 1;
        int Sum = 0;
        for (auto z : vc[x]) {
          if (vis[a[z + 1]]) Sum++;
          if (vis[a[z - 1]] && a[z - 1] != x) Sum++;
          if (Num[a[z + 1]] >= K) Del[id[a[z + 1]]]++;
          if (Num[a[z - 1]] >= K) Del[id[a[z - 1]]]++;
        }
        Ans = Ans + Num[x] - Sum;
      } else {
        int Sum = 0;
        for (auto z : vc[x]) {
          if (vis[a[z + 1]]) Sum++;
          if (vis[a[z - 1]] && a[z - 1] != x) Sum++;
          if (Num[a[z + 1]] >= K) Del[id[a[z + 1]]]--;
          if (Num[a[z - 1]] >= K) Del[id[a[z - 1]]]--;
        }
        vis[x] ^= 1;
        Ans = Ans - Num[x] + Sum;
      }
    }
    printf ("%d\n", Ans);
  }
}
