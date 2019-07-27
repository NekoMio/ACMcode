#include <cstdio>
using namespace std;
const int MAXN = 600005;
bool isnprime[MAXN];
int prime[MAXN], cnt;
void Get_Prime(int n) {
  isnprime[1] = 1;
  for (int i = 1; i <= n; i++) {
    if (!isnprime[i])
      prime[++cnt] = i;
    for (int j = 1; j <= cnt; j++) {
      if (i % prime[j] == 0) break;
      isnprime[i * prime[j]] = 1;
    }
  }
}
int main() {
  Get_Prime(10000);
  for (int i = 1; i <= 100; ++i) {
    printf ("%d\n", prime[i]);
  }
}