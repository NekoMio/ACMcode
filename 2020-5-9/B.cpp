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
const int MAXN = 5e5 + 5;
int t[MAXN], Num[8006];
long long Calc(int s, int k) {
  int R = 0;
  for (int l = 1, r = k; l <= r; r--) {
    R++;
    if (Num[l] + Num[r] <= s) l++;
  }
  return 1ll * s * R;
}
int main() {
  int n = read(), k = read();
  for (int i = 1; i <= n; i++) {
    t[i] = read();
    Num[t[i]]++;
  }
  sort(Num + 1, Num + k + 1);
  int MinS = Num[k], MaxS = Num[k];
  for (int i = 1; i * 2 <= k; i++) {
    MaxS = max(MaxS, Num[i] + Num[k - i + 1]);
  }
  long long Ans = 0x3f3f3f3f3f3f3f3f;
  for (int i = MinS; i <= MaxS; i++) {
    Ans = min(Ans, Calc(i, k));
  }
  printf ("%lld\n", Ans);
}