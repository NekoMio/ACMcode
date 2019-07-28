#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
long long Ans[100];
int cnt;
int main() {
  long long l, r, k;
  scanf ("%lld%lld%lld", &l, &r, &k);
  long long tmp = 1;
  while (1) {
    if (tmp >= l && tmp <= r) Ans[++cnt] = tmp;
    if (1.0 * tmp * k > r) break;
    tmp = tmp * k;
  }
  if (cnt == 0) printf ("-1\n");
  for (int i = 1; i <= cnt; ++i) 
    printf ("%lld ", Ans[i]);
  // while (1);
}