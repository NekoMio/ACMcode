#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5, MAXM = 1e6 + 5;
char c[MAXN], s[MAXM];
unsigned Hash[MAXM], H, base = 13, h[MAXM];
unsigned Get_Hash(int l, int r) {
  return Hash[r] - Hash[l - 1] * h[r - l + 1];
}
int main() {
  int n;
  scanf ("%d", &n);
  h[0] = 1;
  for (int i = 1; i <= 1e6; i++) h[i] = h[i - 1] * base;
  scanf ("%s", s + 1);
  int S = strlen(s + 1);
  for (int i = 1; i <= S; i++) Hash[i] = Hash[i - 1] * base + s[i];
  for (int i = 2; i <= n; i++) {
    scanf ("%s", c + 1);
    int len = strlen(c + 1);
    int L = 0;
    H = 0;
    for (int j = 1; j <= len && j <= S; j++) {
      H = H * base + c[j];
      if (H == Get_Hash(S - j + 1, S))
        L = j;
    }
    for (int j = L + 1; j <= len; j++) {
      S++;
      s[S] = c[j];
      Hash[S] = Hash[S - 1] * base + s[S];
    }
  }
  for (int i = 1; i <= S; i++)
    printf ("%c", s[i]);
  // while (1);
}