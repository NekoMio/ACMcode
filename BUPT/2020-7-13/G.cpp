#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3;
int next1[maxn];
int s[maxn];
int t[maxn];
int len1, len2;

int main() {
  scanf("%d%d", &len1, &len2);
  for (int i = 0; i < len1; i++) {
    scanf("%d", s + i);
  }
  for (int i = 0; i < len2; i++) {
    scanf("%d", t + i);
  }
  printf("%d\n", ans);
}