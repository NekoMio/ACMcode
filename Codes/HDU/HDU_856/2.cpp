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
const int MAXN = 1e5 + 5;
struct data {
  int x, y;
}L[MAXN], R[MAXN], U[MAXN], D[MAXN];
int Ln, Rn, Un, Dn;
char op[MAXN];
bool cmp1(const data &a, const data &b) {
  return a.x < b.x;
}
bool cmp2(const data &a, const data &b) {
  return a.x > b.x;
}
#define lowbit(_) ((_) & (-_))
int cnt, Sum[MAXN * 2], Hash[MAXN * 2];
void Add(int x, int c) {
  for (int i = x; i <= cnt; i += lowbit(i))
    Sum[i] += c;
}
int Query(int x) {
  int ans = 0;
  for (int i = x; i > 0; i -= lowbit(i))
    ans += Sum[i];
  return ans;
}
int main() {
  int T = read();
  while (T--) {
    int n = read(), m = read(), K = read();
    cnt = 0;
    Ln = Rn = Un = Dn = 0;
    Hash[++cnt] = n, Hash[++cnt] = m;
    for (int i = 1; i <= K; i++) {
      int x = read(), y = read();
      scanf ("%s", op);
      Hash[++cnt] = x, Hash[++cnt] = y;
      if (op[0] == 'U') U[++Un].x = x, U[Un].y = y;
      if (op[0] == 'R') R[++Rn].x = x, R[Rn].y = y;
      if (op[0] == 'L') L[++Ln].x = x, L[Ln].y = y;
      if (op[0] == 'D') D[++Dn].x = x, D[Dn].y = y;
    }
    sort(Hash + 1, Hash + cnt + 1);
    cnt = unique(Hash + 1, Hash + cnt + 1) - Hash - 1;
    for (int i = 1; i <= Un; i++) {
      U[i].x = lower_bound(Hash + 1, Hash + cnt - 1, U[i].x) - Hash;
      U[i].y = lower_bound(Hash + 1, Hash + cnt - 1, U[i].y) - Hash;
    }
    for (int i = 1; i <= Rn; i++) {
      R[i].x = lower_bound(Hash + 1, Hash + cnt - 1, R[i].x) - Hash;
      R[i].y = lower_bound(Hash + 1, Hash + cnt - 1, R[i].y) - Hash;
    }
    for (int i = 1; i <= Ln; i++) {
      L[i].x = lower_bound(Hash + 1, Hash + cnt - 1, L[i].x) - Hash;
      L[i].y = lower_bound(Hash + 1, Hash + cnt - 1, L[i].y) - Hash;
    }
    for (int i = 1; i <= Dn; i++) {
      D[i].x = lower_bound(Hash + 1, Hash + cnt - 1, D[i].x) - Hash;
      D[i].y = lower_bound(Hash + 1, Hash + cnt - 1, D[i].y) - Hash;
    }
    
    long long ans = 0;

    sort(R + 1, R + Rn + 1, cmp1);
    sort(U + 1, U + Un + 1, cmp1);
    sort(D + 1, D + Dn + 1, cmp1);
    memset (Sum, 0, sizeof (Sum[0]) * (cnt + 3));
    for (int i = 1; i <= Un; i++) Add(U[i].y, 1);
    for (int i = 1, h = 1; i <= Rn; i++) {
      while (h <= Un && U[h].x < R[i].x) {
        Add(U[h].y, -1);
        h++;
      }
      ans += Query(R[i].y);
    }
    memset (Sum, 0, sizeof (Sum[0]) * (cnt + 3));
    for (int i = 1; i <= Dn; i++) Add(D[i].y, 1);
    for (int i = 1, h = 1; i <= Rn; i++) {
      while (h <= Dn && D[h].x < R[i].x) {
        Add(D[h].y, -1);
        h++;
      }
      ans += Query(cnt) - Query(R[i].y - 1);
    }

    reverse(U + 1, U + Un + 1);
    reverse(D + 1, D + Dn + 1);
    sort(L + 1, L + Ln + 1, cmp2);
    memset (Sum, 0, sizeof (Sum[0]) * (cnt + 3));
    for (int i = 1; i <= Un; i++) Add(U[i].y, 1);
    for (int i = 1, h = 1; i <= Ln; i++) {
      while (h <= Un && U[h].x > L[i].x) {
        Add(U[h].y, -1);
        h++;
      }
      ans += Query(L[i].y);
    }
    memset (Sum, 0, sizeof (Sum[0]) * (cnt + 3));
    for (int i = 1; i <= Dn; i++) Add(D[i].y, 1);
    for (int i = 1, h = 1; i <= Ln; i++) {
      while (h <= Dn && D[h].x > L[i].x) {
        Add(D[h].y, -1);
        h++;
      }
      ans += Query(cnt) - Query(L[i].y - 1);
    }
    printf ("%lld\n", ans + 1);
  }
  // while (1);
}