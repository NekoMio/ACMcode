#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long pow(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a;
    b >>= 1;
    a = a * a;
  }
  return ans;
}
int main() {
  for (int i = 1; i <= 10; i++) {
    for (int j = 1; j <= 10; j++) {
      for (int a = 1; a <= 10; a++) {
        for (int b = 1; b <= 10; b++) {
          printf ("%d %d %d %d: %lld\n", i, j, a, b, __gcd(pow(i, a), pow(j, b)));
        }
      }
    }
  }
}