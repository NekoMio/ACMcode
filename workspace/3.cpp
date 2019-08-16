#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
char s[15];
bool flag[15];
int ans;
int pre(int x) {
  for (int i = x - 1; i >= 1; i--) {
    if (!flag[i]) return i;
  }
  return 0;
}
int nxt(int x) {
  for (int i = x + 1; i <= 9; i++) {
    if (!flag[i]) return i;
  }
  return 0;
}
void DFS(int dep, int num) {
  if ((9 - dep + 1) / 3 + num <= ans) return;
  if (dep == 10) {
    ans = max(ans, num);
    return;
  }
  for (int i = 2; i <= 8; i++) {
    int p = pre(i), n = nxt(i);
    if (p && n) {
      if (!flag[i] && !flag[p] && !flag[n]) {
        if (s[i] == s[p] && s[i] == s[n]) {
          flag[i] = flag[p] = flag[n] = 1;
          DFS(dep + 3, num + 1);
          flag[i] = flag[p] = flag[n] = 0;
        }
      }
    }
  }
  for (int i = 1; i <= 9; i++) {
    if (!flag[i]) {
      flag[i] = 1;
      DFS(dep + 1, num);
      flag[i] = 0;
    }
  }
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    scanf ("%s", s + 1);
    ans = 0;
    memset (flag, 0, sizeof (flag));
    DFS(1, 0);
    cout << ans << endl;
  }
}