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
struct edge {
  int END, next;
}v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b) {
  v[p].END = b;
  v[p].next = first[a];
  first[a] = p++;
}
int prime[MAXN], cnt;
bool isnprime[MAXN];
void Get_Prime(int n) {
  isnprime[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isnprime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt; j++) {
      if (i * prime[j] > n) break;
      isnprime[i * prime[j]] = 1;
      if (i % prime[j] == 0) break; 
    }
  }
}
int Max[MAXN], sum, size[MAXN], root, d[MAXN];
bool vis[MAXN];
void Get_Root(int rt, int fa) {
  size[rt] = 1, Max[rt] = 0;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!vis[v[i].END] && v[i].END != fa) {
      Get_Root(v[i].END, rt);
      size[rt] += size[v[i].END];
      Max[rt] = max(Max[rt], size[v[i].END]);
    }
  }  
  Max[rt] = max(Max[rt], sum - size[rt]);
  if (Max[rt] < Max[root]) root = rt;
}
long long ans = 0;
int H[MAXN], tot, Num[MAXN];
void DFS(int rt, int fa) {
  H[++tot] = d[rt];
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!vis[v[i].END] && v[i].END != fa) {
      d[v[i].END] = d[rt] + 1;
      DFS(v[i].END, rt);
    }
  }
}
int 
long long Calc(int rt, int v) {
  d[rt] = v;
  long long Ans = 0;
  tot = 0;
  DFS(rt, 0);
  sort(H + 1, H + tot + 1);
  // memset (Num, 0, sizeof (Num[0]) * (H[tot] + 1));
  for (int i = 1; i <= tot; i++)
    Num[H[i]]++;
  for (int i = tot; i >= 1; i--) {
    Num[H[i]]--;
    for (int j = 1; j <= cnt && prime[j] - H[i] <= H[i]; j++)
      if (prime[j] - H[i] >= 0)
        Ans += Num[prime[j] - H[i]];
  }
  return Ans;
}
void Solve(int rt) {
  ans += Calc(rt, 0);
  vis[rt] = 1;
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (!vis[v[i].END]) {
      ans -= Calc(v[i].END, 1);
      root = 0, sum = size[v[i].END];
      Get_Root(v[i].END, 0);
      Solve(root);
    }
  }
}
int main() {
  int n = read();
  Get_Prime(n);
  memset (first, -1, sizeof (first));
  for (int i = 1; i < n; i++) {
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }
  Max[0] = sum = n;
  root = 0;
  Get_Root(1, 0);
  Solve(root);
  printf ("%.7f", 2.0 * ans / (1.0 * n * (n - 1)));
  // while (1);
}