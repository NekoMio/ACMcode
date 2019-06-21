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
int f[MAXN], size[MAXN];
struct edge {
  int END, next;
}v[MAXN];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
struct cmp {
  bool operator ()(const int &a, const int &b) const {
    return size[a] < size[b];
  }
};
int tp[MAXN], cnt;
int Ans[MAXN], S[MAXN], E[MAXN];
priority_queue<int, vector<int>, cmp> Q;
void DFS(int rt) {
  size[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    DFS(v[i].END);
    size[rt] = max(size[rt], size[v[i].END] + 1);
  }
}
int main() {
  memset (first, -1, sizeof (first));
  int n = read(), m = read();
  for (int i = 2; i <= n; ++i) {
    f[i] = read();
    add(f[i], i);
  }
  DFS(1);
  Q.push(1);
  int ans = 0;
  for (ans = 1; !Q.empty(); ans++) {
    cnt = 0;
    S[ans] = E[ans - 1] + 1;
    E[ans] = S[ans] - 1;
    for (int i = 1; i <= m && !Q.empty(); ++i) {
      int k = Q.top();
      // cerr << k << endl;
      Ans[++E[ans]] = k;
      Q.pop();
      for (int j = first[k]; j != -1; j = v[j].next) {
        tp[++cnt] = v[j].END;
      }
    }
    for (int i = 1; i <= cnt; ++i)
      Q.push(tp[i]);
  }
  ans--;
  printf ("%d\n", ans);
  for (int i = 1; i <= ans; ++i) {
    printf ("%d ", E[i] - S[i] + 1);
    for (int j = S[i]; j <= E[i]; ++j)
      printf ("%d ", Ans[j]);
    printf ("\n");
  }
}
