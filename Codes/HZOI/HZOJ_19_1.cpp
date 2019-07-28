#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005, MAXM = 200050;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
  while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
  return x * f;
}
struct data {
  int END, next, v;
}v[MAXM];
int first[MAXN], p;
void add(int a, int b, int x) {
  v[p].END = b;
  v[p].next = first[a];
  v[p].v = x;
  first[a] = p++;
}
double Dis[MAXN];
bool flag[MAXN];
queue<int> q;
void Spfa(int S) {
  memset (Dis, 0x7f, sizeof (Dis));
  flag[S] = 1;
  q.push(S);
  Dis[S] = 100;
  while (!q.empty()) {
    int k = q.front();
    q.pop();
    flag[k] = 0;
    for (int i = first[k]; i != -1; i = v[i].next) {
      if (Dis[v[i].END] >  Dis[k] / ((100.0 - v[i].v) / 100)) {
        Dis[v[i].END] = Dis[k] / ((100.0 - v[i].v) / 100);
        if (!flag[v[i].END]) {
          flag[v[i].END] = 1;
          q.push(v[i].END);
        }
      }
    }
  }
}
int main() {
  memset(first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int a = read(), b = read(), c = read();
    add(a, b, c);
    add(b, a, c);
  }
  int A = read(), B = read();
  Spfa(B);
  printf ("%.8f\n", Dis[A]);
  // while (1);
}