#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
inline int read() {
  int x = 0, f = 1;
  char ch = getc();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getc();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getc();
  }
  return x * f;
}
/*
#define max(_, __) ((_) > (__) ? (_) : (__))
#define min(_, __) ((_) < (__) ? (_) : (__))
*/
inline int max(int x, int y) {
  return x > y ? x : y;
}
inline int min(int x, int y) {
  return x < y ? x : y;
}
const int MAXN = 1e6 + 5;
struct heap {
  int a[MAXN + 10], x;
  heap() { x = 0; }
  inline int top() { return a[1]; }
  inline void push(int c) {
    a[++x] = c;
    for (register int i = x, j = i >> 1; j; i = j, j >>= 1) {
      if (a[i] > a[j]) swap(a[i], a[j]);
      else break;
    }
  }
  inline void pop() {
    a[1] = a[x--];
    for (register int i = 1, j = (i << 1); j <= x; i = j, j <<= 1) {
      if ((j | 1) <= x && a[j | 1] > a[j]) j |= 1;
      if (a[j] > a[i]) swap(a[j], a[i]);
      else break;
    }
  }
};

struct Priority_queue {
  heap Q1, Q2;
  inline int size() { return Q1.x - Q2.x; }
  inline void push(const int &x) { Q1.push(x); }
  inline void erase(const int &x) { Q2.push(x); }
  inline int top() {
    while (Q2.x != 0 && Q1.top() == Q2.top()) {
      Q1.pop();
      Q2.pop();
    }
    return Q1.top();
  }
} Q;
int a[MAXN], n, k;
int Max[MAXN << 2], Maxid[MAXN << 2];
inline void Build(int l, int r, int rt) {
  if (l == r) {
    Max[rt] = a[l];
    Maxid[rt] = l;
    return;
  }
  int mid = l + r >> 1;
  Build(l, mid, rt << 1);
  Build(mid + 1, r, rt << 1 | 1);
  if (Max[rt << 1] <= Max[rt << 1 | 1]) {
    Max[rt] = Max[rt << 1 | 1];
    Maxid[rt] = Maxid[rt << 1 | 1];
  } else {
    Max[rt] = Max[rt << 1];
    Maxid[rt] = Maxid[rt << 1];
  }
}
inline int Query(int L, int R, int l, int r, int rt) {
  if (L <= l && R >= r) return Maxid[rt];
  int mid = l + r >> 1;
  int ans = 0, Max = 0;
  if (L <= mid) {
    int t = Query(L, R, l, mid, rt << 1);
    a[t] > Max ? Max = a[t], ans = t : 0;
  }
  if (R > mid) {
    int t = Query(L, R, mid + 1, r, rt << 1 | 1);
    a[t] >= Max ? Max = a[t], ans = t : 0;
  }
  return ans;
}
void Update(int x, int c, int l, int r, int rt) {
  if (l == r) {
    Max[rt] = c;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid)
    Update(x, c, l, mid, rt << 1);
  else
    Update(x, c, mid + 1, r, rt << 1 | 1);
  if (Max[rt << 1] <= Max[rt << 1 | 1]) {
    Max[rt] = Max[rt << 1 | 1];
    Maxid[rt] = Maxid[rt << 1 | 1];
  } else {
    Max[rt] = Max[rt << 1];
    Maxid[rt] = Maxid[rt << 1];
  }
}
bool Iskey[MAXN];
int val[MAXN];
bool Addkey(int x) {
  int d1 = 0, d2 = 0;
  x > 1 ? d1 = a[Query(max(1, x - k), x - 1, 1, n, 1)] : 0;
  x < n ? d2 = a[Query(x + 1, min(n, x + k), 1, n, 1)] : 0;
  if (a[x] >= d1 && a[x] > d2) {
    val[x] = d1 > d2 ? d1 : d2;
    Q.push(a[x] + val[x]);
    Iskey[x] = 1;
    return 1;
  }
  return 0;
}
int main() {
  // freopen("Sum.in", "r", freopen);
  // stdin("Sum.out", "w", stdout);
#ifdef Mine
  freopen("46.in", "r", stdin);
  freopen("46.ans", "w", stdout);
#endif
  n = read(), k = read();
  register int q = read(), op = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  Build(1, n, 1);
  for (int i = 1; i <= n; ++i) Addkey(i);
  register int lastans = 0;
  printf("%d\n", lastans = Q.top());
  while (q--) {
    op ? 0 : lastans = 0;
    int x = read() ^ lastans, y = read() ^ lastans;
    if (Iskey[x]) {
      Q.erase(a[x] + val[x]), Iskey[x] = 0;
      a[x] = y;
      Update(x, y, 1, n, 1);
      Addkey(Query(max(1, x - k), x, 1, n, 1));
      x < n ? Addkey(Query(x + 1, min(n, x + k), 1, n, 1)) : 0;
    } else {
      int d1 = 0, d2 = 0;
      x > 1 ? d1 = Query(max(1, x - k), x - 1, 1, n, 1) : 0;
      x < n ? d2 = Query(x + 1, min(n, x + k), 1, n, 1) : 0;
      (d1 && Iskey[d1]) ? Q.erase(a[d1] + val[d1]), Iskey[d1] = 0 : 0;
      (d2 && Iskey[d2]) ? Q.erase(a[d2] + val[d2]), Iskey[d2] = 0 : 0;
      a[x] = y;
      Update(x, y, 1, n, 1);
      bool t = Addkey(x);
      if (!t) {
        d1 ? Addkey(d1) : 0;
        d2 ? Addkey(d2) : 0;
      }
    }
    printf("%d\n", lastans = Q.top());
  }
}
