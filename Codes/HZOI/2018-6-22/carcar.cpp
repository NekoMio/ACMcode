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
const int MAXN = 500005;
const int MOD = 1e9 + 7;
struct edge {
  int END, next, v;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int c) {
  v[p].END = b;
  v[p].next = first[a];
  v[p].v = c;
  first[a] = p++;
}
struct data {
  int a, b, c;
}a[MAXN];
int fa[MAXN], du[MAXN], bin[MAXN];
int find(int x) {
  if (fa[x] != x) fa[x] = find(fa[x]);
  return fa[x];
}
int ans = 0;
void DFS(int rt, int fa, int id) {
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt, i);
  }
  if (du[rt] & 1) {
    du[rt] ^= 1, du[fa] ^= 1;
    ans = (ans + bin[v[id].v]) % MOD;
  }
}
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i <= m; ++i) {
    a[i].a = read(), a[i].b = read(), a[i].c = i;
    du[a[i].a]++, du[a[i].b]++;
  }
  bin[0] = 1;
  for (int i = 1; i <= m; ++i) {
    bin[i] = bin[i - 1] * 2 % MOD;
    ans = (ans + bin[i]) % MOD;
  }
  for (int i = 1; i <= n; ++i) du[i] &= 1;
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    if (find(a[i].a) != find(a[i].b)) {
      fa[find(a[i].a)] = find(a[i].b);
      add(a[i].a, a[i].b, a[i].c);
      add(a[i].b, a[i].a, a[i].c);
    }
  }
  DFS(1, 0, 0);
  printf ("%d\n", ans);
}
