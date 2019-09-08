#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 100005
using namespace std;
int n, Q, a;
int A[N];
long long p = 100003;
long long ksm(long long x, long long z) {
  long long ans = 1;
  while (z) {
    if (z & 1) ans = ans * x % p;
    x = x * x % p;
    z >>= 1;
  }
  return ans;
}
long long ans;
void dfs(int sum, int x, int cnt) {
  if (!cnt) {
    ans += (ksm(a, sum) - 1 + p) * ksm(a - 1, p - 2) % p;
    ans %= p;
    return;
  }
  if (x > n) return;
  dfs(sum, x + 1, cnt);
  dfs(sum + A[x], x + 1, cnt - 1);
}
void work(int x) {
  ans = 0;
  dfs(0, 1, x);
  printf("%lld\n", ans);
}
int main() {
  scanf("%d%d%d", &n, &a, &Q);
  for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
  for (int i = 1; i <= Q; i++) {
    int x;
    scanf("%d", &x);
    work(x);
  }
  while (1);
  return 0;
}
/*
2
5
2
42

3
4
2
1

5
1
2
2
3

*/
