#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int MAXM = 5e5 + 5;
const int MAXN = 3e5 + 5;
const int MOD = 998244353;
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
struct edge {
  int END, next;
}v[MAXM * 2];
int first[MAXM], p;
void add(int a, int b) {
  v[p].next = first[a];
  v[p].END = b;
  first[a] = p++;
}
int ans[MAXM], num;
int dfn[MAXM], st[MAXM], cnt;
bool vis[MAXM];
void DFS(int rt, int e) {
  vis[rt] = 1;
  st[++cnt] = rt;
  dfn[rt] = cnt;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if ((i ^ 1) == e) continue;
    if (dfn[v[i].END]) {
      ans[++num] = cnt - dfn[v[i].END] + 1;
      continue;
    } else {
      if (vis[v[i].END]) continue;
      DFS(v[i].END, i);
    }
  }
  dfn[rt] = 0;
  cnt--;
}
int main() {

  // int __size__=128<<20;
  // char*__p__=(char*)malloc(__size__)+ __size__;
  // __asm__("movq %0, %%rsp\n"::"r"(__p__));

  int T = 1;

  while (T--) {
    num = 0, cnt = 0;
    memset (vis, 0, sizeof (vis));
    memset (dfn, 0, sizeof (dfn));
    memset (first, -1, sizeof (first));
    p = 0;
    int n = read(), m = read();
    for (int i = 1; i <= m; i++) {
      int a = read(), b = read();
      add(a, b);
      add(b, a);
    }
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        DFS(i, -1);
      }
    }
    long long Ans = 1;
    for (int i = 1; i <= num; i++) {
      Ans = (Ans * (pow_mod(2, ans[i]) - 1)) % MOD;
      m -= ans[i];
    }
    Ans = Ans * pow_mod(2, m) % MOD;
    printf ("%lld\n", Ans);
  }
  // while (1);
}