#include <bits/stdc++.h>
using namespace std;
struct data {
  int END, v, next;
}v[997007];
int first[1000], p;
void add(int a, int b, int c) {
  v[p].END = b;
  v[p].v = c;
  v[p].next = first[a];
  first[a] = p++;
}
vector<int> vc;
int main() {
  int n, m;
  memset (first, -1, sizeof(first));
  scanf ("%d", &n);
  m = n * (n - 1) / 2;
  int a, b, c;
  for (int i = 1; i <= m; i++) {
    scanf ("%d%d%d", &a, &b, &c);
    add(a, b, c);
    add(b, a, c);
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    vc.clear();
    for (int j = first[i]; j != -1; j = v[j].next) {
      vc.push_back(v[j].v);
    }
    sort(vc.begin(), vc.end(), greater<int>());
    for (int j = 0; j < vc.size(); j += 2) {
      ans += vc[j];
    }
  }
  printf ("%lld\n", ans);
}