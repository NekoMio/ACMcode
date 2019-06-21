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
int pr[10] = {0, 2, 3, 5, 7, 11, 13, 17, 19};
int Judge(int x) {
  for (int i = 1; i <= 8; ++i) {
    int t = 0;
    while (x % pr[i] == 0) {
      x /= pr[i];
      t++;
    }
    if (t > 1) return -1;
  }
  if (x != 1) return x;
  return 0;
}
int Divide(int x) {
  int ans = 0;
  for (int i = 1; i <= 8; ++i) {
    if (x % pr[i] == 0) {
      ans = ans | (1 << (i - 1));
    }
  }
  return ans;
}
bool flag[505];
const int MOD = 998244353;
vector<int> vc[505], num;
int f[2][505][257], N = 255;
int main() {
  int n = read(), K = read();
  for (int i = 2; i <= n; ++i) {
    int x = Judge(i);
    if (x != -1 && x != 0) {
      flag[i] = 1;
      vc[x].push_back(Divide(i / x));
    } else if (x == 0) {
      num.push_back(Divide(i));
    }
  }
  int now = 0;
  f[now][0][0] = 1;
  for (int i = 0; i < num.size(); ++i) {
    now ^= 1;
    memset (f[now], 0, sizeof (f[now]));
    for (int k = 0; k <= N; ++k) {
      for (int j = 0; j <= K; ++j) if (f[now ^ 1][j][k]) {
		if ((num[i] & k) == 0) f[now][j + 1][k | num[i]] = (f[now][j + 1][k | num[i]] + f[now ^ 1][j][k]) % MOD;
        f[now][j][k] = (f[now][j][k] + f[now ^ 1][j][k]) % MOD;
      }
    }
  }
  for (int i = 1; i <= n; ++i) if (vc[i].size()) {
    now ^= 1;
    memset (f[now], 0, sizeof (f[now]));
    for (int k = 0; k <= N; ++k) {
      for (int j = 0; j <= K; ++j) if (f[now ^ 1][j][k]) {
        f[now][j][k] = (f[now][j][k] + f[now ^ 1][j][k]) % MOD;
      }
    }
	for (int s = 0; s < vc[i].size(); ++s) {
      for (int k = 0; k <= N; ++k) {
        for (int j = 0; j <= K; ++j) if (f[now ^ 1][j][k]) {
          if ((vc[i][s] & k) == 0) f[now][j + 1][k | vc[i][s]] = (f[now][j + 1][k | vc[i][s]] + f[now ^ 1][j][k]) % MOD;
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= K; ++i) {
    for (int k = 0; k <= N; ++k) {
      ans = (ans + f[now][i][k]) % MOD;
    }
  }
  printf ("%d\n", ans);
}
