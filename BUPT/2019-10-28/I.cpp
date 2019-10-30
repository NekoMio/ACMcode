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
const int MAXN = 1e5 + 5;
long long a[MAXN], Sum[MAXN];
long long ans[MAXN];
int main() {
  int T = read();
  while (T--) {
    int n = read();
    for (int i = 2; i <= n; i++)
      a[i] = read();
    memset (Sum, 0, sizeof(Sum));
    for (int i = 2; i <= n; i++)
      Sum[i] = Sum[i - 1] + a[i];
    int l = 1, r = n, cnt = 2;
    long long tmp = Sum[n];
    long long Ans = Sum[n];
    ans[1] = 0;
    ans[2] = Sum[n];
    while (cnt < n) {
      cnt++;
      if (cnt & 1) {
        l++;
        Ans += tmp;
      } else {
        r--;
        tmp += Sum[r] - Sum[l];
        Ans += tmp;
      }
      ans[cnt] = Ans;
    }
    printf("0");
    for(int i = 2;i <= n;++i)
      printf(" %lld",ans[i]);
    printf ("\n");
  }
  // while (1);
}