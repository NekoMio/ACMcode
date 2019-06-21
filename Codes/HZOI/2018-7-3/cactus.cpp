#pragma GCC optimize("O2")
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
const int MAXN = 3e5 + 5;
const int MOD = 998244353;
set<pair<int,int>> st;
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int n, m, lim[MAXN];
int N, rev[MAXN * 4], Inv;
int pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
void Init(int n) {
  N = 1;
  while (N < n) N <<= 1;
  Inv = pow_mod(N, MOD - 2);
  for (int i = 1; i < N; ++i) {
    if (i & 1) rev[i] = (rev[i >> 1] >> 1) | (N >> 1);
    else rev[i] = (rev[i >> 1] >> 1);
  }
}
void FFt(int *a, int op) {
  for (int i = 1; i <= N; ++i)
    if (i < rev[i])
      swap(a[i], a[rev[i]]);
  int wn, w, t;
  for (int k = 2; k <= N; k <<= 1) {
    wn = pow_mod(3, op == 1 ? (MOD - 1) / k : MOD - 1 - (MOD - 1) / k);
    for (int j = 0; j < N; j += k) {
      w = 1;
      for (int i = 0; i < (k >> 1); ++i, w = 1ll * w * wn % MOD) {
        t = 1ll * a[i + j + (k >> 1)] * w % MOD;
        a[i + j + (k >> 1)] = (a[i + j] - t + MOD) % MOD;
        a[i + j] = (a[i + j] + t) % MOD;
      } 
    }
  }
  if (op == -1)
    for (int i = 0; i < N; ++i)
      a[i] = 1ll * a[i] * Inv % MOD;
}
struct data {
  int a, b, c;
};
vector<data> X[MAXN];
int Solve(int *a, int l, int r, int rt) {
  int ra = (r - l + 1) * 2 + 1;
  if (ra <= 256) {
    memset (a, 0, ra << 2), a[0] = 1;
    for (int i = l; i <= r; ++i) {
      for (int j = 2 * (i - l); j >= 0; --j) {
        a[j + 2] = (a[j + 2] + 1ll * a[j] * X[rt][i].a % MOD) % MOD;
        a[j + 1] = (a[j + 1] + 1ll * a[j] * X[rt][i].b % MOD) % MOD;
        a[j] = 1ll * a[j] * X[rt][i].c % MOD;
      }
    }
    // while (a[ra - 1] == 0) ra--;
    return ra;
  }
  int mid = l + r >> 1;
  int *f1 = a, r1 = Solve(f1, l, mid, rt);
  int *f2 = a + r1, r2 = Solve(f2, mid + 1, r, rt);
  Init(ra);
  static int tmp1[MAXN * 10], tmp2[MAXN * 10];
  memcpy(tmp1, f1, r1 << 2), memset (tmp1 + r1, 0, (N - r1) << 2), FFt(tmp1, 1);
  memcpy(tmp2, f2, r2 << 2), memset (tmp2 + r2, 0, (N - r2) << 2), FFt(tmp2, 1);
  for (int i = 0; i < N; ++i) a[i] = 1ll * tmp1[i] * tmp2[i] % MOD;
  FFt(a, -1);
  return ra;
}
int tmp[MAXN * 10];
bool vis[MAXN], flag[MAXN];
vector<int> vc[MAXN];
int fa[MAXN];
void DFS(int rt, int F) {
  vis[rt] = 1;
  flag[rt] = 1;
  if (F != -1) fa[rt] = v[F].END;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (i == F) continue;
    if (vis[v[i].END]) vc[v[i].END].push_back(rt);
    else {
      if (!flag[v[i].END])
        DFS(v[i].END, i ^ 1);
    }
  }
  vis[rt] = 0;
}
int f[MAXN][2][2][2], fcnt;
int Sum[MAXN][4];
void DP(int rt, int F) {
  vis[rt] = 1;
  for (auto x : vc[rt]) {
    fcnt++;
    int now = 0;
    int ff = fcnt;
    f[ff][now][0][1] = 1;
    f[ff][now][1][0] = 1;
    for (int i = x; i != rt; i = fa[i]) {
      DP(i, fa[i]);
      now ^= 1;
      f[ff][now][0][1] = (1ll * f[ff][now ^ 1][0][1] * (Sum[i][1] + Sum[i][2]) % MOD + 1ll * f[ff][now ^ 1][0][0] * Sum[i][1] % MOD) % MOD;
      f[ff][now][0][0] = (1ll * f[ff][now ^ 1][0][1] * ((Sum[i][1] + Sum[i][2]) % MOD + Sum[i][3]) % MOD + 1ll * f[ff][now ^ 1][0][0] * (Sum[i][1] + Sum[i][2]) % MOD) % MOD;
      f[ff][now][1][1] = (1ll * f[ff][now ^ 1][1][1] * (Sum[i][1] + Sum[i][2]) % MOD + 1ll * f[ff][now ^ 1][1][0] * Sum[i][1] % MOD) % MOD;
      f[ff][now][1][0] = (1ll * f[ff][now ^ 1][1][1] * ((Sum[i][1] + Sum[i][2]) % MOD + Sum[i][3]) % MOD + 1ll * f[ff][now ^ 1][1][0] * (Sum[i][1] + Sum[i][2]) % MOD) % MOD;
      vis[i] = 1;
    }
    X[rt].push_back((data){f[ff][now][0][0], f[ff][now][1][0] + f[ff][now][0][1], f[ff][now][1][1]});
  }
  
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == F) continue;
    if (vis[v[i].END]) continue;
    DP(v[i].END, rt);
    X[rt].push_back((data){0, ((Sum[v[i].END][1] + Sum[v[i].END][2]) % MOD + Sum[v[i].END][3]) % MOD, (Sum[v[i].END][1] + Sum[v[i].END][2]) % MOD});
  }
  // cerr << rt << endl;
  // X[rt].push_back((data){0, 0, 1});
  int cnt = X[rt].size() - 1;
  // memset (tmp, 0, (lim[rt] + 1) << 2);
  if (cnt != -1) 
  {
    Solve(tmp, 0, cnt, rt);
    int len = 0;
    for (auto x : X[rt]) {
      if (x.a) len += 2;
      else if (x.b) len += 1;
    }
// #define Mine
#ifdef Mine
    if (1) {
      printf ("%d:\n", rt);
      for (auto x : X[rt]) printf ("%d %d %d\n", x.a, x.b, x.c);
      printf ("0 0 1\n");
      for (int i = 0; i <= len; ++i) printf ("%d ", tmp[i]);
      printf ("\n");
    }
#endif
    for (int i = len + 1; i < N; ++i) tmp[i] = 0;
    for (int i = 0; i < lim[rt] - 1 && i <= len; ++i)
      Sum[rt][1] = (Sum[rt][1] + tmp[i]) % MOD;
    if (lim[rt] - 1 <= len) Sum[rt][2] = tmp[lim[rt] - 1];
    if (lim[rt] <= len) Sum[rt][3] = tmp[lim[rt]];
  } else {
    if (lim[rt] == 1) {
      Sum[rt][2] = 1;
      Sum[rt][1] = 0;
    }
    else {
      Sum[rt][2] = 0;
      Sum[rt][1] = 1;
    }
    Sum[rt][3] = 0;
  }
#ifdef Mine
  printf ("----%d:\n", rt);
  printf ("%d %d %d\n", Sum[rt][1], Sum[rt][2], Sum[rt][3]);
  printf ("\n");
#endif
// #undef Mine
}
int main() {
/*
#ifdef Mine
  freopen ("2018-7-3/cactus6-5.in", "r", stdin);
  freopen ("2018-7-3/cactus.out", "w", stdout);
#else
  freopen ("cactus.in", "r", stdin);
  freopen ("cactus.out", "w", stdout);
#endif
*/
  n = read(), m = read();
  memset (first, -1, sizeof (first));
  for (int i = 1; i <= m; ++i) {
    int a = read(), b = read();
    // if (!st.count(pair<int,int>(a,b))) {
      add(a, b);
      add(b, a);
      // st.insert(pair<int,int>(a,b));
    // }
  }
  for (int i = 1; i <= n; ++i) lim[i] = read();
  DFS(1, -1);
  // fprintf (stderr, "%d\n", vc[1].size());
  DP(1, 0);
  printf ("%d\n", ((Sum[1][1] + Sum[1][2]) % MOD + Sum[1][3]) % MOD);
}
