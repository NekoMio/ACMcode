#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

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
const int MAXN = 1005;
int kk[MAXN];
struct data {
  int END, next, v;
} v[MAXN * MAXN];
int first[MAXN], p;
void add(int a, int b, int x) {
  v[p].next = first[a];
  v[p].END = b;
  v[p].v = x;
  first[a] = p++;
}
queue<int> Q;
bool flag[MAXN];
int dis[MAXN];
void spfa() {
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    flag[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (dis[v[i].END] > dis[k] + v[i].v) {
        dis[v[i].END] = dis[k] + v[i].v;
        if (!flag[v[i].END]) {
          flag[v[i].END] = 1;
          Q.push(v[i].END);
        }
      }
    }
  }
}
int main() {
  int T = read();
  while (T--) {
    int n = read(), m = read(), s = read(), k = read(), c = read();
    memset(first, -1, sizeof(first));
    p = 0;
    for (int i = 1; i <= k; i++) kk[i] = read();
    for (int i = 1; i <= m; i++) {
      int a = read(), b = read(), x = read();
      add(a, b, x);
      add(b, a, x);
    }
    int Max1 = 0, Max2 = 0;
    Q.push(s);
    memset(dis, 0x3f, sizeof(dis));
    memset(flag, 0, sizeof(flag));
    dis[s] = 0;
    spfa();
    for (int i = 1; i <= n; i++) Max1 = max(Max1, dis[i]);
    memset(dis, 0x3f, sizeof(dis));
    memset(flag, 0, sizeof(flag));
    for (int i = 1; i <= k; i++) {
      Q.push(kk[i]);
      dis[kk[i]] = 0;
    }
    spfa();
    for (int i = 1; i <= n; i++) Max2 = max(Max2, dis[i]);
    if (Max1 <= 1ll * Max2 * c)
      printf("%d\n", Max1);
    else
      printf("%d\n", Max2);
  }
}