#pragma GCC optimize("O3")
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
const int MAXN = 50005;
const int MAXM = 100005;
struct data {
  int i, hi, j, hj;
} D[MAXM];
struct edge {
  int END, next;
} v[MAXM << 2];
int first[MAXN << 1], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
char tmp[2][5];
char S[MAXN];
int id[10];
int ID(int x, int y) {
  if (S[x] - 'a' == y) return 0;
  if (S[x] == 'a') return x * 2 + y - 1;
  else if (S[x] == 'b') return x * 2 + y / 2;
  else return x * 2 + y;
}
int dfn[MAXN << 1], low[MAXN << 1], Index, belong[MAXN << 1], T;
bool vis[MAXN << 1];
int st[MAXN << 1], top;
void Tarjan(int rt) {
  dfn[rt] = low[rt] = ++Index;
  st[++top] = rt;
  vis[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!dfn[v[i].END]) {
      Tarjan(v[i].END);
      low[rt] = min(low[rt], low[v[i].END]);
    } else if (vis[v[i].END])
      low[rt] = min(low[rt], dfn[v[i].END]);
  }
  if (low[rt] == dfn[rt]) {
    T++;
    int x;
    do {
      x = st[top--];
      vis[x] = 0;
      belong[x] = T;
    } while (low[x] != dfn[x]);
  }
}
bool Calc(int n, int m) {
  memset(first, -1, sizeof(first)), p = 0;
  memset(dfn, 0, sizeof(dfn));
  memset(low, 0, sizeof(low));
  memset(belong, 0, sizeof(belong));
  T = Index = 0;
  for (int i = 1; i <= m; ++i) {
    int t1 = ID(D[i].i, D[i].hi);
    int t2 = ID(D[i].j, D[i].hj);
    if (t1) {
      if (t2) add(t1, t2), add(t2 ^ 1, t1 ^ 1);
      else add(t1, t1 ^ 1);
    }
  }
  for (int i = 2; i <= 2 * n + 1; ++i) {
    if (!dfn[i]) Tarjan(i);
    if (i & 1) {
      if (belong[i] == belong[i - 1]) return 0;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (belong[2 * i] < belong[2 * i + 1]) {
      if (S[i] == 'a') printf("B");
      if (S[i] == 'b') printf("A");
      if (S[i] == 'c') printf("A");
    } else {
      if (S[i] == 'a') printf("C");
      if (S[i] == 'b') printf("C");
      if (S[i] == 'c') printf("B");
    }
  }
  printf("\n");
  return 1;
}
int main() {
  int n = read(), d = read();
  scanf("%s", S + 1);
  int x = 0;
  int m = read();
  for (int i = 1; i <= m; ++i) {
    scanf("%d%s%d%s", &D[i].i, tmp[0], &D[i].j, tmp[1]);
    D[i].hi = tmp[0][0] - 'A';
    D[i].hj = tmp[1][0] - 'A';
  }
  for (int i = 1; i <= n; ++i)
    if (S[i] == 'x') id[++x] = i;
  int N = (1 << d) + 1;
  for (int i = 0; i <= N; ++i) {
    for (int j = 1; j <= x; ++j)
      if (i & (1 << (j - 1))) S[id[j]] = 'a';
      else S[id[j]] = 'b';
    if (Calc(n, m)) return 0;
  }
  return printf("-1\n"), 0;
}