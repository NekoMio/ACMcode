#include <bits/stdc++.h>
using namespace std;
template<typename _Tp>
_Tp read() {
  _Tp x = 0;
  int f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int tmp[50];
void print(__int128 x) {
  int T = 0;
  while (x) {
    tmp[++T] = x % 10;
    x /= 10;
  }
  for (int i = T; i >= 1; i--) printf("%d", tmp[i]);
  printf("\n");
}
__int128 S[1001], R[1001];
int main() {
  int T = read<int>();
  __int128 N;
  S[1] = 4, R[1] = 2;
  for (int i = 2; i <= 100; i++) {
    S[i] = 2 * S[i - 1] + 3 * R[i - 1];
    R[i] = S[i - 1] + 2 * R[i - 1];
  }
  while (T--) {
    N = read<__int128>();
    for (int i = 1; i <= 100; i++) {
      if (N <= S[i]) {
        print(S[i]);
        break;
      }
    }
  }
}