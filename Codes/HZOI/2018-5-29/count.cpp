#include <bits/stdc++.h>
using namespace std;
inline long long read() {
  long long x = 0, f = 1;
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
const int MOD = 1e9 + 7;
int pr[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
int id[20], cnt;
long long a[MAXN];
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int n;
long long s1, s2;
int bin[20];
void Trans(long long &x) {
  x /= s1;
  int ans = 0;
  for (int i = 1; i <= cnt; ++i) {
    if (x % pr[id[i]] == 0) {
      ans |= (1 << (i - 1));
    }
  }
  x = ans;
}
int ans = 0;
int N, Qa;
int f[MAXN][32769], tmp[32769];
inline int Num(unsigned int x) {
  unsigned int tmp = x
                   - ((x >> 1) & 033333333333)
                   - ((x >> 2) & 011111111111);
  tmp = (tmp + (tmp >> 3)) & 030707070707;
  return tmp % 63;
}
void DFS(int rt, int fa) {
  for (int i = 0; i <= N; ++i) f[rt][i] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    DFS(v[i].END, rt);
    int vv = a[rt] ^ a[v[i].END];
    int T = N ^ vv;
    for (int j = T; ; j = (j - 1) & T)
    {
      f[rt][j | vv] = (f[rt][j | vv] + 1ll * f[rt][j | vv] * f[v[i].END][j | vv] % MOD) % MOD;    
      if (j == 0) break;
    }
  }
  for (int i = 0; i <= N; ++i) {
    if (Num(i ^ N) & 1) ans = (ans - f[rt][i] + MOD) % MOD;
    else ans = (ans + f[rt][i]) % MOD;
  }
}
int main() {
  // freopen("test/1.in", "r", stdin);
  memset(first, -1, sizeof (first));
  n = read(), s1 = read(), s2 = read();
  s2 /= s1;
  for (int i = 0; i <= 14; ++i) {
    if (s2 % pr[i] == 0) {
      id[++cnt] = i;
    }
  }
  // fprintf (stderr, "%d\n", N);
  N = (1 << cnt) - 1;
  // Qa = N / 2;
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    Trans(a[i]);
    // printf ("%lld\n", a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int b = read(), c = read();
    add(b, c);
    add(c, b);
  }
  DFS(1, 0);
  printf ("%d\n", ans);
}
