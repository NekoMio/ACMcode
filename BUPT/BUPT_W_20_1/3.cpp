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
struct edge {
  int next, END;
}v[200005 * 2];
int first[200005], p, n;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int Size[200005];
long long Ans[200005];
void DFS1(int rt, int fa) {
  Size[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END != fa) { 
      DFS1(v[i].END, rt);
      Size[rt] += Size[v[i].END];
    }
  }
  if (rt != 1) Ans[1] += Size[rt];
}
void DFS2(int rt, int fa) {
  if (rt != 1) {
    Ans[rt] = Ans[fa] - Size[rt] + n - Size[rt];
  }
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END != fa) {
      DFS2(v[i].END, rt);
    }
  }
}
int main() {
  n = read();
  memset (first, -1, sizeof(first));
  int a, b;
  for (int i = 1; i < n; i++) {
    a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  DFS1(1, 0);
  DFS2(1, 0);
  long long Max = 0;
  for (int i = 1; i <= n; i++) Max = max(Max, Ans[i]);
  printf ("%lld\n", Max + n);
  // while (1);
}