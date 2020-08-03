#include <bits/stdc++.h>
using namespace std;
char s[304 * 300];
int Map[305][305];
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, S, t = 0;
    scanf ("%d%d", &n, &S);
    scanf ("%s", s);
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        Map[i][j] = Map[j][i] = (s[t++] - '0');
      }
    }
    
  }
}