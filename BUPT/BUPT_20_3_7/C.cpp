#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;
int xa[200000] = {0}, xb[200000] = {0};
int wa[200000] = {0}, wb[200000] = {0};
int main() {
  scanf("%d%d", &a, &b);
  for (i = 1; i <= b; i++) {
    scanf("%d%d", &wa[i], &wb[i]);
    xb[wa[i]]++;
    xb[wb[i]]++;
  }
  c = 0;
  for (i = 1; i <= a; i++) {
    if (xb[i] < a - 1) {
      c = i;
    }
  }
  if (c == 0)
    printf("NO\n");
  else {
    printf("YES\n");
    d = 0;
    for (i = 1; i <= b; i++) {
      if (wa[i] == c) {
        d++;
        xa[wb[i]] = d;
      }
      if (wb[i] == c) {
        d++;
        xa[wa[i]] = d;
      }
    }
    d++;
    xa[c] = d;
    for (i = 1; i <= a; i++) {
      if (xa[i] == 0) {
        d++;
        xa[i] = d;
      }
      printf("%d ", xa[i]);
    }
    printf("\n");
    xa[c]++;
    for (i = 1; i <= a; i++) {
      printf("%d ", xa[i]);
    }
    printf("\n");
  }
}