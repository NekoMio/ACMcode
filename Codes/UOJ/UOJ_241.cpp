#include <bits/stdc++.h>
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
const int B = 1, A = 0, C = 2;
const int MOD = 998244353;
long long f[2][3][3];
int main() {
  int n = read(), m = read();
  int now = 0;
  f[0][1] = m % MOD;
  for (int i = 2; i <= n; ++i) {
    now ^= 1;
    f[now][A][B] = (f[now ^ 1][B][A] + f[now ^ 1][C][A] + f[now ^ 1][B][C] +
                    f[now ^ 1][C][C]) %
                   MOD;
    f[now][B][A] = (f[now ^ 1][A][B] + f[now ^ 1][A][C] + f[now ^ 1][C][B] +
                    f[now ^ 1][C][C]) %
                   MOD;
    f[now][A][C] =
        (f[now ^ 1][B][A] * (m - 2) % MOD + f[now ^ 1][B][C] * (m - 3) % MOD +
         f[now ^ 1][C][A] * (m - 2) % MOD + f[now ^ 1][C][B] * (m - 2) % MOD +
         f[now ^ 1][C][C] * (m - 3) % MOD) %
        MOD;
    f[now][B][C] =
        (f[now ^ 1][A][A] * (m - 2) % MOD + f[now ^ 1][A][C] * (m - 3) % MOD +
         f[now ^ 1][C][A] * (m - 2) % MOD + f[now ^ 1][C][B] * (m - 2) % MOD +
         f[now ^ 1][C][C] * (m - 3) % MOD) %
        MOD;
    f[now][C][A] =
        (f[now ^ 1][A][B] * (m - 2) % MOD + f[now ^ 1][A][C] * (m - 2) % MOD +
         f[now ^ 1][B][C] * (m - 2) % MOD + f[now ^ 1][C][B] * (m - 3) % MOD +
         f[now ^ 1][C][C] * (m - 3) % MOD) %
        MOD;
    f[now][C][B] =
        (f[now ^ 1][B][A] * (m - 2) % MOD + f[now ^ 1][B][C] * (m - 2) % MOD +
         f[now ^ 1][A][C] * (m - 2) % MOD + f[now ^ 1][C][A] * (m - 3) % MOD +
         f[now ^ 1][C][C] * (m - 3) % MOD) %
        MOD;
    f[now][C][C] = (f[now ^ 1][A][B] * (m - 3) % MOD * (m - 2) % MOD +
                    f[now ^ 1][B][A] * (m - 3) % MOD * (m - 2) % MOD +
                    f[now ^ 1][A][C] * (m - 4) % MOD * (m - 2) % MOD +
                    f[now ^ 1][B][C] * (m - 4) % MOD * (m - 2) % MOD +
                    f[now ^ 1][C][C] * (m - 4) % MOD * (m - 3) % MOD +
                    f[now ^ 1][C][B] * (m - 4) % MOD * (m - 2) % MOD +
                    f[now ^ 1][C][A] * (m - 4) % MOD * (m - 2) % MOD) %
                   MOD;
  }
  printf("%d\n", f[now][0]);
}
