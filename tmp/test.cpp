#include <bits/stdc++.h>
using namespace std;
int st[103], n;
#define lcm(_, __) ((_) / __gcd(_, __) * (__))
void DFS(int Sum, int LCM, int dep) {
  if (dep == n + 1) {
    if (Sum == LCM) {
      for (int i = 1; i <= n; i++) {
        printf ("%d ", st[i]);
      }
      printf ("\n");
      fflush(stdout);
      // exit(0);
    }
    return;
  }
  for (int i = st[dep - 1] + 1; i <= 100; i++) {
    st[dep] = i;
    DFS(Sum + i, lcm(LCM, i), dep + 1);
  }
}
int main() {
  scanf ("%d", &n);
  DFS(0, 1, 1);
}