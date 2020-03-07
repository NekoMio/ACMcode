#include <bits/stdc++.h>
using namespace std;
int vet[20005], t;
int num[3] = {0, 4, 7};
int bin[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
void DFS(int base, int dep) {
  if (dep == 9) return;
  for (int i = 0; i <= 2; i++) {
    vet[++t] = base + bin[dep] * num[i];
    DFS(base + bin[dep] * num[i], dep + 1);
  }
}
int Mer(int L, int R, int l, int r) {
  if (R <= l || r <= l) return 0;

  if (L <= l && R <= r) return R - l + 1;
  if (l <= L && r <= R) return r - L + 1;
  if (L <= l && r <= R) return r - l + 1;
  if (l <= L && R <= l) return R - L + 1;
  return 0;
}
long long Calc(int L, int R, int l, int r, int k) {
  int start = lower_bound(vet + 1, vet + t + 1, L) - vet;
  long long ret = 0;
  for (int i = start - 1; vet[i] < R; i++) {
    ret += 1ll * Mer(vet[i] + 1, vet[i + 1], L, R) * Mer(vet[i + k], vet[i + k + 1] - 1, l, r);
  }
  return ret;
}
int main() {
  int pl, pr, vl, vr, k;
  scanf ("%d%d%d%d%d", &pl, &pr, &vl, &vr, &k);
  printf("----------\n");
  DFS(4, 1);
  DFS(7, 1);
  sort(vet + 1, vet + t + 1);
  long long ans = 0;
  ans += Calc(pl, pr, vl, vr, k);
  ans += Calc(vl, vr, pl, pr, k);
  printf ("%d\n", ans);
  printf ("%.9f\n", 1.0 * ans / (1. * (pr - pl + 1) * (vr - vl + 1)));
}