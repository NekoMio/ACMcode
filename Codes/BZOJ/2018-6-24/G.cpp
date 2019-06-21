#include <bits/stdc++.h>
using namespace std;
char s[1000005];
int Sum[27];
int main() {
  scanf ("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; ++i)
    Sum[s[i] - 'a']++;
  int ans = 0x3f3f3f3f;
  for (int i = 0; i <= 25; ++i)
    ans = min(ans, Sum[i]);
  printf ("%d\n", ans);
}
