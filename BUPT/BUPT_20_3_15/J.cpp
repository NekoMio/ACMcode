#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;
int ra, rb, rc, rd, sa, sb, sc, sd;
int y = 1111111111;

void jh(int &j, int &k) {
  int l;
  l = j;
  j = k;
  k = l;
}

int bj(int j, int k) {
  if (j == k) return 1;
  if (j > k)
    printf("-1\n");
  else
    printf("1\n");
  return 0;
}

int main() {
  scanf("%d", &a);
  for (i = 1; i <= a; i++) {
    scanf("%d%d", &b, &c);
    scanf("%d", &ra);
    ra += 2;
    rb = rc = rd = y;
    if (b >= 2) {
      scanf("%d", &rc);
      rc++;
    }
    if (b == 3) scanf("%d", &rd);
    scanf("%d", &sa);
    sa += 2;
    sb = sc = sd = y;
    if (c >= 2) {
      scanf("%d", &sc);
      sc++;
    }
    if (c == 3) scanf("%d", &sd);
    if (ra > rb) jh(ra, rb);
    if (rc > rd) jh(rc, rd);
    if (sa > sb) jh(sa, sb);
    if (sc > sd) jh(sc, sd);
    if ((ra > rc) || ((ra == rc) && (rb > rd))) {
      jh(ra, rc);
      jh(rb, rd);
    }
    if ((sa > sc) || ((sa == sc) && (sb > sd))) {
      jh(sa, sc);
      jh(sb, sd);
    }
    // printf("%d %d %d %d\n",ra,rb,rc,rd);
    // printf("%d %d %d %d\n",sa,sb,sc,sd);
    if (bj(ra, sa)) {
      if (bj(rb, sb)) {
        if (bj(rc, sc)) {
          if (bj(rd, sd)) printf("0\n");
        }
      }
    }
  }
}