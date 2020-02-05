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
struct edge {
  int next, END;
}v[200005 * 2];
int first[200005], p, du[200005];
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
bool flag[200005], vis[200005], color[200005];
void DFS(int rt, bool type) {
  color[rt] = type;
  vis[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!vis[v[i].END]) {
      DFS(v[i].END, type ^ 1);
    }
  }
}
int main() {
  int T = read();
  while (T--) {
    p = 0;
    int n = read(), m = read();
    memset (du, 0, sizeof (du[0]) * (n + 1));
    memset (vis, 0, sizeof (vis[0]) * (n + 1));
    memset (color, 0, sizeof(color[0]) * (n + 1));
    memset (first, -1, sizeof (first[0]) * (n + 1));
    int a, b;
    for (int i = 1; i <= m; i++) {
      a = read(), b = read();
      add(a, b);
      add(b, a);
      du[a]++, du[b]++;
    }
    int Min = n;
    for (int i = 1; i <= n; i++) {
      Min = min(Min, du[i]);
    }
    for (int i = 1; i <= n; i++) {
      if (du[i] == Min) {
        vis[i] = 1;
        flag[i] = 1;
        DFS(v[first[i]].END, 1);
        break;
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      if (color[i]) ans++;
    }
    // assert(ans <= n / 2);
    if (ans > n / 2) {
      printf ("%d\n", n - ans);
      for (int i = 1; i <= n; i++) {
        if (!color[i]) printf("%d ", i);
      }
      printf ("\n");
    } else {
      printf ("%d\n", ans);
      for (int i = 1; i <= n; i++) {
        if (color[i]) printf("%d ", i);
      }
      printf ("\n");
    }
  }
  // while (1);
}