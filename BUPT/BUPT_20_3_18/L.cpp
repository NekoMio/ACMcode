#include <bits/stdc++.h>
using namespace std;
char s[200][200];
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int a, b, c;
    scanf ("%d%d%d", &a, &b, &c);
    for (int i = 1; i <= 2 * (b + c) + 1; i++) {
      for (int j = 1; j <= 2 * (b + a) + 1; j++) {
        s[i][j] = '.';
      }
    }
    // 2 * b + 2 - i
    for (int i = 1; i <= 2 * b; i += 2) {
      for (int j = 1; j <= 2 * a; j += 2) {
        s[i][j + 2 * b + 1 - i] = '+';
        s[i][j + 2 * b + 2 - i] = '-';
      }
      s[i][2 * a + 2 * b + 2 - i] = '+';
      for (int j = 1; j <= 2 * a; j += 2) {
        s[i + 1][j + 2 * b - i] = '/';
      }
      s[i + 1][2 * a + 2 * b - i + 1] = '/';
    }
    for (int i = 2 * b + 1; i <= 2 * (b + c) + 1; i += 2) {
      for (int j = 1; j <= 2 * a; j += 2) {
        s[i][j] = '+';
        s[i][j + 1] = '-';
      }
      s[i][2 * a + 1] = '+';
      for (int j = 1; j <= 2 * a; j += 2) {
        s[i + 1][j] = '|';
      }
      s[i + 1][2 * a + 1] = '|';
      // printf ("%d\n", i);
    }
    
    for (int i = 1; i <= 2 * b; i += 2) {
      for (int j = 1; j <= 2 * c; j += 2) {
        s[j + i][2 * (b + a) + 2 - i] = '|';
        s[j + i + 1][2 * (b + a) + 2 - i] = '+';
      }
      for (int j = 1; j <= 2 * c; j += 2) {
        s[j + i + 2][2 * (b + a) + 1 - i] = '/';
      }
    }
    for (int i = 1; i <= 2 * (b + c) + 1; i++) {
      for (int j = 1; j <= 2 * (b + a) + 1; j++) {
        printf ("%c", s[i][j]);
      }
      printf ("\n");
    }
  }
}