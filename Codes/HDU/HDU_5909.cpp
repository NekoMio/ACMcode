#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
const int Inv2 = (MOD + 1) / 2;
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
struct data {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
void FWT(int *a, int m) {
  for (int k = 1; k < m; k <<= 1) {
    for (int i = 0; i < m; i++) {
      if (i & k) continue;
      int tmp = (a[i] + a[i + k]) % MOD;
      a[i + k] = (a[i] - a[i + k] + MOD) % MOD;
      a[i] = tmp;
    }
  }
}
void IFWT(int *a, int m) {
  for (int k = 1; k < m; k <<= 1) {
    for (int i = 0; i < m; i++) {
      if (i & k) continue;
      int tmp = 1ll * (a[i] + a[i + k]) % MOD * Inv2 % MOD;
      a[i + k] = 1ll * (a[i] - a[i + k] + MOD) % MOD * Inv2 % MOD;
      a[i] = tmp;
    }
  }
}
int w[MAXN], m;
int F[MAXN][MAXN + 50], tmp[MAXN + 50], ans[MAXN + 50];
void DP(int rt, int fa) {
  F[rt][w[rt]] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DP(v[i].END, rt);
    for (int j = 0; j < m; j++) tmp[j] = F[rt][j];
    FWT(F[v[i].END], m), FWT(tmp, m);
    for (int j = 0; j < m; j++)
      tmp[j] = 1ll * tmp[j] * F[v[i].END][j] % MOD;
    IFWT(tmp, m);
    for (int j = 0; j < m; j++) F[rt][j] = (F[rt][j] + tmp[j]) % MOD;
  }
  for (int i = 0; i < m; i++) ans[i] = (ans[i] + F[rt][i]) % MOD;
}
int main() {
  int T = read();
  while (T--) {
    memset (first, -1, sizeof (first));
    memset (F, 0, sizeof (F));
    memset (ans, 0, sizeof (ans));
    p = 0;
    int n = read();
    m = read();
    for (int i = 1; i <= n; i++)
      w[i] = read();
    for (int i = 1; i < n; i++) {
      int a = read(), b = read();
      add(a, b);
      add(b, a);
    }
    DP(1, 0);
    for (int i = 0; i < m; i++) printf ("%d%c", ans[i], " \n"[i == (m - 1)]);
  }
}