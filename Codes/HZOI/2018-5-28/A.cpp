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
const int MAXN = 5e3 + 5;
int du[MAXN];
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p, size[MAXN];
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int f[MAXN][2];
void DFS(int rt, int fa) {
  int t = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt);
    f[rt][0] |= f[v[i].END][1];
    t = 0;
  }
  f[rt][0] |= t;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    if (!f[v[i].END][0]) continue;
    int tmp = 1;
    for (int j = first[rt]; j != -1; j = v[j].next) {
      if (v[j].END == fa || i == j) continue;
      tmp = tmp & f[v[j].END][1];
    }
    f[rt][1] = f[rt][1] | tmp;
  }
}
int main() {
  int n = read(), K = read();
  memset (first, -1, sizeof (first));
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  if (n & 1) printf ("Alan\n");
  else {
    DFS(1, 0);
    if (f[1][1] && K >= n / 2 - 1)
      printf ("Bob\n");
    else printf ("Alan\n");
  }
}

