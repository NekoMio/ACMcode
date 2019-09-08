#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;
char xa[2000000], xb[2000000];
int w[1000005][26] = {0};

void ma(int &j, int k) {
  if (j < k) j = k;
}

int main() {
  scanf("%d%d", &a, &b);
  scanf("%s%s", xa, xb);
  c = 0;
  d = -1;
  for (i = 0; i < 26; i++) {
    w[a][i] = a;
  }
  for (i = a - 1; i >= 0; i--) {
    for (m = 0; m < 26; m++) {
      w[i][m] = w[i + 1][m];
      if (xa[i] - 'a' > m) w[i][m] = i;
    }
  }
  for (i = 0; i < a; i++) {
    e = w[i][xb[c] - 'a'];
    // printf("%d %d %d %d\n",i,c,e,d);
    if (e < a) ma(d, c + a - e);
    if (xa[i] == xb[c]) {
      c++;
      if (c == b) {
        if (i + 1 < a) ma(d, c + a - i - 1);
        i = a + 10;
      }
    }
  }
  printf("%d\n", d);
}