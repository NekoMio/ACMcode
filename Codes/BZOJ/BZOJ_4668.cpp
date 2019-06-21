#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
int rk[MAXN], fa[MAXN], id[MAXN], cnt;
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
void Merge(int a, int b, int val) {
  if (a == b) return;
  if (rk[a] > rk[b]) swap(a, b);
  fa[a] = b;
  rk[a] == rk[b] ? ++rk[b] : 0;
  id[a] = val;
}
void add(int a, int b) {
  while (a != fa[a]) a = fa[a];
  while (b != fa[b]) b = fa[b];
  Merge(a, b, ++cnt);
}
int main() {
  int n = read(), m = read();
  int lastans = 0;
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    int tp = read();
    if (!tp) add(read() ^ lastans, read() ^ lastans);
    else {
      int x = read() ^ lastans, y = read() ^ lastans, tmpx = x, tmpy = y;
      int lenx = 0, leny = 0;
      while (x != fa[x]) lenx++, x = fa[x];
      while (y != fa[y]) leny++, y = fa[y];
      if (x != y) printf ("%d\n", lastans = 0);
      else {
        x = tmpx, y = tmpy;
        if (lenx < leny) swap(x, y), swap(lenx, leny);
        lastans = 0;
        for (int i = 1; i <= lenx - leny; ++i) lastans = max(lastans, id[x]), x = fa[x];
        for (; x != y; x = fa[x], y = fa[y]) lastans = max(lastans, max(id[x], id[y]));
        printf ("%d\n", lastans);
      }
    }
  }
}
