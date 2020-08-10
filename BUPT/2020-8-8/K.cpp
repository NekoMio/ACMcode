#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
#define inf 0x3f3f3f3f
#define m(a) memset(a, 0, sizeof(a))
#define mm(a) memset(a, -1, sizeof(a))
#define mi(a) memset(a, 0x3f3f3f3f, sizeof(a))
const int MAXN = 1e5 + 5;
int n, t, tot;
struct ed {
  int v, nex;
} e[MAXN * 10];
int ti[MAXN];
int res;
int d;
int head[MAXN * 6];
int dfsa(int now, int fa) {
  if (now == n) return 1;
  for (int i = head[now]; i; i = e[i].nex) {
    int v = e[i].v;
    if (v == fa) continue;
    if (dfsa(v, now)) {
      ti[now] = v;
      return v != 0;
    }
  }
}
int dfsb(int now, int fa) {
  int maxx = -1;
  for (int i = head[now]; i; i = e[i].nex) {
    int v = e[i].v;
    if (v == fa || v == ti[now]) continue;
    maxx = max(dfsb(v, now), maxx);
  }
  return maxx + 1;
}
void dfsc(int now, int fa, int st) {
  int d1 = d - 3 * st, c;
  if (d1 <= 0) return;
  int d2 = dfsb(now, fa);
  if (d2 >= d1)
    c = d1 + st;
  else
    c = (d1 + d2 + 1) / 2 + st;
  res = max(res, c);
  dfsc(ti[now], now, st + 1);
}

int main() {
  // cin >> n >> t;
  scanf ("%d%d", &n, &t);
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf ("%d%d", &u, &v);
    // cin >> u >> v;
    e[++tot].v = v;
    e[tot].nex = head[u];
    head[u] = tot;
    e[++tot].v = u;
    e[tot].nex = head[v];
    head[v] = tot;
  }
  dfsa(1, -1);
  int pla = 1, tim = t;
  while (tim-- && pla != n) pla = ti[pla];
  if (pla == n) {
    printf ("0\n");
    // cout << 0 << endl;
    return 0;
  }
  int fy = 1;
  d = -t;
  while (fy != n) {
    fy = ti[fy];
    d++;
  }
  dfsc(pla, -1, 0);
  printf ("%d\n", res);
  // cout << res << endl;
}