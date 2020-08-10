#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int first[55], p;
class edge {
 public:
  int END, S, next, cap, cost;
} v[205];

void add(int a, int b, int f, int c) {
  v[p].END = b, v[p].next = first[a], v[p].S = a, v[p].cap = f, v[p].cost = c,
  first[a] = p++;
  v[p].END = a, v[p].next = first[b], v[p].S = b, v[p].cap = 0, v[p].cost = -c,
  first[b] = p++;
}
int dis[205], pre[205];
bool vis[205];
bool spfa(int S, int E) {
  memset(dis, 0x3f, sizeof(dis));
  memset(pre, -1, sizeof(pre));
  memset(vis, 0, sizeof(vis));
  queue<int> Q;
  Q.push(S);
  vis[S] = 1;
  dis[S] = 0;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    vis[u] = 0;
    for (int i = first[u]; i != -1; i = v[i].next) {
      if (!v[i].cap) continue;
      if (dis[v[i].END] > dis[u] + v[i].cost) {
        dis[v[i].END] = dis[u] + v[i].cost;
        pre[v[i].END] = i;
        if (!vis[v[i].END]) {
          vis[v[i].END] = 1;
          Q.push(v[i].END);
        }
      }
    }
  }
  return dis[E] != 0x3f3f3f3f;
}
int tmp[205], tot;
void MinCost(int S, int T) {
  while (spfa(S, T)) {
    // flow = INF;
    // for (int i = pre[T]; i != -1; i = pre[v[i].S]) flow = min(flow, v[i].cap);
    for (int i = pre[T]; i != -1; i = pre[v[i].S])
      v[i].cap -= 1, v[i ^ 1].cap += 1;
    tmp[++tot] = dis[T];
  }
}
int main() {
  int n, m;
  while (scanf ("%d%d", &n, &m) != EOF) {
    memset(first, -1, sizeof(first));
    tot = p = 0;
    int a, b, c;
    for (int i = 1; i <= m; i++) {
      scanf ("%d%d%d", &a, &b, &c);
      add(a, b, 1, c);
    }
    int q, v, u;
    MinCost(1, n);
    scanf ("%d", &q);
    long long C = 0;
    while (q--) {
      scanf ("%d%d", &u, &v);
      if (1.0 * v / u > tot) {
        printf ("NaN\n");
      } else {
        int t = v / u;
        long long ans = 0;
        for (int i = 1; i <= t; i++) {
          ans = ans + tmp[i];
        }
        C = v - 1ll * u * t;
        C = C * tmp[t + 1] + 1ll * ans * u;
        long long gcd = __gcd(C, 1ll * v);
        printf ("%lld/%d\n", C / gcd, v / gcd);
      }
    }
  }
}
