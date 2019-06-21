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
const int MAXN = 1000005;
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p, du[MAXN];
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
#define data pair<int, int>
queue<data> Q;
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), k = read();
  for (int i = 1; i < n; ++i) {
    int a = read(), b = read();
    du[a]++, du[b]++;
    add(a, b);
    add(b, a);
  }
  for (int i = 1; i <= n; ++i)
    if (du[i] == 1 || du[i] == 0)
      Q.push(data(i, 0));
  int ans = 0;
  for (int i = 1; i <= k / 2; i++) {
    while (!Q.empty() && Q.front().second < i) {
      int t = Q.front().first;
      Q.pop();
      ans++;
      for (int j = first[t]; j != -1; j = v[j].next) {
        du[v[j].END]--;
        if (du[v[j].END] == 1)
          Q.push(data(v[j].END, i));
      }
    }
  }
  if ((k & 1) && Q.size()) ans++; 
  printf ("%d\n", ans);
}
