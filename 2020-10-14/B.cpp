#include <bits/stdc++.h>
using namespace std;
map<string, int> mp;
char s1[100], s2[100];
int main() {
  int T;
  scanf("%d", &T);
  mp["Beijing"] = 8;
  mp["Washington"] = -5;
  mp["London"] = 0;
  mp["Moscow"] = 3;
  int cnt = 0;
  while (T--) {
    int a, b;
    cnt++;
    char c[10];
    scanf ("%d:%d%s", &a, &b, c);
    if (a == 12) a = 0;
    if (c[0] == 'P') a += 12;
    scanf ("%s%s", s1, s2);
    a += mp[s2] - mp[s1];
    int t = 0, p = 0;
    if (a >= 24) a -= 24, t = 1;
    if (a >= 12) a -= 12, p = 1;
    if (a < 0) {
      a += 24;
      if (a >= 12) a -= 12, p = 1;
      if (a == 0) a = 12;
      printf ("Case %d: %s %d:%02d %s\n", cnt, "Yesterday", a, b, p ? "PM": "AM");
    } else {
      if (a == 0) a = 12;
      printf ("Case %d: %s %d:%02d %s\n", cnt, t ? "Tomorrow": "Today", a, b, p ? "PM": "AM");
    }
  }
}