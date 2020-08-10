#include <bits/stdc++.h>
using namespace std;
int H1, M1, S1;
int H2, M2, S2;
bool Judge() {
  if (H1 > H2) return 1;
  else if (H1 < H2) return 0;
  else {
    if (M1 > M2) return 1;
    else if (M1 < M2) return 0;
    else {
      if (S1 > S2) return 1;
      else return 0;
    }
  }
}
int main() {
  scanf ("%d:%d:%d", &H1, &M1, &S1);
  scanf ("%d:%d:%d", &H2, &M2, &S2);
  if (Judge()) {
    swap(H1, H2);
    swap(M1, M2);
    swap(S1, S2);
  }
  printf ("%d\n", (H2 - H1) * 3600 + (M2 - M1) * 60 + (S2 - S1));
}