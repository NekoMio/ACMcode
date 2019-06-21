#include <algorithm>
#include <cstdio>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int MAXN = 1e6 + 5;
int a[MAXN], n;
int Num[32][2];
int Get_Max(int a, int b) {
  for (int i = 30; i >= 0; i--) {
    if ((a & (1 << i)) ^ (b & (1 << i))) return i;
  }
  return -1;
}
int Calc() {
  int ans = 0;
  for (int i = 0; i <= 30; ++i) {
    if (Num[i][1] && Num[i][0])
      return -1;
    else if (Num[i][1])
      ans |= (1 << i);
  }
  return ans;
}
int Init() {
  for (int i = 2; i <= n; ++i) {
    int M = Get_Max(a[i - 1], a[i]);
    if (M != -1) {
      if ((a[i - 1] & (1 << M)) ^ (a[i] & (1 << M))) {
        if ((a[i - 1] & (1 << M))) {
          Num[M][1]++;
        } else {
          Num[M][0]++;
        }
      }
    }
  }
  return Calc();
}
int main() {
  n = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  printf("%d\n", Init());
  int q = read();
  while (q--) {
    int p = read(), v = read();
    if (p != 1) {
      int M = Get_Max(a[p - 1], a[p]);
      if (M != -1) {
        if ((a[p - 1] & (1 << M)) ^ (a[p] & (1 << M))) {
          if ((a[p - 1] & (1 << M))) {
            Num[M][1]--;
          } else {
            Num[M][0]--;
          }
        }
      }
      M = Get_Max(a[p - 1], v);
      if (M != -1) {
        if ((a[p - 1] & (1 << M)) ^ (v & (1 << M))) {
          if ((a[p - 1] & (1 << M))) {
            Num[M][1]++;
          } else {
            Num[M][0]++;
          }
        }
      }
    }
    if (p != n) {
      int M = Get_Max(a[p], a[p + 1]);
      if (M != -1) {
        if ((a[p] & (1 << M)) ^ (a[p + 1] & (1 << M))) {
          if ((a[p] & (1 << M))) {
            Num[M][1]--;
          } else {
            Num[M][0]--;
          }
        }
      }
      M = Get_Max(a[p + 1], v);
      if (M != -1) {
        if ((v & (1 << M)) ^ (a[p + 1] & (1 << M))) {
          if ((v & (1 << M))) {
            Num[M][1]++;
          } else {
            Num[M][0]++;
          }
        }
      }
    }
    a[p] = v;
    printf("%d\n", Calc());
  }
}
