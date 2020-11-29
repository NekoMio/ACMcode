#include <bits/stdc++.h>
using namespace std;
set<int> st[100005];
int a[100005];
int main() {
  int N, Q;
  scanf ("%d%d", &N, &Q);
  long long Sum = 0;
  for (int i = 1; i <= N; i++) {
    scanf ("%d", &a[i]);
    Sum = Sum + 1ll * a[i] * a[i];
  }
  char s[2];
  while (Q--) {
    int x1, x2, y;
    scanf ("%s%d%d%d", s, &x1, &x2, &y);
    if (s[0] == '+') {
      auto pos = st[x1].upper_bound(y);
      int p1 = , p2;
      if (pos != st[x1].end()) 
    }
  }
}