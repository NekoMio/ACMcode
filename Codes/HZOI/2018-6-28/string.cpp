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
const int MAXN = 300005;
const int MOD = 1e9 + 7;
int n, m;
char s[MAXN];
struct PAM {
  int ch[MAXN][26], fail[MAXN], len[MAXN], f[MAXN], d[MAXN];
  int cnt, now;
  PAM() {cnt = 1, fail[0] = fail[1] = 1, len[1] = -1; }
  void extend(int c, int pos) {
    int p = now;
    while (s[pos - len[p] - 1] != s[pos]) p = fail[p];
    if (!ch[p][c]) {
      int np = ++cnt, q = fail[p];
      len[np] = len[p] + 2;
      while (s[pos - len[q] - 1] != s[pos]) q = fail[q];
      fail[np] = ch[q][c];
      d[np] = len[np] - len[fail[np]];
      f[np] = (d[np] == d[fail[np]] ? f[fail[np]] : np);
      ch[p][c] = np;
    }
    now = ch[p][c];
  }
  int find(int x, int pos) {
    while (s[pos - len[x] - 1] != s[pos]) x = fail[x];
    return x;
  }
  struct edge {
    int END, next;
  } v[MAXN];
  int first[MAXN], p;
  int L[MAXN], R[MAXN], Index;
  void add(int a, int b) {
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
  }
  void Build() {
    memset (first, -1, sizeof (first));
    for (int i = 0; i <= cnt; ++i)
      if (i != 1)
        add(fail[i], i);
  }
  void dfs(int x) {
    L[x] = ++Index;
    for (int i = first[x]; i != -1; i = v[i].next)
      dfs(v[i].END);
    R[x] = Index;
  }
}pam;

struct data {
  int L, id;
};
struct Seg {
  int Max[MAXN << 2];
  void Pushup(int rt) {
    Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]); 
  }
  void Update(int x, int c, int l, int r, int rt) {
    if (l == r) return Max[rt] = c, void();
    int mid = l + r >> 1;
    if (x <= mid) Update(x, c, l, mid, rt << 1);
    else Update(x, c, mid + 1, r, rt << 1 | 1);
    Pushup(rt);
  }
  int Query(int L, int R, int l, int r, int rt) {
    if (L <= l && R >= r) return Max[rt];
    int mid = l + r >> 1, ans = 0;
    if (L <= mid) ans = max(ans, Query(L, R, l, mid, rt << 1));
    if (R > mid) ans = max(ans, Query(L, R, mid + 1, r, rt << 1 | 1));
    return ans;
  }
}seg;
struct BIT {
  int Sum[MAXN];
  #define lowbit(_) ((_) & (-_))
  void Update(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i))
      Sum[i] += c;
  }
  int Query(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
      ans += Sum[i];
    return ans;
  }
}bit;
vector<data> vc[MAXN];
int ans[1000005];
int main() {
  // freopen ("string.in", "r", stdin);
  // freopen ("string.out", "w", stdout);
  n = read(), m = read();
  scanf ("%s", s + 1);
  for (int i = 1; i <= n; ++i)
    pam.extend(s[i] - 'a', i);
  pam.Build(), pam.dfs(1);
  for (int i = 1; i <= m; ++i) {
    int l = read(), r = read();
    vc[r].push_back((data){l, i});
  }
  int now = 1;
  for (int i = 1; i <= n; ++i) {
    now = pam.ch[pam.find(now, i)][s[i] - 'a'];
    for (int j = now; j; j = pam.fail[pam.f[j]]) {
      bit.Update(max(1, seg.Query(pam.L[j], pam.R[j], 1, pam.Index, 1) - pam.len[j] + 2), 1);
      bit.Update(i - pam.len[pam.f[j]] + 2, -1);
    }
    seg.Update(pam.L[now], i, 1, pam.Index, 1);
    for (auto x : vc[i]) ans[x.id] = bit.Query(x.L);
  }
  int Ans = 0;
  for (int i = 1; i <= m; ++i) Ans = (Ans + 1ll * ans[i] * i % MOD) % MOD;
  printf ("%d\n", Ans);
}
