#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
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
const int MAXN = 2e5 + 5;
int a[MAXN], cnt;
struct data {
  int id, v;
}b[MAXN];
long long Sum[MAXN];
int Num[MAXN];
#define lowbit(_) ((_) & (-_))
void add(int x, int c) {
  for (int i = x; i <= cnt; i += lowbit(i)) Sum[i] += c, Num[i]++;
}
long long Query(int x) {
  long long ans = 0;
  for (int i = x; i > 0; i -= lowbit(i))
    ans += Sum[i];
  return ans;
}
int query(int x) {
  int ans = 0;
  for (int i = x; i > 0; i -= lowbit(i))
    ans += Num[i];
  return ans;
}
int r, s, t;
long long su;
bool cmp (const data &A, const data &B) {
  return A.v == B.v ? A.id < B.id : A.v < B.v;
}
int main() {
  int Q = read();
  while (Q--) {
    memset (Sum, 0, sizeof (Sum));
    memset (Num, 0, sizeof (Num));
    memset (b, 0, sizeof (b));
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) b[i].v = a[i] = read(), b[i].id = i;
    sort(b + 1, b + n + 1, cmp);
    for (int i = 1; i <= n; i++)
      a[b[i].id] = i;
    cnt = n;
    for (int i = 1; i <= n; i++) {
      r = 0;
      s = cnt;
      while (r < s) {
        t = (r + s + 1) / 2;
        su = Query(t);
        // printf("%d %d %d %d %lld\n",i,t,r,s,su + b[a[i]]);
        if (su + b[a[i]].v > m)
          s = t - 1;
        else
          r = t;
      }
      // printf("==%d %d %d\n",i,r,query(r));
      printf ("%d ", i - query(r) - 1);
      add(a[i], b[a[i]].v);
    }
    printf("\n");
  }
  // while (1);
}