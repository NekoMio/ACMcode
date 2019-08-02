#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
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
const int MAXN = 1e5 + 5;
int A[MAXN], B[MAXN];
long long pow_mod(long long a, int b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % MOD;
    b >>= 1;
    a = a * a % MOD;
  }
  return ans;
}
map<int, int> mp;
void Divide(int x) {
  int t = 2;
  while (x != 1) {
    if (t * t > x) return mp[x]++, void();
    while (x % t == 0) x /= t, mp[t]++;
    t++;
  }
  return void();
}
int Calc(int a, long long X) {
  int t = 2, num = 0;
  while (a != 1) {
    if (t * t > a) {
      X = (X * pow_mod(mp[a] + 1, MOD - 2) % MOD) * mp[a] % MOD;
      break;
    }
    while (a % t == 0) {
      a /= t;
      num++;
    }
    if (num) X = (X * pow_mod(mp[t] + 1, MOD - 2) % MOD) * (mp[t] - num + 1) % MOD;
    t++;
    num = 0;
  }
  return X;
}
int main() {
  int n = read();
  for (int i = 1; i <= n; i++) {
    A[i] = read();
    Divide(A[i]);
  }
  long long X = 1, Ans = 0;
  for (auto x : mp)
    X = X * (x.second + 1) % MOD;
  for (int i = 1; i <= n; i++) {
    Ans = (Ans + Calc(A[i], X)) % MOD;
  }
  printf ("%lld\n", Ans);
}