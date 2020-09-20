#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    if (n % 2 == 1) {
      for (int i = 2; i <= n; i += 2) {
        for (int j = 1; j < i; j++) {
          cout << j << " " << i << "\n";
          cout << j << " " << i + 1 << "\n";
        }
        cout << i << " " << i + 1 << "\n";
      }
    } else {
      for (int i = 2; i < n; i += 2) {
        for (int j = 1; j < i; j++) {
          cout << j << " " << i << "\n";
          cout << j << " " << i + 1 << "\n";
        }
        cout << i << " " << i + 1 << '\n';
      }
      for (int j = 1; j < n; j++) {
        cout << j << " " << n << '\n';
      }
    }
  }
}