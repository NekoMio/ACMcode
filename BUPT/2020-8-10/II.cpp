#include <bits/stdc++.h>
using namespace std;
int n;
typedef pair<int, int> Di;
Di a[100000];
void DFS(int n) {
  if (n == 2) {
    a[1] = Di(1, 2);
    // a[2] = Di(1, 3);
    return;
  } 
  if (n == 3) {
    a[1] = Di(1, 2);
    a[2] = Di(1, 3);
    a[3] = Di(2, 3);
    return;
  }
  DFS(n / 2);
  int t = n / 2;
  int n1 = (n / 2) * (n / 2 - 1) / 2;
  int n2 = n * (n - 1) / 2;
  int pos = n1;
  if (n & 1) {
    for (int i = 1; i <= n; i++) if (i != t + 1) {
      a[++pos] = Di(i, t + 1);
    }
  }
  for (int i = 1; i <= t; i++) {
    for (int j = 1; j <= t; j++) {
      a[++pos] = Di(i, j + t + (n & 1));
    }
  }
  for (int i = 1; i <= t; i++) {
    a[++pos] = Di(a[i].first + t + (n & 1), a[i].second + t + (n & 1));
  }
}
int main() {
  int t;
  scanf ("%d", &t);
  while (t--) {
    memset (a, 0, sizeof (a));
    scanf ("%d", &n);
    DFS(n);
    int n2 = n * (n - 1) / 2;
    for (int i = 1; i <= n2; i++) {
      printf ("%d %d\n", a[i].first, a[i].second);
    }
  }
}