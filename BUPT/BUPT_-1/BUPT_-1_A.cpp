#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
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
const int MAXN = 65537;
int du[MAXN], S[MAXN], m;
struct Edge {
  int a, b;
}v[65537];
queue<int> Q;
void add(int a, int b) {
  v[++m].a = a;
  v[m].b = b;
}
int main() {
  int n = read();
  for (int i = 0; i < n; i++) {
    du[i] = read(), S[i] = read();
    if (du[i] == 1) Q.push(i);
  }
  while (!Q.empty()) {
    int k = Q.front();
    Q.pop();
    if (du[k] == 0) continue;
    int t = S[k];
    add(k, t);
    du[t]--;
    S[t] ^= k;
    if (du[t] == 1) Q.push(t);
  }
  printf ("%d\n", m);
  for (int i = 1; i <= m; ++i) {
    printf ("%d %d\n", v[i].a, v[i].b);
  }
  // while (1);
}