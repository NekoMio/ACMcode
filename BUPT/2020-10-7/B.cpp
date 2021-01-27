#include <bits/stdc++.h>
using namespace std;
int Num[12][30], C[14][30], t;
char tmp[10];
__int128 DP[30][11][605];
__int128 DP2[30][605];
__int128 c(int n, int m) {
  __int128 ans = 1;
  for (int i = m + 1; i <= n; i++) {
    ans = ans * i / (i - m);
  }
  return ans;
}
__int128 gcd(__int128 a, __int128 b) {
  if (b == 0) return a;
  return gcd(b, a % b); 
}
int st[100], top;
void print(__int128 a) {
  if (a == 0) printf ("0");
  top = 0;
  while (a != 0) {
    st[++top] = a % 10;
    a /= 10;
  }
  for (int i = top; i >= 1; i--) printf("%d", st[i]);
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    memset(DP, 0, sizeof(DP));
    memset(DP2, 0, sizeof (DP2));
    memset(Num, 0, sizeof (Num));
    memset(C, 0, sizeof(C));
    t = 0;
    int n, m;
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf ("%s", tmp);
      Num[tmp[0] - '0' + 1][tmp[1] - 'A']++;
      Num[11][tmp[1] - 'A']++;
    }
    for (int i = 1; i <= m; i++) {
      scanf ("%s", tmp);
      if (tmp[0] != '?') {
        C[tmp[0] - '0' + 1][tmp[1] - 'A']++;
        C[12][tmp[1] - 'A']++;
      } else if (tmp[1] != '?') {
        C[11][tmp[1] - 'A']++;
        C[12][tmp[1] - 'A']++;
      } else {
        t++;
      }
    }
    for (int i = 0; i <= 25; i++) {
      DP[i][0][0] = 1;
      for (int j = 1; j <= 10; j++) {
        for (int l = 0; l <= C[12][i] + t; l++) {
          // DP[i][j][l] += DP[i][j - 1][l];
          for (int k = C[j][i]; k <= Num[j][i]; k++) {
            // if (k == 0) continue;
            DP[i][j][l + k] += DP[i][j - 1][l] * c(Num[j][i], k);
          }
        }
      }
    }
    for (int l = C[12][0]; l <= Num[11][0]; l++) {
      DP2[0][l] = DP[0][10][l];
    }
    for (int i = 1; i <= 25; i++) {
      // DP2[i][0] = 1;
      for (int l = 0; l <= m; l++) {
        // DP2[i][l] += DP2[i - 1][l];
        for (int k = C[12][i]; k <= Num[11][i]; k++) {
          // if (k == 0) continue;
          DP2[i][l + k] += DP2[i - 1][l] * DP[i][10][k];
        }
      }
    }
    __int128 a1 = DP2[25][m], a2 = c(n, m);
    if (a1 == 0) a2 = 1;
    else {
      __int128 gc = gcd(a1, a2);
      a1 /= gc, a2 /= gc;
    }
    print(a1);
    printf ("/");
    print(a2);
    printf("\n");
  }
}