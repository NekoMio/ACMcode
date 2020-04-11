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
priority_queue<int, vector<int>, greater<int>> Q;
map<int,int> flag;
int main() {
  int T = read();
  while (T--) {
    int n = read(), a, b;
    flag.clear();
    long long ans1 = 0;
    int ans2 = 0;
    for (int i = 1; i <= n; i++) {
      a = read();
      // if (!Q.empty()) printf ("%d\n", Q.top());
      if (!Q.empty() && a > Q.top()) {
        b = Q.top();
        Q.pop();
        ans1 += a - b;
        Q.push(a);
        if (!flag[b]) {
          // printf ("%d\n", i);
          ans2 += 2;
        } else {
          flag[b]--;
        }
        flag[a]++;
      }
      Q.push(a);
    }
    while (!Q.empty()) Q.pop();
    printf ("%lld %d\n", ans1, ans2);
  }
}