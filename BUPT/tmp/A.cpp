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
bool flag[100005];
int a[100005];
struct cmp{
  bool operator() (int c, int d) {
    return a[c] == a[d] ? flag[c] < flag[d] : a[c] > a[d];
  }
};
priority_queue<int, vector<int>, cmp> Q;
int main() {
  int T = read();
  while (T--) {
    int n = read(), b;
    memset (flag, 0, sizeof (flag));
    long long ans1 = 0;
    int ans2 = 0;
    for (int i = 1; i <= n; i++) {
      a[i] = read();
      // if (!Q.empty()) printf ("%d\n", Q.top());
      if (!Q.empty() && a[i] > a[Q.top()]) {
        b = Q.top();
        Q.pop();
        ans1 += a[i] - a[b];
        Q.push(i);
        if (!flag[b]) {
          printf ("%d\n", i);
          ans2 += 2;
        } else {
          flag[b] = 0;
        }
        flag[i] = 1;
      }
      Q.push(i);
    }
    while (!Q.empty()) Q.pop();
    printf ("%lld %d\n", ans1, ans2);
  }
}