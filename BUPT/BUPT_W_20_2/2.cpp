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
const int MAXN = 200000 + 5;
struct data {
  int END, v, next;
}v[MAXN * 2];
int first[MAXN], p;
void add(int a, int b, int c) {
  v[p].END = b;
  v[p].next = first[a];
  v[p].v = c;
  first[a] = p++;
}
int size[MAXN], n;
long long F[MAXN][5], tmp[5];
long long ans = 0;
void DFS(int rt, int fa) {
  size[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END != fa) {
      DFS(v[i].END, rt);
      size[rt] += size[v[i].END];
      memset(tmp, 0, sizeof(tmp));
      // ans += F[rt][2] * ()
      if (v[i].v) {
        tmp[1] += F[v[i].END][1] + F[v[i].END][3];
        tmp[4] += F[v[i].END][4] + 1;
        // tmp[5] += F[v[i].END][5] + F[v[i].END][2];
      } else {
        tmp[2] += F[v[i].END][2] + F[v[i].END][4];
        tmp[3] += F[v[i].END][3] + 1;
      }
      ans += F[rt][1] * tmp[4];
      ans += F[rt][2] * tmp[3];
      ans += F[rt][3] * (tmp[2] + tmp[4] + 2 * tmp[3]);
      ans += F[rt][4] * (tmp[1] + tmp[3] + 2 * tmp[4]);
      for (int i = 1; i <= 4; i++) F[rt][i] += tmp[i];
    }
  }
  // ans += F[rt][1] * F[rt][4];
  // ans += F[rt][3] * F[rt][4];
  // ans += F[rt][2] * F[rt][3];
  ans += F[rt][1] + F[rt][2] + F[rt][3] * 2 + F[rt][4] * 2;
}
int main() {
  n = read();
  memset (first, -1, sizeof(first));
  for (int i = 1; i < n; i++) {
    int a = read(), b = read(), c = read();
    add(a, b, c);
    add(b, a, c);
  }
  DFS(1, 0);
  printf ("%lld\n", ans);
  // while (1);
}