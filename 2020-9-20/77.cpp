#include <bits/stdc++.h>
using namespace std;
char s[100005];
int Num[300];
int main() {
  int T, cnt = 0;
  scanf ("%d", &T);
  while (T--) {
    cnt++;
    scanf ("%s", s);
    memset(Num, 0, sizeof(Num));
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
      Num[s[i]]++;
    }
    int Max= 0 ;
    for (int i = 'a'; i <= 'z'; i++) {
      Max = max(Max, Num[i]);
    }
    printf ("Case #%d: %d\n", cnt, Max);
  }
}