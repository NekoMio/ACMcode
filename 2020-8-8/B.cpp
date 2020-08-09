#include <bits/stdc++.h>
using namespace std;
const int MaxN = 100010, MaxM = 100010;
struct edge {
  int to, w, next;
};

edge e[MaxM];
int head[MaxN], cnt;
int n;
inline void add_edge(int u, int v, int w) {
  cnt++;
  e[cnt].w = w;
  e[cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}
int ans = 0;
void init() {
  ans = 0;
  memset(head, 0, sizeof(head));
  cnt = 0;
}
int a[MaxN], sz[MaxN], wsz[MaxN];
void dfs_pre(int now, int pre, int prew) {
  int nxt, w;
  sz[now] = a[now];
  wsz[now] = prew;
  for (int i = head[now]; i; i = e[i].next) {
    nxt = e[i].to;
    w = e[i].w;
    if (nxt == pre) continue;
    dfs_pre(nxt, now, w);
    sz[now] += sz[nxt];
    wsz[now] += wsz[nxt];
  }
}
void dfs(int now, int pre, int HP, int prew) {
  int nxt, w;
  HP += a[now];
  int res = 0;
  for (int i = head[now]; i; i = e[i].next) {
    nxt = e[i].to;
    w = e[i].w;
    if (nxt == pre) continue;
    if (HP >= w) {
      dfs(nxt, now, HP - w, w);
    } else {
      ans += w - HP;
      dfs(nxt, now, 0, w);
    }
    HP = max(0, HP + sz[nxt] - 2 * wsz[nxt]);
    // cout << now << " " << nxt << " " << HP << endl;
  }
  // cout << now << " " << pre << " " << HP << " " << prew << endl;
  // cout << ans << endl;
  if (pre == 0) return;
  if (HP >= prew) return;
  ans += prew - HP;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i < n; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      add_edge(u, v, w);
      add_edge(v, u, w);
    }
    dfs(1, 0, 0, 0);
    printf("%d\n", ans);
  }
}
