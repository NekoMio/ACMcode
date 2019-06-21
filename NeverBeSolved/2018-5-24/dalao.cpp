// #pragma GCC optimize("O2")
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
int n;
const int MAXN = 2e6 + 5;
long long seed;
long long Rand() {
  return seed = ((seed * 19260817) ^ 233333) & ((1 << 24) - 1);
}
struct data {
  int a, b, c;
  bool operator<(const data &d) const { return a < d.a; }
} a[MAXN], tmp[MAXN];
bool cmp(const data &x, const data &y) {
  return x.b < y.b;
}
#define lowbit(_) ((_) & (-_))
int Sum[MAXN];
void add(int x) {
  for (int i = x; i <= n; i += lowbit(i))
    ++Sum[i];
}
long long Query(int x) {
  long long ans = 0;
  for (int i = x; i >= 1; i -= lowbit(i))
    ans += Sum[i];
  return ans;
}
long long ans = 0;
int main() {
  n = read();
  seed = read();
  for (int i = 1; i <= n; i++) a[i].a = i;
  for (int i = 1; i <= n; i++) swap(a[i].a, a[Rand() % i + 1].a);
  seed = read();
  for (int i = 1; i <= n; i++) a[i].b = i;
  for (int i = 1; i <= n; i++) swap(a[i].b, a[Rand() % i + 1].b);
  seed = read();
  for (int i = 1; i <= n; i++) a[i].c = i;
  for (int i = 1; i <= n; i++) swap(a[i].c, a[Rand() % i + 1].c);
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    ans += Query(a[i].b);
    add(a[i].b);
  }
  memset (Sum, 0, sizeof (Sum));
  for (int i = 1; i <= n; i++) {
    ans += Query(a[i].c);
    add(a[i].c);
  }
  memset (Sum, 0, sizeof (Sum));
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    ans += Query(a[i].c);
    add(a[i].c);
  }
  printf("%lld\n", (ans - 1ll * n * (n - 1) / 2) / 2);
}
