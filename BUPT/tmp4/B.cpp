#include <bits/stdc++.h>
using namespace std;
int T = 10000000;
int Get_Next(int &lastHash) {
  lastHash = (1ll * lastHash * 31 + 'a') % 1000000007;
  lastHash = 1ll * lastHash * 7 % 1000000007;
  int H = lastHash / T;
  int ans = T - (lastHash % T);
  lastHash = (H + 1) * T;
  return ans;
}
int main() {
  int lastHash;
  scanf ("%d", &lastHash);
  // int dug = lastHash, t;
  printf ("a %d\n", Get_Next(lastHash));
  // printf ("%d %lld\n", lastHash, H(dug, s, t));
  // dug = lastHash;
  printf ("a %d\n", Get_Next(lastHash));
  // printf ("%d %lld\n", lastHash, H(dug, s, t));
}