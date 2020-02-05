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
  int a, b;
}v1[1005], v2[1005];
int ans[1005];
int cnt1 = 0, cnt2 = 0;
bool Judge(int x) {
  for (int i = v2[x].a; i < v2[x].b; i++) {
    if (ans[i] > ans[i + 1]) return 1;
  }
  return 0;
}
bool vis[1005];
int main() {
  int n = read(), m = read();
  int t, a, b;
  for (int i = 1; i <= m; i++) {
    t = read(), a = read(), b = read();
    if (t == 1) v1[++cnt1].a = a, v1[cnt1].b = b;
    else v2[++cnt2].a = a, v2[cnt2].b = b;
  }
  for (int i = 1; i <= n; i++) {
    ans[i] = i;
  }
  for (int i = 1; i <= cnt1; i++) {
    for (int j = v1[i].a; j < v1[i].b; j++) {
      vis[j] = 1;
    }
  }
  bool flag = 0;
  for (int i = 1; i <= cnt2; i++) {
    if (!Judge(i)) {
      int t = -1;
      for (int j = v2[i].a; j < v2[i].b; j++) {
        if (!vis[j]) {
          t = j + 1;
          break;
        }
      }
      if (t == -1) {
        flag = 1;
        break;
      } else {
        for (int j = t; j <= n; j++) {
          ans[j] -= 2;
        }
      }
    }
  }
  if (flag) printf ("NO\n");
  else {
    printf ("YES\n");
    for (int i = 1; i <= n; i++) {
      printf ("%d ", ans[i] + 2000);
    }
    printf ("\n");
  }
  // while (1);
}