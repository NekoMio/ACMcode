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
int v[1505][1505];
bitset<1505> a[1505];
bool Gauss(int n, int m) {
  for (int i = 1, k = 1; i <= m; i++) {
    int tmp = 0;
    for (int j = k + 1; j <= n; j++) {
      if (a[j][i] != 0) {
        tmp = j;
        break;
      }
    }
    if (!tmp) continue;
    if (a[k][i] == 0) swap(a[k], a[tmp]);
    bool flag = 0;
    for (int j = k + 1; j <= n; j++) {
      if (a[j][i]) {
        a[j] ^= a[k];
      }
    }
    k++;
  }
  for (int i = 1; i <= n; i++) {
    if (a[i][m] == 1 && a[i].count() == 1) return 0;
  }
  return 1;
}
int main() {
  int n = read(), k = read();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      a[j][i] = read() & 1;
    }
  }
  for (int i = 1; i <= n + 1; i++)
    a[k + 1][i] = 1;
  if (Gauss(k + 1, n + 1)) printf ("No\n");
  else printf ("Yes\n");
}

/*
1 0 0
0 1 0
1 1 1
*/