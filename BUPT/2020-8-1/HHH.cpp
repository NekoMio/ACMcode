#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
  long long N, K, sum = 0, nxt;
  cin >> N >> K;
  int t = 0;
  for (int k = 2; k <= min(N, K); k++) {
    sum = sum + (N / k) + ((N - 1) / k) + 1;
  }
  (sum += N) %= MOD;
  if (K > N) (sum += K - N) %= MOD;;
  cout << sum;
}