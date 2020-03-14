#include <bits/stdc++.h>
using namespace std;
int INF = 0x3f3f3f3f;
int A[4], B[4];
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int a, b;
    scanf ("%d%d", &a, &b);
    for (int i = 1; i <= a; i++) scanf ("%d", &A[i]);
    for (int i = 1; i <= b; i++) scanf ("%d", &B[i]);
    int A1 = A[1] + 2, A2;
    int B1 = B[1] + 2, B2;
    if (a == 1) A2 = INF;
    else if (a == 2) A2 = A[2] + 1;
    else A2 = (A[2] + 1) * A[3];
    if (b == 1) B2 = INF;
    else if (b == 2) B2 = B[2] + 1;
    else B2 = (B[2] + 1) * B[3];
    if (min(A1, A2) == min(B1, B2)) {
      if (max(A1, A2) == max(B1, B2)) {
        printf ("0\n");
      } else {
        printf ("%d\n", max(A1, A2) < max(B1, B2) ? 1 : -1);
      }
    } else {
      printf ("%d\n", min(A1, A2) < min(B1, B2) ? 1 : -1);
    }
  }
}