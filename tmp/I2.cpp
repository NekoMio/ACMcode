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
const int MAXN = 1e4 + 5;
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p, len;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
char c[MAXN], s[MAXN];
bool flag = 0;
void DFS(int rt, int dep) {
  if (dep == len) return flag = 1, void();
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (c[v[i].END] == s[dep + 1]) {
      DFS(v[i].END, dep + 1);
      if (flag) return;
    }
  }
}
int main() {
  int T = read(), tt = 0;;
  while (T--) {
    tt++;
    int n = read();
    memset (first, -1, sizeof (first));
    flag = 0;
    p = 0;
    for (int i = 1; i < n; i++) {
      int a = read(), b = read();
      add(a, b);
      add(b, a);
    }
    scanf ("%s", c + 1);
    scanf ("%s", s + 1);
    len = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
      if (c[i] == s[1]) {
        DFS(i, 1);
        if (flag) break;
      }
    }
    if (flag) printf ("Case #%d: Find\n", tt);
    else printf ("Case #%d: Impossible\n", tt);
  }
  // while (1);
}