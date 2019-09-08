#include <cstdio>
#include <cstring>
long long a, b, c, d, e, f, g, i, m, n, r, s, t;
char x[500000];
unsigned wa[500000] = {0}, wb[500000] = {0};
unsigned wc[500000] = {0}, wd[500000] = {0};
unsigned we[500000] = {0}, wf[500000] = {0};
unsigned ya = 131, yb = 1313;
long long za[500000][30] = {0}, zb[500000][30] = {0}, h;

unsigned Get_Hash(long long l, long long r, unsigned *Hash, unsigned *bin) {
  return Hash[r] - Hash[l - 1] * bin[r - l + 1];
}

void mi(long long &j, long long k) {
  if (j > k) j = k;
}

void ma(long long &j, long long k) {
  if (j < k) j = k;
}

int main() {
  // freopen("1.in","r",stdin);
  we[i] = 1;
  wf[i] = 1;
  for (i = 1; i <= 300000; i++) we[i] = we[i - 1] * ya;
  for (i = 1; i <= 300000; i++) wf[i] = wf[i - 1] * yb;
  scanf("%s", x);
  a = strlen(x);
  wa[0] = wb[0] = wc[0] = wd[0] = 0;
  for (i = 1; i <= a; i++) wa[i] = wa[i - 1] * ya + x[i - 1];
  for (i = 1; i <= a; i++) wb[i] = wb[i - 1] * yb + x[i - 1];
  for (i = 1; i <= a; i++) wc[i] = wc[i - 1] * ya + x[a - i];
  for (i = 1; i <= a; i++) wd[i] = wd[i - 1] * yb + x[a - i];
  for (i = 0; i < 26; i++) {
    za[0][i] = 0;
    zb[a + 1][i] = a + 1;
  }
  for (i = 1; i <= a; i++) {
    for (m = 0; m < 26; m++) {
      za[i][m] = za[i - 1][m];
    }
    za[i][x[i - 1] - 'a'] = i;
  }
  for (i = a; i >= 1; i--) {
    for (m = 0; m < 26; m++) {
      zb[i][m] = zb[i + 1][m];
    }
    zb[i][x[i - 1] - 'a'] = i;
  }
  h = 0;
  for (i = 1; i <= a; i++) {
    r = 0;
    s = a - i;
    mi(s, i - 1);
    while (r < s) {
      t = (r + s + 1) / 2;
      if ((Get_Hash(i - t, i - 1, wa, we) ==
           Get_Hash(a - (i + t) + 1, a - (i + 1) + 1, wc, we)) &&
          ((Get_Hash(i - t, i - 1, wb, wf) ==
            Get_Hash(a - (i + t) + 1, a - (i + 1) + 1, wd, wf))))
        r = t;
      else
        s = t - 1;
    }
    for (m = 0; m < 26; m++) {
      c = 0;
      if (i - r <= za[i][m]) ma(c, za[i][m] - (i - r) + 1);
      if (zb[i][m] <= i + r) ma(c, (i + r) - zb[i][m] + 1);
      h += c;
      // printf("%d %d  %d  %d %d %d\n",i,m,c,r,za[i][m],zb[i][m]);
    }
  }
  for (i = 1; i < a; i++) {
    if (x[i] == x[i - 1]) {
      r = 0;
      s = a - i - 1;
      mi(s, i - 1);
      while (r < s) {
        t = (r + s + 1) / 2;
        if ((Get_Hash(i - t, i, wa, we) ==
             Get_Hash(a - (i + t + 1) + 1, a - (i + 1) + 1, wc, we)) &&
            ((Get_Hash(i - t, i, wb, wf) ==
              Get_Hash(a - (i + t + 1) + 1, a - (i + 1) + 1, wd, wf))))
          r = t;
        else
          s = t - 1;
      }
      for (m = 0; m < 26; m++) {
        c = 0;
        if (i - r + 1 <= za[i][m]) ma(c, za[i][m] - (i - r + 1) + 1);
        if (zb[i + 1][m] <= i + r + 1) ma(c, (i + r + 1) - zb[i + 1][m] + 1);
        h += c;
        // printf("%d %d %d  %d  %d %d %d\n",h,i,m,c,r,za[i][m],zb[i+1][m]);
      }
    }
  }
  printf("%lld", h);
}