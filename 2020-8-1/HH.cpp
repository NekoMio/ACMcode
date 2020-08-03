#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
  long long n, k, nxt, sum = 0;
  cin >> n >> k;
  long long t = min(n, k);
  for (long long i = 2; i <= t; i = nxt + 1) {
    nxt = n / (n / i);
    if (nxt > t) nxt = t;
    (sum += ((n / i) % MOD) % MOD * ((nxt - i + 1) % MOD) % MOD) %= MOD;
  }
  long long N = n - 1;
  t = min(N, k);
  for (long long i = 2; i <= t; i = nxt + 1) {
    nxt = N / (N / i);
    if (nxt > t) nxt = t;
    (sum += ((N / i + 1) % MOD) % MOD * ((nxt - i + 1) % MOD) % MOD) %= MOD;
  }
  (sum += n) %= MOD;
  if (k > n) (sum += k - n) %= MOD;;
  cout << (sum + 1) % MOD;
}