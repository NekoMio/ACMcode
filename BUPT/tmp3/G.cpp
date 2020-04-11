#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
char s[MAXN];
int L[30], R[30];
int Sum[MAXN][26];
int k, n;
unsigned Hash_A[MAXN], Hash_B[MAXN];
unsigned bin_A[MAXN], bin_B[MAXN];
const unsigned base_A = 131, base_B = 1313;
unsigned Get_Hash(int l, int r, unsigned *Hash, unsigned *bin) {
  if (l > 0) return Hash[r] - Hash[l - 1] * bin[r - l + 1];
  return Hash[r];
}
bool Judge(int x) {
  for (int i = 0; i < 26; i++) {
    if (Sum[x + k - 1][i] - Sum[x - 1][i] < L[i] || Sum[x + k - 1][i] - Sum[x - 1][i] > R[i])
      return 0;
  }
  return 1;
}
bool Cmp(int a, int b) {
  if (a == -1) return 1;
  if (s[a] != s[b]) return s[a] > s[b];
  int l = 1, r = k;
  int mid, ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (Get_Hash(a, a + mid - 1, Hash_A, bin_A) == Get_Hash(b, b + mid - 1, Hash_A, bin_A) && \
        Get_Hash(a, a + mid - 1, Hash_B, bin_B) == Get_Hash(b, b + mid - 1, Hash_B, bin_B)) ans = mid, l = mid + 1;
    else r = mid - 1;
  }
  return s[a + ans] > s[b + ans];
}
int main() {
  bin_A[0] = 1, bin_B[0] = 1;
  for (int i = 1; i <= MAXN - 1; i++) {
    bin_A[i] = bin_A[i - 1] * base_A;
    bin_B[i] = bin_B[i - 1] * base_B;
  }
  while (scanf ("%s", s + 1) != EOF) {
    scanf ("%d", &k);
    n = strlen(s + 1);
    for (int i = 0; i < 26; i++) scanf ("%d%d", L + i, R + i), Sum[0][i] = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < 26; j++) {
        Sum[i][j] = Sum[i - 1][j] + ((s[i] - 'a') == j);
      }
    }
    for (int i = 1; i <= n; i++) {
      Hash_A[i] = Hash_A[i - 1] * base_A + s[i];
      Hash_B[i] = Hash_B[i - 1] * base_B + s[i];
    }
    int ans = -1;
    for (int i = 1; i + k - 1 <= n; i++) {
      if (Judge(i)) {
        if (Cmp(ans, i)) ans = i;
      }
    }
    if (ans == -1) printf ("-1\n");
    else {
      for (int i = ans; i <= ans + k - 1; i++) printf ("%c", s[i]);
      printf ("\n");
    }
  }
}