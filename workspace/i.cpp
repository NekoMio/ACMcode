#include <bits/stdc++.h>
using namespace std;
int a[20], ans[20]; 
int tmp[20];
bool Test(int k, int n) {
  for (int i = 1; i <= n; i++)
    tmp[i] = a[i];
  for (int i = 1; i <= n; i++) {
    
  }
}
int main() {
  int n, N = 1;
  scanf ("%d", &n);
  for (int i = 1; i <= n; i++) {
    a[i] = i;
    N = N * i;
  }
  while (N--) {
    for (int i = 1; i <= n; i++) {
      if (Test(i, n)) {
        ans[i]++; 
        break;
      }
    }
  }
  printf ("%d\n", ans);
}