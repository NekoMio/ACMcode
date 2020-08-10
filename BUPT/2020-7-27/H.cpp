#include <bits/stdc++.h>
using namespace std;
char s[104];
int F[105][10][1000];
int main() {
  scanf ("%s", s + 1);
  int n = strlen(s + 1);
  reverse(s + 1, s + n + 1);
  for (int i = 1; i <= n; i++) s[i] -= '0';
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = 0; k <= 9; k++) {
        for (int l = 0; l <= 901; l++) {
          F[i][j][l + j] += F[i - 1][k][l];
        }
      }
    }
  }
}