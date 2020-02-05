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
long long S[200005];
int n;
long long Sum[200005];
#define lowbit(_) ((_) & (-_))
void Update (int x, long long c) {
  for (int i = x; i <= n; i+=lowbit(i)) {
    Sum[i] += c;
  }
}
long long Query(int x) {
  long long ans = 0;
  for (int i = x; i > 0; i-=lowbit(i)) {
    ans += Sum[i];
  }
  return ans;
}
int p[200005];
int main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    S[i] = read();
  }
  for (int i = 1; i <= n; i++) Update(i, i);
  int l, r, mid, ans;
  for (int i = n; i >= 1; i--) {
    l = 0, r = n + 1;
    while (l < r) {
      mid = l + r >> 1;
      if (Query(mid) <= S[i]) {
        ans = mid, l = mid + 1;
      } else {
        r = mid;
      }
    }
    p[i] = ans + 1;
    Update(p[i], -p[i]);
  }
  for (int i = 1; i <= n; i++) printf ("%d%c", p[i], " \n"[i == n]);
  // while (1);
}