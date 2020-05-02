#include <bits/stdc++.h>
using namespace std;
vector<int> vc;
int a[70];
set<int> st;
int main() {
  srand(time(NULL));
  int n = 62;
  a[1] = 0;
  st.insert(0);
  for (int i = 2; i <= n; i++) {
    a[i] = rand() % (999 - i);
    while (st.find(a[i]) != st.end()) a[i] = rand() % (109 - i * 10);
    st.insert(a[i]);
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      vc.push_back(abs(a[i] - a[j]));
    }
  }
  sort(vc.begin(), vc.end());
  printf ("%d\n", n);
  for (auto x : vc) printf ("%d ", x);
}