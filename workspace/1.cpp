#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, p, q, m;
unsigned int SA, SB, SC;
unsigned int rng61() {
  SA ^= SA << 16;
  SA ^= SA >> 5;
  SA ^= SA << 1;
  unsigned int t = SA; SA = SB;
  SB = SC;
  SC ^= t ^ SA;
  return SC;
}
const int MAXN = 5e6 + 5;
unsigned int a[MAXN], Max[MAXN];
int main() {
  int T, cnt = 0;;
  scanf ("%d", &T);
  while (T--) {
    cnt++;
    int top = 0;
    long long ans = 0;
    scanf ("%d%d%d%d%u%u%u", &n, &p, &q, &m, &SA, &SB, &SC);
    for (int i = 1; i <= n; i++) {
      if (rng61() % (p + q) < p) {
        a[++top] = rng61() % m + 1;
        Max[top] = max(Max[top - 1], a[top]);
      } else {
        if (top) top--;
      }
      ans = ans ^ (1ll * i * Max[top]);
    }
    printf ("Case #%d: %lld\n", cnt, ans);
  }
  // while (1);
}