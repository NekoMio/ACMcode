#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long
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
const int MAXN = 40010;
struct edge {
  int END, next, v;
} v[MAXN * 2];
int first[MAXN], p;
void add(int a, int b, int c) {
  v[p].END = b;
  v[p].next = first[a];
  v[p].v = c;
  first[a] = p++;
}
int Max[MAXN], sum, size[MAXN], ans, d[MAXN], H[MAXN];
bool vis[MAXN];
int root, cnt, K;
void Get_root(int rt, int fa) {
  size[rt] = 1, Max[rt] = 0;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!vis[v[i].END] && v[i].END != fa) {
      Get_root(v[i].END, rt);
      size[rt] += size[v[i].END];
      Max[rt] = max(Max[rt], size[v[i].END]);
    }
  }
  Max[rt] = max(Max[rt], sum - size[rt]);
  if (Max[rt] < Max[root]) root = rt;
}
void DFS(int rt, int fa) {
  H[++cnt] = d[rt];
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END != fa && !vis[v[i].END]) {
      d[v[i].END] = d[rt] + v[i].v;
      DFS(v[i].END, rt);
    }
  }
}
int Calc(int rt, int val) {
  d[rt] = val, cnt = 0;
  DFS(rt, 0);
  sort(H + 1, H + cnt + 1);
  int l = 1, r = cnt, ret = 0;
  while (l < r) {
    if (H[l] + H[r] <= K) {
      ret += r - l;
      l++;
    } else r--;
  }
  return ret;
}
void Solve(int rt) {
  ans += Calc(rt, 0);
  vis[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!vis[v[i].END]) {
      ans -= Calc(v[i].END, v[i].v);
      root = 0, sum = size[v[i].END];
      Get_root(v[i].END, 0);
      Solve(root);
    }
  }
}
signed main() {
  int n = read(), m = read();
  memset (first, -1, sizeof (first));
  for (int i = 1; i <= m; i++) {
    int a = read(), b = read(), c = read();
    add(a, b, c);
    add(b, a, c);
  }
  K = read();
  Max[0] = sum = n;
  Get_root(1, 0);
  Solve(root);
  printf ("%lld\n", ans);
}