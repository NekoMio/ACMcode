#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

struct xl {
  int p, q;
};

int a, b, c, d, e, f, g, i, m, n, h1, h2, h3, h4, h5, h6, r1, r2, r3, r4, r5;
int xa[300000] = {0}, xb[300000] = {0}, xc[300000] = {0};
xl wa[300000], wb[300000], wc[300000], wd[300000], we[300000];
int y = -3000000;

inline bool sx(xl j, xl k) { return j.p < k.p; }

inline bool sx1(xl j, xl k) { return j.p > k.p; }

inline void Get(int &j) {
  j = 0;
  char ch;
  do {
    ch = getchar();
  } while (ch < '0' || ch > '9');
  do {
    j = j * 10 + ch - '0';
    ch = getchar();
  } while (ch >= '0' && ch <= '9');
}

inline void Put(int j) {
  if (j >= 10) Put(j / 10);
  putchar(j % 10 + '0');
}

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  Get(a);  //
  for (n = 1; n <= a; n++) {
    Get(b);  //
    h1 = 0;
    h2 = 0;
    h3 = 0;
    h4 = 0;
    h5 = 0;
    for (i = 1; i <= b; i++) {
      Get(xa[i]);  //
      Get(xb[i]);  //
      xc[i] = 0;
      wa[i].p = xa[i];
      wa[i].q = i;
      wb[i].p = xa[i] + xb[i];
      wb[i].q = i;
    }
    h1 = h2 = b;
    make_heap(wa + 1, wa + h1 + 1, sx);
    make_heap(wb + 1, wb + h2 + 1, sx);

    h6 = wa[1].p;
    r1 = wa[1].q;
    xc[r1]++;
    pop_heap(wa + 1, wa + h1 + 1, sx);
    h1--;
    wc[h3 + 1].p = xb[r1];
    wc[h3 + 1].q = r1;
    push_heap(wc + 1, wc + h3 + 2, sx);
    h3++;
    wd[h4 + 1].p = xa[r1];
    wd[h4 + 1].q = r1;
    push_heap(wd + 1, wd + h4 + 2, sx1);
    h4++;

    Put(h6);
    r4 = y;
    for (i = 2; i <= 2 * b; i++) {
      // printf("\n%d %d\n",i,r4);
      if (r4 > y)
        h6 += r4, r4 = y;
      else {
        while ((h1 > 0) && (xc[wa[1].q] >= 1)) {
          pop_heap(wa + 1, wa + h1 + 1, sx);
          h1--;
        }
        while ((h2 > 0) && (xc[wb[1].q] >= 1)) {
          pop_heap(wb + 1, wb + h2 + 1, sx);
          h2--;
        }
        while ((h3 > 0) && (xc[wc[1].q] != 1)) {
          pop_heap(wc + 1, wc + h3 + 1, sx);
          h3--;
        }
        while ((h4 > 0) && (xc[wd[1].q] != 1)) {
          pop_heap(wd + 1, wd + h4 + 1, sx1);
          h4--;
        }
        while ((h5 > 0) && (xc[we[1].q] != 2)) {
          pop_heap(we + 1, we + h5 + 1, sx1);
          h5--;
        }
        if (h1 > 0)
          r1 = wa[1].p;
        else
          r1 = y;
        if (h3 > 0)
          r3 = wc[1].p;
        else
          r3 = y;
        // printf("%d %d\n",wc[1].p,wc[2].p);
        r2 = y;
        if (h2 > 0) {
          if (h4 > 0) r2 = wb[1].p - wd[1].p, r5 = 1;
          if ((h5 > 0) && (r2 <= wb[1].p - we[1].p))
            r2 = wb[1].p - we[1].p, r5 = 2;
        }
        // printf("%d %d %d %d  %d %d %d %d %d\n",r1,r2,r3,r5,h1,h2,h3,h4,h5);
        if ((r1 >= r2) && (r1 >= r3)) {
          h6 += wa[1].p;
          r1 = wa[1].q;
          xc[r1]++;
          pop_heap(wa + 1, wa + h1 + 1, sx);
          h1--;
          wc[h3 + 1].p = xb[r1];
          wc[h3 + 1].q = r1;
          push_heap(wc + 1, wc + h3 + 2, sx);
          h3++;
          wd[h4 + 1].p = xa[r1];
          wd[h4 + 1].q = r1;
          push_heap(wd + 1, wd + h4 + 2, sx1);
          h4++;

        } else {
          if (r2 >= r3) {
            h6 += r2;
            r1 = wb[1].q;
            xc[r1] = 2;
            pop_heap(wb + 1, wb + h2 + 1, sx);
            h2--;
            if (r5 == 1)
              r4 = wd[1].p;
            else
              r4 = we[1].p;
            we[h5 + 1].p = xb[r1];
            we[h5 + 1].q = r1;
            push_heap(we + 1, we + h5 + 2, sx1);
            h5++;
          } else {
            h6 += wc[1].p;
            r1 = wc[1].q;
            xc[r1]++;
            pop_heap(wc + 1, wc + h3 + 1, sx);
            h3--;
            we[h5 + 1].p = xb[r1];
            we[h5 + 1].q = r1;
            push_heap(we + 1, we + h5 + 2, sx1);
            h5++;
          }
        }
      }
      // printf("%d\n",h6);
      putchar(' ');
      Put(h6);
    }
    putchar('\n');
  }
}