#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 300000 + 5;
char s[MAXN];
struct PAM {
  int len[MAXN << 1], fail[MAXN << 1], size[MAXN], tr[MAXN << 1][26];
  int cnt, now;
  PAM() {
    cnt = 1;
    fail[0] = fail[1] = 1;
    len[1] = -1;
  }
  int extend(int c, int pos) {
    int p = now;
    while (s[pos - len[p] - 1] != s[pos]) p = fail[p];
    if (!tr[p][c]) {
      int np = ++cnt, q = fail[p];
      len[np] = len[p] + 2;
      while (s[pos - len[p] - 1] != s[pos]) q = fail[q];
      fail[np] = tr[q][c];
      tr[p][c] = np;
    }
    now = tr[p][c];
		size[now]++;
    return pos - len[now];
  }
}pam;
int main() {
  scanf ("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; i++)
    pam.extend(s[i], i);
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    pam.size[pam.fail[i]] += pam.size[i];
    ans = max(ans, 1ll * pam.size[i] * pam.len[i]);
  }
  printf ("%lld\n", ans);
  while (1);
}