#include <cstdio>

int a, b, c, d, e, f, g;
int i, m, n;
__int128 x[30][30] = {0}, h;
// unsigned long long w[30][30]={0};
int z[30] = {0};

void sr(__int128 &j) {
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

int main() {
  for (i = 1; i <= 26; i++) {
    x[26][i] = 1;
    // w[26][i]=i;
  }
  for (i = 1; i <= 25; i++) {
    x[25][i] = i + 1;
    // w[25][i]=w[25][i-1]+i+1;
  }
  for (i = 24; i >= 1; i--) {
    for (m = 1; m <= i; m++) {
      x[i][m] = x[i + 1][m + 1] + x[i + 1][m] * m;
      // w[i][m]=w[i][m-1]+x[i][m];
    }
  }
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%d", &b);
    sr(h);
    h--;
    z[1] = 1;
    d = 1;
    for (i = 2; i <= b; i++) {
      z[i] = 1;
      for (m = 1; m <= d; m++) {
        if (h >= x[26 - b + i][d]) {
          h -= x[26 - b + i][d];
          z[i] = m + 1;
        }
      }
      if (z[i] == d + 1) d++;
      // printf("%llu %llu %llu %llu %llu\n",i,z[i],d,c,x[26-b+i][d]);
    }
    printf("Case #%d: ", n);
    for (i = 1; i <= b; i++) {
      printf("%c", z[i] + 'A' - 1);
    }
    printf("\n");
  }
}