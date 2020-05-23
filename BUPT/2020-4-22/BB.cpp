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
long long C[13];
struct data {
  int x, y, c;
  bool operator == (const data &a) {
    return x == a.x && y == a.y;
  }
}a[100005];
struct cmp{
    bool operator() (int c, int d) const {
        return a[c].y < a[d].y;
    }
};
priority_queue<int, vector<int>, cmp> pq;
int main() {
  int T = read();
  while (T--) {
    int n = read(), K = read();
    for (int i = 1; i <= K; i++) {
      a[i].x = read(), a[i].y = read();
      a[i].c = 1;
    }
    sort(a + 1, a + K + 1, [](const data &a1, const data &a2) -> bool{
      return a1.x == a2.x ? a1.y < a2.y : a1.x < a2.x;
    });
    int Q = read(), ans = 0;
    long long Sum = 0;
    for (int i = 1; i <= Q; i++) {
        scanf ("%lld", &C[i]);
        while (!pq.empty()) pq.pop();
        ans = 0;
        int j = 1;
        Sum = 0;
        for (int x = 1, y = n; x <= n; x++) {
            while (a[j].x < x && j <= K) j++;
            while (j <= K && a[j].x == x && a[j].y <= y) {
                pq.push(j);
                Sum += a[j].x, Sum += a[j].y;
                j++;
            }
            while (1ll * (y + x) * pq.size() - Sum > C[i] && y > 0) {
                while (!pq.empty() && a[pq.top()].y == y) {
                    Sum -= a[pq.top()].x;
                    Sum -= a[pq.top()].y;
                    pq.pop();
                }
                y--;
            }
            if (1ll * (y + x) * pq.size() - Sum == C[i]) ans++;
        }
        printf ("%d%c", ans, " \n"[i == Q]);
    }
  }
  // printf ("%.2f\n", 1.0 * clock() / CLOCKS_PER_SEC);
}