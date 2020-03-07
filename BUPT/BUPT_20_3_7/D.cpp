#include <cstdio>
#include <cstring>
long long a, b, c, d, e, f, g, i, m, n;
long long xa[200000] = {0}, xb[200000] = {0}, xc[200000] = {0};
char wa[200000], wb[200000];

int main() {
  scanf("%s%s", wa + 1, wb + 1);
  a = strlen(wa + 1);
  b = strlen(wb + 1);
  for (i = 2; i <= b; i++) {
    c = xb[i - 1];
    while ((c != 0) && (wb[c + 1] != wb[i])) c = xb[c];
    if (wb[c + 1] == wb[i])
      xb[i] = c + 1;
    else
      xb[i] = 0;
  }
  c = 1;
  m = 1;
  while ((m + 1 <= a) && (wa[m] == wa[m + 1])) m++;
  xa[2] = m - 1;
  for (i = 3; i <= a; i++) {
    if (xa[i - c + 1] + i < xa[c] + c)
      xa[i] = xa[i - c + 1];
    else {
      m = xa[c] + c - i;
      if (m < 0) m = 0;
      while ((i + m <= a) && (m + 1 <= b) && (wa[i + m] == wb[m + 1])) m++;
      xa[i] = m;
      c = i;
    }
  }
  for (i = 2; i <= a; i++) {
    xc[xa[i]]++;
    // printf("%lld %lld\n",i,xa[i]);
  }
  for (i = b; i >= 1; i--) {
    xc[i] += xc[i + 1];
    // printf("%lld %lld\n",i,xc[i]);
  }
  c = a * b;
  for (i = 1; i <= b; i++) {
    if (xb[i] > 0) c -= xc[i - xb[i]];
    // printf("%lld %lld %lld\n",i,xb[i],xc[i-xb[i]]);
  }
  printf("%lld\n", c);
}