#include <bits/stdc++.h>
using namespace std;
char s[100];
map<string, int> mp;
long long Ans = 0;
int CalcT(int l, int r) {
  static string c;
  c.resize(r - l + 1);
  for (int i = l; i <= r; i++) c[i - 1] = s[i];
  return mp[c];
}
int CalcN(int l, int r) {
  bool flag = 0;
  int x = 0;
  for (int i = l; i <= r; i++) {
    if (s[i] == '[') flag = 1;
    else {
      if (s[i] == ']') break;
      if (flag)
        x = x * 10 + s[i] - '0';
    }
  }
  if (x == 0) return 1;
  return x;
}
int main() {
  int T, cnt = 0;
  mp["char"] = 1;
  mp["int"] = 4;
  mp["long long"] = 8;
  mp["__int128"] = 16;
  mp["float"] = 4;
  mp["double"] = 8;
  mp["long double"] = 16;
  mp["bool"] = 1;
  scanf ("%d", &T);
  while (T--) {
    cnt++;
    int n;
    scanf ("%d", &n);
    Ans = 0;
    getchar();
    for (int i = 1; i <= n; i++) {
      gets(s + 1);
      int len = strlen(s + 1), v = 0;
      for (int j = len; j >= 1; j--) {
        if (s[j] == ' ') {
          v = j;
          break;
        }
      }
      Ans += CalcT(1, v - 1) * CalcN(v + 1, len - 1);
    }
    printf ("Case #%d: %lld\n", cnt, Ans / 1024 + ((Ans % 1024) != 0));
  }
  // while (1);
}