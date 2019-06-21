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
  int END, next;
}v[100005];
int first[100005], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int ans = 0;
int du[100005];
int st[100005], top;
void DFS(set<int> Q) {
  if (Q.empty()) {
    for (int i = 1; i <= top; ++i)
      printf ("%d ", st[i]);
    printf ("\n");
    ans++;
    return;
  }
  for (auto x : Q) {
    set<int> tp = Q;
    tp.erase(x);
    st[++top] = x;
    for (int i = first[x]; i != -1; i = v[i].next) {
      du[v[i].END]--;
      if (du[v[i].END] == 0)
        tp.insert(v[i].END);
    } 
    DFS(tp);
    for (int i = first[x]; i != -1; i = v[i].next)
      du[v[i].END]++;
    top--;
  }
}
int main() {
  memset (first, -1, sizeof (first));
  set<int> Q;
  int n = read(), m = read();
  for (int i = 1; i <= m; ++i) {
    int a = read(), b = read();
    add(a, b);
    du[b]++;
  }
  for (int i = 0; i < n; ++i)
    if (!du[i])
      Q.insert(i);
  DFS(Q);
  printf ("%d\n", ans);
}
