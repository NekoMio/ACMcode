#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e6 + 5;
long long nxt[MAXN], pre[MAXN], extend[MAXN];
char w[MAXN], t[MAXN];
void KMP(char *s, int n) {
  for (int i = 2, k; i <= n; i++) {
    k = nxt[i - 1];
    while (k && s[i] != s[k + 1]) k = nxt[k];
    if (s[i] == s[k + 1]) nxt[i] = k + 1;
    else nxt[i] = 0;
  }
}
void Get_Extend(char *s, int n) {
  pre[1] = n;
  pre[2] = 1;
  while (s[pre[2]] == s[pre[2] + 1] && pre[2] + 1 <= n) pre[2]++;
  pre[2]--;
  int P_pos = 2;
  for (int i = 3; i <= n; i++) {
    if (pre[i - P_pos + 1] + i < pre[P_pos] + P_pos) pre[i] = pre[i - P_pos + 1];
    else {
      pre[i] = pre[P_pos] + P_pos - i;
      if (pre[i] < 0) pre[i] = 0;
      while (s[pre[i] + 1] == s[pre[i] + i] && i + pre[i] <= n) pre[i]++;
      P_pos = i;
    }
  }
}
void Match(char *s, char *t) {
  int m = strlen(s + 1), n = strlen(t);
  Get_Extend(t, n);
  extend[1] = 1;
  while (s[extend[1]] == t[extend[1]] && extend[1] <= n) extend[1]++;
  extend[1]--;
  int P_pos = 1;
  for (int i = 2; i <= m; i++) {
    if (pre[i - P_pos + 1] + i < extend[P_pos] + P_pos) extend[i] = pre[i - P_pos + 1];
    else {
      extend[i] = P_pos + extend[P_pos] - i;
      if (extend[i] < 0) extend[i] = 0;
      while (t[extend[i] + 1] == s[i + extend[i]] && i + extend[i] <= m && extend[i] <= n) extend[i]++;
      P_pos = i;
    }
  }
}
int main() {
  int T;
  scanf("%d ", &T);
  while (T--) {
    memset (pre, 0, sizeof (pre));
    scanf ("%s", w + 1);
    int n = strlen(w + 1);
    // KMP(w, n);
    Get_Extend(w, n);
    long long ans = 0;
    for (int i = 2; i <= n; i++) {
      ans += ((pre[i] + i - 1 == n) ? pre[i] : pre[i] + 1);
    }
    printf ("%lld\n", ans);
  }
}
