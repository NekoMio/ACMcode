#include <bits/stdc++.h>
using namespace std;
map<int, unsigned long long> Val;
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
const int MAXP = 1e4;
int prime[MAXP], cnt;
bool isnprime[MAXP];
unsigned long long val[MAXP];
void Get_Prime() {
  isnprime[1] = 1;
  for (int i = 2; i <= MAXP; i++) {
    if (!isnprime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt; j++) {
      if (i * prime[j] > MAXP) break;
      isnprime[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
const int MAXN = 100005;
struct edge {
  int END, next;
  unsigned long long v;
} v[MAXN << 1];
int first[MAXN], p;
void add(int a, int b, int w) {
  v[p].END = b;
  v[p].next = first[a];
  for (int i = 1; i <= cnt; i++) {
    while (w % prime[i] == 0) {
      w /= prime[i];
      v[p].v ^= val[i];
    }
  }
  if (w != 1) {
    if (!Val[w]) Val[w] = (1ll * rand() << 32) | rand();
    v[p].v ^= Val[w];
  }
  first[a] = p++;
  v[p].END = a;
  v[p].next = first[b];
  v[p].v = v[p - 1].v;
  first[b] = p++;
}
long long ans = 0;
unsigned long long dis[MAXN];
void DFS(int rt, int fa) {
  for (int i = first[rt]; i != -1; i = v[i].next) {
    if (v[i].END == fa) continue;
    dis[v[i].END] = dis[rt] ^ v[i].v;
    DFS(v[i].END, rt);
  }
}
int main() {
  Get_Prime();
  // printf ("%d\n", cnt);
  for (int i = 1; i <= cnt; i++) val[i] = ((1ll * rand() << 32) | rand());
  memset(first, -1, sizeof(first));
  int n = read();
  for (int i = 1; i < n; i++) {
    int a = read(), b = read(), w = read();
    add(a, b, w);
  }
  DFS(1, 0);
  int num = 0;
  sort(dis + 1, dis + n + 1);
  // for (int i = 1; i <= n; i++) {
    // printf ("%llu\n", dis[i]);
  // }
  num = 1;
  for (int i = 2; i <= n; i++) {
    if (dis[i] != dis[i - 1]) {
      ans = ans + 1ll * num * (num - 1);
      num = 0;
    }
    num++;
  }
  ans = ans + 1ll * num * (num - 1);
  printf ("%lld\n", ans);
}
