#include <bits/stdc++.h>
using namespace std;
int vet[20005], t;
int num[3] = {0, 4, 7};
int bin[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
void DFS(int base, int dep) {
  if (dep == 9) return;
  for (int i = 0; i <= 2; i++) {
    vet[++t] = base + bin[dep] * num[i];
    if (i != 0)
      DFS(base + bin[dep] * num[i], dep + 1);
  }
}
int Mer(int L, int R, int l, int r) {
  if (R < l || r < L) return 0;

  if (L <= l && R <= r) return R - l + 1;
  if (l <= L && r <= R) return r - L + 1;
  if (L <= l && r <= R) return r - l + 1;
  if (l <= L && R <= r) return R - L + 1;
  return 0;
}
long long Calc(int L, int R, int l, int r, int k) {
  int start = lower_bound(vet + 1, vet + t + 1, L) - vet;
  long long ret = 0;
  for (int i = start - 1; vet[i] < R && i + k <= t; i++) {
    ret += 1ll * Mer(vet[i] + 1, vet[i + 1], L, R) * Mer(vet[i + k], vet[i + k + 1] - 1, l, r);
  }
  return ret;
}
int main() {
  int pl, pr, vl, vr, k;
  scanf ("%d%d%d%d%d", &pl, &pr, &vl, &vr, &k);
  // printf("----------\n");
  DFS(4, 1);
  DFS(7, 1);
  sort(vet + 1, vet + t + 1);
  t = unique(vet + 1, vet + t + 1) - vet - 1;
  vet[t + 1] = 0x3f3f3f3f;
  // for (int i = 1; i <= t; i++) printf ("%d\n", vet[i]);
  long long ans = 0;
  ans += Calc(pl, pr, vl, vr, k);
  ans += Calc(vl, vr, pl, pr, k);
  if (k == 1) {
    for (int i = 1; i <= t; i++)
      if (vet[i] <= pr && vet[i] >= pl && vet[i] <= vr && vet[i] >= vl)
        ans--;
  }
  // printf ("%d\n", ans);
  printf ("%.9f\n", 1.0 * ans / (1. * (pr - pl + 1) * (vr - vl + 1)));
}