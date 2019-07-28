#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
long long Ans;
long long GCD(long long a, long long b) {
  if (b == 0) return a;
  Ans += a / b;
  return GCD(b, a % b);
}
int main() {
  long long a, b;
  scanf ("%lld%lld", &a, &b);
  if (a < b) swap(a, b);
  GCD(a, b);
  printf ("%lld\n", Ans);
  // while (1);
}