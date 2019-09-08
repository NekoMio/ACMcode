#include <cstdio>
#include <cstring>
int a, b, c, d, e, f, g, i, m, n;
char xa[200000], xb[200000];
unsigned wa[200000] = {0}, wb[200000] = {0};
unsigned wc[200000] = {0}, wd[200000] = {0};
unsigned we[200000] = {0}, wf[200000] = {0};
unsigned ya = 131, yb = 1313;

unsigned Get_Hash(int l, int r, unsigned *Hash, unsigned *bin) {
  if (l > 0) return Hash[r] - Hash[l - 1] * bin[r - l + 1];
  return Hash[r];
}

int main() {
  we[i] = 1;
  wf[i] = 1;
  for (i = 1; i <= 100000; i++) we[i] = we[i - 1] * ya;
  for (i = 1; i <= 100000; i++) wf[i] = wf[i - 1] * yb;
  scanf("%s", xa);
  a = strlen(xa);
  for (i = 0; i < a; i++) wa[i] = wa[i - 1] * ya + xa[i];
  for (i = 0; i < a; i++) wb[i] = wb[i - 1] * yb + xa[i];
  scanf("%d", &c);
  for (n = 1; n <= c; n++) {
    scanf("%s", xb);
    b = strlen(xb);
    if (a == b) {
      d = 0;
      for (i = 0; i < a; i++) {
        if (xa[i] != xb[i]) d = 1;
      }
      if (d == 0)
        puts("jntm!");
      else
        puts("friend!");
    } else {
      for (i = 0; i < b; i++) wc[i] = wc[i - 1] * ya + xb[i];
      for (i = 0; i < b; i++) wd[i] = wd[i - 1] * yb + xb[i];
      if (a > b) {
        d = 0;
        for (i = 0; i + b <= a; i++) {
          if ((wc[b - 1] == Get_Hash(i, i + b - 1, wa, we)) &&
              (wd[b - 1] == Get_Hash(i, i + b - 1, wb, wf))) {
            d = 1;
            i = a + 10;
          }
        }
        if (d == 1)
          puts("my child!");
        else
          puts("oh, child!");
      } else {
        d = 0;
        for (i = 0; i + a <= b; i++) {
          if ((wa[a - 1] == Get_Hash(i, i + a - 1, wc, we)) &&
              (wb[a - 1] == Get_Hash(i, i + a - 1, wd, wf))) {
            d = 1;
            i = a + 10;
          }
        }
        if (d == 1)
          puts("my teacher!");
        else
          puts("senior!");
      }
    }
  }
}