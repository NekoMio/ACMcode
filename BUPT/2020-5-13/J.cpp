#include <bits/stdc++.h>
using namespace std;
char s[100005], t[105];
int POS[26][100005];
int main() {
  scanf ("%s", s + 1);
  scanf ("%s", t + 1);
  int lens = strlen(s + 1), lent = strlen(t + 1);
  for (int i = 1; i <= lens; i++) POS[s[i] - 'a'][++POS[s[i] - 'a'][0]] = i;
  for (int i = 0; i < 26; i++) POS[i][++POS[i][0]] = lens + 1;
  int ret = 0;
  long long ans = 0;
  while (ret <= lens) {
    int pos = ret + 1;
    while (pos <= lens) {
      if (s[pos] == t[1])
        break;
      pos++;
    }
    if (pos > lens) break;
    int tmp = pos, j = 2;
    while (tmp <= lens) {
      if (j == lent + 1) break;
      tmp = *upper_bound(POS[t[j] - 'a'] + 1, POS[t[j] - 'a'] + POS[t[j] - 'a'][0], tmp);
      if (tmp != lens + 1) j++;
    }
    if (j <= lent) break;
    ans = ans + 1ll * (pos - ret) * (lens + 1 - tmp);
    ret = pos;
  }
  printf ("%lld\n", ans);
}