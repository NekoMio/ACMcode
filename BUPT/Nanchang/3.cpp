#include <cstdio>
struct xl  // 9,1,0,2
{
  int ha, hb, hc, hd;
  int hab, hbc, hcd;
  int habc, hbcd;
  int habcd;
};

int a, b, c, d, e, f, i, m, n;
int x[500000] = {0};
int xa[500000] = {0}, xb[500000] = {0}, xc[500000] = {0}, xd[500000] = {0};
// 8,1,0,2
xl w[5000000], g, h;
char z[500000];

void ma(int &j, int k) {
  if (j < k) j = k;
}

void qk(xl &j) {
  j.ha = j.hb = j.hc = j.hd = j.hab = j.hbc = j.hcd = -1;
  j.habc = j.hbcd = j.habcd = -1;
}

void cl(int &j, int k, int l) {
  if ((k > 0) && (l > 0)) ma(j, k + l);
}

void hb(xl &j, xl k, xl l, int p, int q, int r, int s, int t) {
  // printf("%d %d %d %d %d\n",r,s,t,p,q);
  if (k.ha > 0) ma(j.ha, k.ha + q - xa[t] + xa[s]);
  if (l.ha > 0) ma(j.ha, l.ha + p - xa[s] + xa[r - 1]);
  if (k.hb > 0) ma(j.hb, k.hb + q - xb[t] + xb[s]);
  if (l.hb > 0) ma(j.hb, l.hb + p - xa[s] + xa[r - 1]);
  if (k.hc > 0) ma(j.hc, k.hc + q - xc[t] + xc[s]);
  if (l.hc > 0) ma(j.hc, l.hc + p - xb[s] + xb[r - 1]);
  if (k.hd > 0) ma(j.hd, k.hd + q - xd[t] + xd[s]);
  if (l.hd > 0) ma(j.hd, l.hd + p - xc[s] + xc[r - 1]);
  if (k.hab > 0) ma(j.hab, k.hab + q - xb[t] + xb[s]);
  if (l.hab > 0) ma(j.hab, l.hab + p - xa[s] + xa[r - 1]);
  if (k.hbc > 0) ma(j.hbc, k.hbc + q - xc[t] + xc[s]);
  if (l.hbc > 0) ma(j.hbc, l.hbc + p - xa[s] + xa[r - 1]);
  if (k.hcd > 0) ma(j.hcd, k.hcd + q - xd[t] + xd[s]);
  if (l.hcd > 0) ma(j.hcd, l.hcd + p - xb[s] + xb[r - 1]);
  if (k.habc > 0) ma(j.habc, k.habc + q - xc[t] + xc[s]);
  if (l.habc > 0) ma(j.habc, l.habc + p - xa[s] + xa[r - 1]);
  if (k.hbcd > 0) ma(j.hbcd, k.hbcd + q - xd[t] + xd[s]);
  if (l.hbcd > 0) ma(j.hbcd, l.hbcd + p - xa[s] + xa[r - 1]);
  if (k.habcd > 0) ma(j.habcd, k.habcd + q - xd[t] + xd[s]);
  if (l.habcd > 0) ma(j.habcd, l.habcd + p - xa[s] + xa[r - 1]);
  cl(j.hab, k.ha, l.hb);
  cl(j.hbc, k.hb, l.hc);
  cl(j.hcd, k.hc, l.hd);
  cl(j.habc, k.hab, l.hc);
  cl(j.habc, k.ha, l.hbc);
  cl(j.hbcd, k.hbc, l.hd);
  cl(j.hbcd, k.hb, l.hcd);
  cl(j.habcd, k.ha, l.hbcd);
  cl(j.habcd, k.hab, l.hcd);
  cl(j.habcd, k.habc, l.hd);
}

void sc(int j, int k, int l) {
  int p = (k + l) / 2;
  qk(w[j]);
  if (k == l) {
    if (x[k] == 9) w[j].ha = 1;
    if (x[k] == 1) w[j].hb = 1;
    if (x[k] == 0) w[j].hc = 1;
    if (x[k] == 2) w[j].hd = 1;
  } else {
    sc(2 * j, k, p);
    sc(2 * j + 1, p + 1, l);
    hb(w[j], w[2 * j], w[2 * j + 1], p - k + 1, l - p, k, p, l);
  }
  /*printf("%d %d abcd%d\n",k,l,w[j].habcd);
  printf("abc%d bcd%d\n",w[j].habc,w[j].hbcd);
  printf("ab%d bc%d cd%d\n",w[j].hab,w[j].hbc,w[j].hcd);
  printf("a%d b%d c%d d%d\n",w[j].ha,w[j].hb,w[j].hc,w[j].hd);
  */
}

xl cz(int j, int k, int l) {
  // printf("%d %d %d %d\n",c,d,k,l);
  if ((c <= k) && (l <= d)) return w[j];
  int p = (k + l) / 2;
  xl r, s, t;
  if (d <= p) return cz(2 * j, k, p);
  if (p < c) return cz(2 * j + 1, p + 1, l);
  qk(r);
  s = cz(2 * j, k, p);
  t = cz(2 * j + 1, p + 1, l);
  if (k < c) k = c;
  if (d < l) l = d;
  hb(r, s, t, p - k + 1, l - p, k, p, l);
  /*
  printf("\n\n%d %d %d %d abcd%d\n",c,d,k,l,s.habcd);
  printf("abc%d bcd%d\n",s.habc,s.hbcd);
  printf("ab%d bc%d cd%d\n",s.hab,s.hbc,s.hcd);
  printf("a%d b%d c%d d%d\n",s.ha,s.hb,s.hc,s.hd);

  printf("\n%d %d %d %d abcd%d\n",c,d,k,l,t.habcd);
  printf("abc%d bcd%d\n",t.habc,t.hbcd);
  printf("ab%d bc%d cd%d\n",t.hab,t.hbc,t.hcd);
  printf("a%d b%d c%d d%d\n",t.ha,t.hb,t.hc,t.hd);

  printf("\n%d %d %d %d abcd%d\n",c,d,k,l,r.habcd);
  printf("abc%d bcd%d\n",r.habc,r.hbcd);
  printf("ab%d bc%d cd%d\n",r.hab,r.hbc,r.hcd);
  printf("a%d b%d c%d d%d\n",r.ha,r.hb,r.hc,r.hd);
  */
  return r;
}

int main() {
  // freopen("test.in","r",stdin);
  scanf("%d%d", &a, &b);
  scanf("%s", z);
  for (i = 1; i <= a; i++) {
    x[i] = z[i - 1] - '0';
    // printf("%d ",x[i]);
    xa[i] = xa[i - 1];
    xb[i] = xb[i - 1];
    xc[i] = xc[i - 1];
    xd[i] = xd[i - 1];
    if (x[i] == 8) xa[i]++;
    if (x[i] == 1) xb[i]++;
    if (x[i] == 0) xc[i]++;
    if (x[i] == 2) xd[i]++;
  }
  sc(1, 1, a);
  qk(h);
  for (i = 1; i <= b; i++) {
    scanf("%d%d", &c, &d);
    g = cz(1, 1, a);

    /*printf("%d abcd%d\n",i,g.habcd);
    printf("abc%d bcd%d\n",g.habc,g.hbcd);
    printf("ab%d bc%d cd%d\n",g.hab,g.hbc,g.hcd);
    printf("a%d b%d c%d d%d\n",g.ha,g.hb,g.hc,g.hd);*/
    if (g.habcd < 0)
      printf("%d\n", g.habcd);
    else
      printf("%d\n", d - c + 1 - g.habcd);
  }
}