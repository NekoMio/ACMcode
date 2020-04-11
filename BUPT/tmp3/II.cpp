#include <bits/stdc++.h>
using namespace std;
int a[101];
int main() {
  a[1] = 1;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 100; j++) {
      a[j] += a[j - 1]; 
    }
  }
  for (int i = 1; i <= 100; i++) printf ("%d ", a[i]);
}