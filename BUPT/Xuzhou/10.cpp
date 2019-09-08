#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 1000006
using namespace std;
int n, zz, a[N];
struct ro {
  int to, next;
} road[N * 2];
void build(int x, int y) {
  zz++;
  road[zz].to = y;
  road[zz].next = a[x];
  a[x] = zz;
}
const int p = 1e9 + 7;
long long ksm(long long x, long long z) {
  long long ans = 1;
  while (z) {
    if (z & 1) ans = ans * x % p;
    x = x * x % p;
    z >>= 1;
  }
  return ans;
}
int fa[N], deep[N], mx;
void dfs(int x) {
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (y == fa[x]) continue;
    fa[y] = x;
    deep[y] = deep[x] + 1;
    dfs(y);
  }
}
long long f[N], inv[N];
void dfs2(int x) {
  if (deep[x] == mx) {
    f[x] = 1;
    return;
  }
  int js = 0;
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (y == fa[x]) continue;
    dfs2(y);
    js++;
  }
  long long tmp = 0;
  for (int i = a[x]; i; i = road[i].next) {
    int y = road[i].to;
    if (y == fa[x]) continue;
    tmp += (1 - f[y] + p) % p * inv[js] % p;
    tmp %= p;
  }
  f[x] = (1 - ksm(tmp, js) + p) % p;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    build(x, y);
    build(y, x);
  }
  //	cout<<endl;
  for (int i = 1; i <= n; i++) inv[i] = ksm(i, p - 2);
  deep[1] = 1;
  dfs(1);
  for (int i = 1; i <= n; i++)
    if (deep[i] > mx) mx = deep[i];
  dfs2(1);
  //	for(int i=1;i<=n;i++) cout<<f[i]<<' ';
  //	cout<<endl;
  printf("%lld", f[1]);
  return 0;
}