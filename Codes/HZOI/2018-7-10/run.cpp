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
inline char readchar() {
  char ch = getchar();
  while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')))
    ch = getchar();
  return ch;
}
const int MAXN = 2005;
int a[MAXN][MAXN], n;
int F[MAXN][MAXN];
#define lowbit(_) ((_) & (-_))
struct BIT_TREE {
  int Sum[MAXN];
  void Add(int x, int c) {
    for (register int i = x; i <= n; i += lowbit(i))
      Sum[i] += c;
  }
  int Query(int x) {
    int ans = 0;
    for (register int i = x; i >= 1; i -= lowbit(i))
      ans += Sum[i];
    return ans;
  }
}bit[MAXN];
long long Sum;
long long DP() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      F[i][j] = max(F[i - 1][j], F[i][j - 1]) + a[i][j];
  Sum = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      Sum = Sum + F[i][j];
  return Sum;
}
inline int f(int x, int y) {
  return F[x][y] + bit[x].Query(y);
}
long long Calc(int x, int y, int c) {
  int l = y, r = n;
  for (int i = l; i <= n; ++i) {
    int tp = max(f(x - 1, i), f(x, i - 1)) + a[x][i];
    if (tp != f(x, i)) {
      bit[x].Add(i, c);
      bit[x].Add(i + 1, -c);
    } else {
      r = i - 1;
      break;
    }
  }
  Sum = Sum + (r - l + 1) * c;
  for (int i = x + 1; i <= n; ++i) {
    while (max(f(i - 1, l), f(i, l - 1)) + a[i][l] == f(i, l) && l <= n) l++;
    while (max(f(i - 1, r), f(i, r - 1) + c) + a[i][r] != f(i, r) && r <= n) r++;
    r--;
    if (r < l) { break; }
    else {
      bit[i].Add(l, c);
      bit[i].Add(r + 1, -c);
      Sum = Sum + (r - l + 1) * c;
    }
  }
  return Sum;
}
int main() {
  // freopen ("run.in", "r", stdin);
  // freopen ("run.out", "w", stdout);
  n = read();
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      a[i][j] = read();
  printf ("%lld\n", DP());
  for (int i = 1; i <= n; ++i) {
    char op = readchar();
    int x = read(), y = read();
    if (op == 'D') {
      a[x][y]--;
      printf ("%lld\n", Calc(x, y, -1));
    }
    else {
      a[x][y]++;
      printf ("%lld\n", Calc(x, y, 1));
    }
  }
}
