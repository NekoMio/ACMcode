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
struct data {
  int x, y, c;
  bool operator == (const data &a) {
    return x == a.x && y == a.y;
  }
}a[100005];
set<int> st;
int Q, n, K, ans[15];
const int MAXN = 1e5 + 5;
long long Sum[MAXN << 2], C[15], SumX[MAXN << 2];
int Num[MAXN << 2];
void build(int l, int r, int rt) {
  Sum[rt] = SumX[rt] = Num[rt] = 0;
  if (l == r) return;
  int mid = l + r >> 1;
  build(l, mid, rt << 1);
  build(mid + 1, r, rt << 1 | 1);
}
void Add(int x, int y, int c, int l, int r, int rt) {
  if (l == r) {
    Sum[rt] += x;
    Num[rt] += c;
    SumX[rt] += y;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) Add(x, y, c, l, mid, rt << 1);
  if (x > mid) Add(x, y, c, mid + 1, r, rt << 1 | 1);
  Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
  Num[rt] = Num[rt << 1] + Num[rt << 1 | 1];
  SumX[rt] = SumX[rt << 1] + SumX[rt << 1 | 1];
}
int v, tmp;
int Query(int pnum, long long pre, long long prex, long long x, int l, int r, int rt) {
  if (l == r) return l;
  int mid = l + r >> 1;
  tmp = 1ll * mid * (pnum + Num[rt << 1]) - (pre + Sum[rt << 1]) + 1ll * v * (pnum + Num[rt << 1]) - (prex + SumX[rt << 1]);
  if (x == tmp) return -1;
  if (x > tmp) return Query(pnum + Num[rt << 1], pre + Sum[rt << 1], prex + SumX[rt << 1], x, mid + 1, r, rt << 1 | 1);
  else return Query(pnum, pre, prex, x, l, mid, rt << 1);
}
long long Q_Sum(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) return Sum[rt];
  int mid = l + r >> 1;
  long long ans = 0;
  if (L <= mid) ans += Q_Sum(L, R, l, mid, rt << 1);
  if (R > mid) ans += Q_Sum(L, R, mid + 1, r, rt << 1 | 1);
  return ans;
}
long long Q_SumX(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) return SumX[rt];
  int mid = l + r >> 1;
  long long ans = 0;
  if (L <= mid) ans += Q_SumX(L, R, l, mid, rt << 1);
  if (R > mid) ans += Q_SumX(L, R, mid + 1, r, rt << 1 | 1);
  return ans;
}
int Q_Num(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) return Num[rt];
  int mid = l + r >> 1;
  int ans = 0;
  if (L <= mid) ans += Q_Num(L, R, l, mid, rt << 1);
  if (R > mid) ans += Q_Num(L, R, mid + 1, r, rt << 1 | 1);
  return ans;
}
bool Judge(int p, int c, int sum, int num, int sumx, int nxt) {
  long long tmp = 1ll * p * num - sum + 1ll * v * num - sumx;
  if ((c - tmp) % num == 0 && (c - tmp) / num < (nxt - p)) return 1;
  return 0; 
}
void Calc() {
  int j = 1, pos, num, nxt;
  set<int>::iterator ito;
  long long sum, sumx;
  for (v = 1; v <= n; v++) {
    while (a[j].x <= v && j <= K) {
      st.insert(a[j].y);
      Add(a[j].y, a[j].x, a[j].c, 1, n, 1);
      j++;
    }
    for (int k = 1; k <= Q; k++) {
      pos = Query(0, 0, 0, C[k], 1, n, 1);
      if (pos == -1) {
        ans[k]++;
        continue;
      }
      if (pos == 1) continue;
      ito = st.upper_bound(pos - 1);
      if (ito != st.end()) nxt = *ito;
      else nxt = n + 1;
      sum = Q_Sum(1, pos - 1, 1, n, 1);
      num = Q_Num(1, pos - 1, 1, n, 1);
      if (num == 0) continue;
      sumx = Q_SumX(1, pos - 1, 1, n, 1);
      if (Judge(pos - 1, C[k], sum, num, sumx, nxt)) {
        ans[k]++;
      }
    }
  }
}
int main() {
  int T = read();
  while (T--) {
    st.clear();
    n = read(), K = read();
    build(1, n, 1);
    memset (ans, 0, sizeof (ans));
    for (int i = 1; i <= K; i++) {
      a[i].x = read(), a[i].y = read();
      a[i].c = 1;
    }
    sort(a + 1, a + K + 1, [](const data &a1, const data &a2) -> bool{
      return a1.x == a2.x ? a1.y < a2.y : a1.x < a2.x;
    });
    int j = 1;
    for (int i = 2; i <= K; i++) {
      if (a[i] == a[j]) {
        a[j].c++;
      } else {
        a[++j] = a[i];
      }
    }
    K = j;
    Q = read();
    for (int i = 1; i <= Q; i++) scanf ("%lld", &C[i]);
    Calc();
    for (int i = 1; i <= Q; i++)
      printf ("%d%c", ans[i], " \n"[i == Q]);
  }
  // printf ("%.2f\n", 1.0 * clock() / CLOCKS_PER_SEC);
}