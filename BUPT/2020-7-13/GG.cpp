#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3;
int next1[maxn];
int s[maxn];
int t[maxn];
int len1, len2;
void getnext() {
  next1[0] = -1;
  int t1 = 0, t2 = -1;
  while (t1 < len2) {
    if (t2 == -1 || t[t1] <= t[t2])
      next1[++t1] = ++t2;
    else
      t2 = next1[t2];
  }
}
int ans = 0;  //有多少个
void kmp() {
  int t1 = 0, t2 = 0;
  while (t1 < len1) {
    if (t2 == -1 || s[t1] >= t[t2])
      t1++, t2++;
    else
      t2 = next1[t2];
    if (t2 == len2) t2 = next1[t2], ans++;
  }
}
int main() {
  scanf("%d%d", &len1, &len2);
  for (int i = 0; i < len1; i++) {
    scanf("%d", s + i);
  }
  for (int i = 0; i < len2; i++) {
    scanf("%d", t + i);
  }
  getnext();
  kmp();
  printf("%d\n", ans);
}