#include <bits/stdc++.h>
using namespace std;
int Num[100];
int Divide(int x) {
  int i = 2;
  int Sum = 0;
  while (i * i <= x) {
    while (x % i == 0) {
      Sum++;
      Num[Sum] = i;
      x /= i;
    }
    i++;
  }
  if (x != 1) Sum++, Num[Sum] = x;
  return Sum;
}
int DFS(int pos, int val, int t, int x) {
  if (pos == t + 1) {
    return ((x / val) & 1) ? Divide(val) + 1 : 0;
  }
  int Ans = 0;
  for (int i = pos; i <= t; i++) {
    Ans ^= DFS(i + 1, val * Num[i], t + 1, x);
  }
  Ans ^= DFS(t + 1, val, t, x);
  return Ans;
}
int Calc(int x) {
  if (x == 1) return 0;
  int t = Divide(x);
  return DFS(1, 1, t, x);
}
int main() {
  int T;
  scanf ("%d", &T);
  while (T--) {
    int n, l;
    scanf ("%d", &n);
    int Ans = 0;
    for (int i = 1; i <= n; i++) {
      scanf ("%d", &l);
      Ans = Ans ^ Calc(l);
    }
    if (Ans == 0) printf ("W\n");
    else printf ("L\n");
  }  
}